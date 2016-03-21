#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#ifndef WIN32
    #include <sys/types.h>
    #define CLEAR "clear" 
    /* system("clear") pour UNIX */
#else
    #define CLEAR "cls" 
    /* system("cls") pour Windows */
#endif


    /*
     * @author: Xavier CHOPIN
     */


    /** Fonction setCheminComplet: donne le chemin complet pour un fichier donné
    * chemin: string de base, nomDossier: nom du dossier Parent, nomFichier: nom du fichier donné
    */

    void setCheminComplet(char * chemin,char * nomDossier, char * nomFichier){
        chemin[0] = '\0'; // réinitialisation
        strcpy(chemin,"./");
        strcat(chemin,nomDossier);
        strcat(chemin,"/");
        strcat(chemin,nomFichier);
    }



    int main (int argc, char *argv[]) {

        struct dirent *pDirent;
        DIR *pDir;
        char chemin [2048];
        strcpy(chemin,"./");
        strcat(chemin,argv[1]);
        strcat(chemin,"/");
        pid_t pid[9999]; // théoriquement 74 mais on pourrait très bien rajouter des fichiers
        int i = 0;
        int status ;
        int resultat = 0;
        system(CLEAR); /* On efface l'écran. */

        if (argc < 3) {
        perror("Vous n'avez pas entré d'argument : le fichier + le mot à chercher  !\n");
        return EXIT_FAILURE;

        }

     

        printf("\n ____ ____ ____ _________ ____ ____ ____ ____ ____ ____ ____ ____ ____ \n");
        printf("||T |||H |||E |||       |||D |||E |||C |||R |||Y |||P |||T |||E |||R ||\n");
        printf("||__|||__|||__|||_______|||__|||__|||__|||__|||__|||__|||__|||__|||__||\n");
        printf("|/__\\|/__\\|/__\\|/_______\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|\n");

        printf("\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("Author: Xavier CHOPIN - Université de Lorraine - 2016 \n \n ");


        pDir = opendir (argv[1]);
        if (pDir == NULL) {
            printf ("Impossible d'ouvrir le répertoire %s'\n", argv[1]);
            return 1;
        }

        while ((pDirent = readdir(pDir)) != NULL && resultat == 0) {
           
            if (!strcmp (pDirent->d_name, "."))
                 continue;
            if (!strcmp (pDirent->d_name, ".."))    
                 continue;
            if (!strcmp (pDirent->d_name, ".DS_Store")) // Et oui je code sur un Mac
                continue;


                                switch( pid[i] = fork() ) {

                                    case (pid_t) -1 :   perror("Création Impossible");
                                                        exit(1);

                                    break;

                                    case (pid_t) 0 :    /** Processus fils */

                                                        // théoriquement le dossier est clean pas besoin de vérifier si ce sont des fichiers..
                                                       // sinon c'est S_ISREG(s.st_mode) où s est une struct stat ;-)
                                                        setCheminComplet(chemin,argv[1],pDirent->d_name);
                                                        execl("./mini-projet","mini-projet", chemin, argv[2], NULL);
                                                        
                                                     
                                    break;

                                    default :           /** Processus père */
                                                     
                                    
                                                        while (wait(&status) > 0) {
                                                            if (WEXITSTATUS (status))
                                                                resultat = 1;
                                                        }
                                    break;
                                }                       
                            
                        
                        
            i++;




           
        }

        if (resultat == 0){



        printf("\n ____________________ _________________________________\n");
        printf("| R E S U L T A T   |||  AUCUN RESULTAT POUR %s :( ||\n",argv[2]);
        printf("|___________________|||_______________________________||\n\n");



        }

        closedir (pDir);
        return 0;
    }
