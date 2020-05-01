#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "lire_ecrire.h"
#include "types.h"

 int choix(const char* cmd, GRAPHE graphe){

	if(cmd[0] == 'q'){
		libere_graphe(graphe);
		return printf("\tBye Bye. Revenez vite Ebovoyag !\n"), 0;
	}
	if(cmd[0] == 'l'){
		for (int j = 1; j < 100; ++j)
		{
			for (int i = 0; i < graphe.nb_sommets; ++i)
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

	if(cmd[0] == 'r'){
		for (int i = 0; i < graphe.nb_sommets; ++i)
		{
			for (int j = 0; j < graphe.nb_sommets; ++j)
			{
				if(graphe.reseau[i][j].duree_entre_station == 88888) continue;
				printf("station : %d %d term :%d %d\n", graphe.station[j - 1].num_sommet, graphe.station[i].num_sommet, graphe.reseau[i][j].terminus, graphe.reseau[j][i].terminus);
			}
		}
	}

	if(cmd[0] == 'h'){
		printf("l : lister les stations\n");
		printf("q : quitter le menu\n");
		printf("r : afficher le reseau\n");
		printf("n : afficher le nombres de stations\n");
		printf("c : calcul le plus court chemin entre deux stations\n");
	}

	if(cmd[0] == 'n'){
		printf("%d stations trouvées\n", graphe.nb_sommets);
	}
	
 	if(cmd[0] == 'c'){
		int deb, fin = 0;
		printf("\tOH SHIT HERE WE GO AGAIN !\n");
		printf("Veuillez rentrer le numero de la station de départ : ");
		scanf("%d\n", &deb);
		printf("Veuillez rentrer le numero de la station d'arrivée : ");
		scanf("%d\n", &fin);
		graphe = calcul_plus_court_chemin(graphe, deb, fin);
 	}
 	return -1;
}


int main(int argc, char* argv[])
{
	printf("\t     Bienvenue dans l'appli Ebovoyag. Cette application permet de trouver son trajet à travers le metropolitain Parisien. Tapez 'h' pour obtenir la liste des commandes disponibles.\n\n\n");
	char buffer[64];
	GRAPHE graphe;
	graphe = compte_nb_sommets(NOMFIC, graphe);
	graphe = initialise_stations(NOMFIC, graphe);
	graphe = initialise_reseau(NOMFIC, graphe);
	
 	do{
 		printf("  >>");
 											//sert uniquement pour l'idee a developper
 		fgets(buffer, 64, stdin);
 	}while(choix(buffer, graphe));
	
}