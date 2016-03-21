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
#include <limits.h>
#define LENGTH(x)  (sizeof(x) / sizeof((x)[0]))

// @author: Xavier Chopin

/** Fonction permettant de concatener un String et un char
* @param: string: la chaine de base, c: le char que l'on veut concaténer
*/
void concatener(char * string, char c) {

	char chaine[2];
	chaine[0] = c;
	chaine[1] = '\0';
	strcat(string,chaine);

}

/** Fonction pour nettoyer une array
* @param: string : le tableau 
*/
void clear(char * string){
		string[0] = '\0';
}


// Lecture de caractères
int main(int argc,char *argv[]) {

	if (argc < 4 ){
		perror("Vous n'avez pas entré d'argument !");
		return EXIT_FAILURE;
	}

	char buffer; 
	int descr_tube = atoi(argv[1]);
	char tabComparateur[9999];


	int i = 0;
	int res = -1;
	int trouve = 0;
	int decalage = atoi(argv[3]);
	char newValeur;
	char resultat[9999]; 


	//Nous ne connaissons pas la taille du buffer donc on lit char par char
	while ( read(descr_tube,&buffer,sizeof(char))  ){

			newValeur = (int)buffer - decalage; // Nouvelle valeur avec le décalage

				//si on tombe entre A - Z 
			if ( newValeur >=65 && newValeur <= 90 ){
				concatener(resultat,newValeur);
				concatener(tabComparateur,newValeur);
				
			}else{
				// Si le caractère crypté était un lettre c'est un espace
				if (((int)buffer>=65 && (int) buffer<=90 )){


					if (newValeur == 64){
						concatener(resultat,' ');
						
						// Si on a recontré le mot plus besoin de faire tous ces tests
						if (trouve == 0){	
									
							if (strcmp(argv[2],tabComparateur) == 0){
								trouve = 1; // Résultat trouvé !		
							}else{
								clear(tabComparateur); // Si on tombe sur un espace: il faut recommencer dépuis le début dans le tableau pour recomparer avec le prochain mot
							}
						}


					}else{
							concatener(resultat,91-(64-newValeur));
							concatener(tabComparateur,91-(64-newValeur));

					}



				}else if (newValeur < 64 ) {

					// si c'est une virgule ;)
					if (buffer == 44){
						concatener(resultat,',');
					}else{

					concatener(resultat,91-decalage);
					concatener(tabComparateur,91-decalage);


					}
					


				}
				
			}


		
			
		}


// Si on trouve le texte cherché on affiche le message décrypté
if (trouve){
	printf("\n Décryptage effectué: %s \n",resultat);
}


			
return trouve;

}