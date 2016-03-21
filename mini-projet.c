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
#include <ctype.h>
#include <sys/wait.h>


/*
 * @author: Xavier CHOPIN
 */




int main(int argc,char *argv[]) {

	struct stat s;
	char ref[1024];
	strcpy(ref,argv[1]);
	char en_tete[2 * sizeof(char) + 1]; 
	int trouve = 0;
	int status ;
	char tabComparateur[sizeof(argv[2])];



	// Vérifions si un argument a été donné au lancement du programme
	if (argc < 3){

		perror("Vous n'avez pas entré d'argument : le fichier + le mot à chercher  !\n");
		return EXIT_FAILURE;

	}else{
		// Vérifions si l'argument donné existe
		if (stat(ref,&s) == -1) {

			perror("Le fichier/répertoire n'existe pas\n");
			return EXIT_FAILURE;

		}else{

			int file = open(ref, O_RDONLY);
			int code = read(file,&en_tete, 2 * sizeof(char));

			if (code < 0){

				// FERMER LE FICHIER
				close(file);
				perror("Erreur de lecture");
				return EXIT_FAILURE;

			}else{

				if ( strcmp(en_tete, "CR") == 0 ){
					

					// Passons à l'étape supérieure
					int nb [2 * sizeof(int)];
					read ( file, &nb , 2 * sizeof(int));
					int tailleMessage = nb[0];
					int nbOctetAvantMessage = nb[1];
				
					// testons la cohérence de ces nombres: les deux int doivent etre positifs
					// La somme de ces nombres doit être inférieur à la taille du fichier : s.st_size

					if ( (tailleMessage > 0 && nbOctetAvantMessage > 0) && ( tailleMessage + nbOctetAvantMessage ) <= s.st_size )  {

						/** Etape III : déplacement du curseur dans le fichier */

						lseek(file, nbOctetAvantMessage, SEEK_CUR);
						char message[tailleMessage]; 
						read(file, &message, sizeof(message));
						int nbDecalage = 25; // Nombre de décalage à tester
						int nbFois = nbDecalage;

						// Tube - Ecriture pour envoyer à l'autre fichier
						char buffer; 
						int tubes[nbDecalage][2];
						
						char lecteur_tube[9999];
						char decal[9999];
						pid_t pid[nbDecalage]; // Création du processus

						for (int proc = 1 ; proc < nbDecalage ; proc++){	
							if (trouve != 1){

								pipe(tubes[proc]);
		
								switch( pid[proc] = fork() ) {

									case (pid_t) -1 :   perror("Création Impossible");
													    exit(1);

									break;

									case (pid_t) 0 :    /** Processus fils */
														sprintf(lecteur_tube,"%d",tubes[proc][0]);
														sprintf(decal,"%d",proc);
													 	close(tubes[proc][1]); // Fermeture de l'écriture 
													    // Envoie au Fils => int: Lecteur du tube, String: valeur à rechercher, int: décalage
													    execl("./fils","fils",lecteur_tube, argv[2], decal, NULL);
													    close(tubes[proc][0]); // Fermeture de la lecture
													 
									break;

									default :           /** Processus père */
													 
													    close(tubes[proc][0]); // Fermeture de la lecture car on est dans l'écrivain
														for (int i = 0; i < tailleMessage ;i++){
															buffer = message[i];
															write(tubes[proc][1], &buffer, sizeof(char));
														}
														close(tubes[proc][1]); // Fermeture de l'écriture 
														

													 	 while (wait(&status) > 0) {
													  		if (WEXITSTATUS (status)){
													  			trouve = 1;


													        printf("\n ____________________ ___________________________________________________\n");
													        printf("|  		    |||  Le programme a trouvé %s     	         ||\n",argv[2]);
													        printf("|  	  1	    |||  dans %s 	      	         ||\n",argv[1]);	
													       	printf("|  R E S U L T A T  |||  en utilisant un décalage de %d                  ||\n",proc);
													        printf("|___________________|||__________________________________________________||\n\n");


															}
													 
													  }
									break;
								}						
							}
						}
						


						


						

					}else{

						// FERMER LE FICHIER
						close(file);

						printf("Erreur: Il manque l'entète --' \n");
						return EXIT_FAILURE;
					}
					

				}else{

					// FERMER LE FICHIER
					close(file);

					printf("Erreur: Le fichier n'est pas crypté... ;-; \n");
					return EXIT_FAILURE;
				}
			}

			// FERMER LE FICHIER
			close(file);
		}
	}

 
	return trouve;

}