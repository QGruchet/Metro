#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "lire_ecrire.h"
#include "types.h"

 int choix(const char* cmd, GRAPHE graphe){

	if(cmd[0] == 'q' && cmd[1] == 'u' && cmd[2] == 'i' && cmd[3] == 't' && cmd[4] == 't' && cmd[5] == 'e' && cmd[6] == 'r'){
		libere_graphe(graphe);
		return printf("\tBye Bye. Revenez vite chez Ebovoyag !\n"), 0;
	}
	if(cmd[0] == 'l' && cmd[1] == 's'){

		if(cmd[2] == '-' && cmd[3] == 'a'){
			for(int i = 0; i < graphe.nb_sommets; i-=-1){
				printf("numero %d | ", graphe.station[i].num_sommet);
				if(graphe.station[i].num_ligne == 70){
					printf("ligne : 7bis station : ");
				}
				if(graphe.station[i].num_ligne == 30){
					printf("ligne : 3bis station : ");
				}
				else printf("ligne : %d station : ", graphe.station[i].num_ligne);
				for(int h = 0; h < graphe.station[i].nombre_nom; ++h){
					printf("%c", graphe.station[i].nom_station[h]);
				}
				printf("\n");
			}
		}

		if(cmd[2] == '-' && cmd[3] == 'l'){
			for (int j = 1; j < 100; ++j)
			{
				for (int i = 0; i < graphe.nb_sommets; i-=-1)
				{
					if(graphe.station[i].num_ligne == j){
						printf("numero %d | ", graphe.station[i].num_sommet);
						if(graphe.station[i].num_ligne == 70){
							printf("ligne : 7bis station : ");
						}
						if(graphe.station[i].num_ligne == 30){
							printf("ligne : 3bis station : ");
						}
						else printf("ligne : %d station : ", graphe.station[i].num_ligne);
						for(int h = 0; h < graphe.station[i].nombre_nom; ++h){
							printf("%c", graphe.station[i].nom_station[h]);
						}
						printf("\n");
					}
				}
			}
		}
	}

	if(cmd[0] == 'r'&& cmd[1] == 'e' && cmd[2] == 's' && cmd[3] == 'e' && cmd[4] == 'a' && cmd[5] == 'u'){
		for (int i = 0; i < graphe.nb_sommets; ++i)
		{
			for (int j = 0; j < graphe.nb_sommets; ++j)
			{
				if(graphe.reseau[i][j].duree_entre_station == 88888) continue;
				printf("station : %d %d term :%d %d\n", graphe.station[j - 1].num_sommet, graphe.station[i].num_sommet, graphe.reseau[i][j].terminus, graphe.reseau[j][i].terminus);
			}
		}
	}

	if(cmd[0] == 'n' && cmd[1] == 'o' && cmd[2] == 'm' && cmd[3] == 'b' && cmd[4] == 'r' && cmd[1] == 'e' ){
		printf("%d stations trouvées\n", graphe.nb_sommets);
	}
	
 	if(cmd[0] == 'c' && cmd[1] == 'a' && cmd[2] == 'l' && cmd[3] == 'c' && cmd[4] == 'u' && cmd[5] == 'l' && cmd[6] == 'e' ){
 		if(cmd[7] == '-' && cmd[8] == 'a'){
			int deb, fin = 0;
			printf("\tOH SHIT HERE WE GO AGAIN !\n");
			printf("Veuillez rentrer le numero de la station de départ : ");
			scanf("%d", &deb);
			printf("\tStation de départ : %s\n", graphe.station[deb].nom_station);
			printf("Veuillez rentrer le numero de la station d'arrivée : ");
			scanf("%d", &fin);
			printf("\tStation d'arrivee : %s\n\n", graphe.station[fin].nom_station);
			graphe = calcul_plus_court_chemin(graphe, deb, fin, 2);
		}
		if(cmd[7] == '-' && cmd[8] == 'l'){
			int deb, fin = 0;
			printf("\tOH SHIT HERE WE GO AGAIN !\n");
			printf("Veuillez rentrer le numero de la station de départ : ");
			scanf("%d", &deb);
			
			printf("\tStation de départ : %s\n", graphe.station[deb].nom_station);
			printf("Veuillez rentrer le numero de la station d'arrivée : ");
			scanf("%d", &fin);
			printf("\tStation d'arrivee : %s\n\n", graphe.station[fin].nom_station);
			graphe = calcul_plus_court_chemin(graphe, deb, fin, 1);
		}
		if(cmd[7] == '-' && cmd[8] == 't'){
			int deb, fin = 0;
			printf("\tOH SHIT HERE WE GO AGAIN !\n");
			printf("Veuillez rentrer le numero de la station de départ : ");
			scanf("%d", &deb);
			printf("\tStation de départ : %s\n", graphe.station[deb].nom_station);
			printf("Veuillez rentrer le numero de la station d'arrivée : ");
			scanf("%d", &fin);
			printf("\tStation d'arrivee : %s\n\n", graphe.station[fin].nom_station);
			graphe = calcul_plus_court_chemin(graphe, deb, fin, 3);
		}
		if(cmd[7] ==' ' || cmd[7] == '\n'){
			printf("Veuillez rajouter un argument après la commande (-a, -t ou -l)\n");
		}
 	}

 	if(cmd[0] == 'h' && cmd[1] == 'e' && cmd[2] == 'l' && cmd[3] == 'p'){
		printf("help : affiche le guide des commandes disponibles\n");
		printf("ls-l : liste les stations par ligne\n");
		printf("ls-a : liste les stations par ordre alphabetique\n");
		printf("reseau : affiche le reseau\n");
		printf("nombre : affiche le nombres de stations\n");
		printf("calcule-l : affiche le trajet sous forme de liste\n");
		printf("calcule-a : affiche le trajet sous forme d'un affichage\n");
		printf("calcule-t : affiche le trajet sous forme de liste et avec affichage\n");
		printf("quitter : quitte le programme\n");
	}

 	return -1;
}


int main(int argc, char* argv[])
{
	printf("   Bienvenue dans l'appli Ebovoyag. Cette application permet de trouver son trajet (le plus rapide) à travers le metropolitain Parisien. Tapez 'help' pour obtenir la liste des commandes disponibles.\n\n\n");
	char buffer[64];
	GRAPHE graphe;
	graphe = compte_nb_sommets(NOMFIC, graphe);
	graphe = initialise_stations(NOMFIC, graphe);
	graphe = initialise_reseau(NOMFIC, graphe);
	
 	do{
 		printf("  >>");
 											
 		fgets(buffer, 64, stdin);
 	}while(choix(buffer, graphe));
	
}