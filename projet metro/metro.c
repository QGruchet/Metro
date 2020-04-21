
// metro.c du projet Metro
// Contient le main du projet

#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "lire_ecrire.h"
#include "types.h"


int choix_depart(){
	int station_depart;
	printf("Entrez le numero de la station de depart : \n");
	scanf("%d\n", &station_depart);
	return station_depart;
}

int choix_arrivee(){
	int station_arrivee;
	printf("Entrez le numero de la station d'arrivee : \n");
	scanf("%d\n", &station_arrivee);
	return station_arrivee;
}

int main(int argc, char* argv[])
{

	GRAPHE graphe;
	graphe.nb_sommets = compte_nb_sommets("metro.txt");
	printf("%d stations trouvées\n", graphe.nb_sommets);
	graphe = initialise_stations("metro.txt", graphe);

	/*TEST DE LA FONCTION INITIALISE_STATIONS*/
	/*for (int j = 1; j < 100; ++j)
	{
		for (int i = 0; i < graphe.nb_sommets; ++i)
		{
			if(graphe.station[i].num_ligne == j){
				printf("station numero %d | ", graphe.station[i].num_sommet);
				printf("ligne : %d station : ", graphe.station[i].num_ligne);
				for(int h = 0; h < graphe.station[i].nombre_nom; ++h){
					printf("%c", graphe.station[i].nom_station[h]);
				}
				printf("\n");
			}
		}
		
	}*/
	graphe = initialise_reseau("metro.txt", graphe);

	/*TEST DE LA FONCTION INITIALISE_RESEAU*/
	/*for (int i = 0; i < graphe.nb_sommets; ++i)
	{
		for (int j = 0; j < graphe.nb_sommets; ++j)
		{
			if(graphe.reseau[i][j].ponderation == 88888) continue;
			printf("station : %d %d term :%d %d\n", graphe.station[j - 1].num_sommet, graphe.station[i].num_sommet, graphe.reseau[i][j].terminus, graphe.reseau[j][i].terminus);
		}
	}*/
	int station_depart = choix_depart();
	int station_arrivee = choix_arrivee();
	
	graphe = calcul_plus_court_chemin(graphe, station_depart, station_arrivee);
	libere_station(graphe);
	return 0;
}


/*----------IDEE DE MENU (A DEVELOPPER)----------*/


// int choix(const char* cmd){
// 	GRAPHE graphe;
// 	graphe.nb_sommets = compte_nb_sommets("metro.txt");
// 	graphe = initialise_stations("metro.txt", graphe);
// 	graphe = initialise_reseau("metro.txt", graphe);
	
// 	if(cmd[0] == 'q'){
// 		libere_station(graphe);
// 		return printf("\tBye Bye\n"), 0;
// 	}
// 	if(cmd[0] == 'l'){
// 		/*TEST DE LA FONCTION INITIALISE_STATIONS*/
// 		for (int j = 1; j < 100; ++j)
// 		{
// 			for (int i = 0; i < graphe.nb_sommets; ++i)
// 			{
// 				if(graphe.station[i].num_ligne == j){
// 					printf("station numero %d | ", graphe.station[i].num_sommet);
// 					printf("ligne : %d station : ", graphe.station[i].num_ligne);
// 					for(int h = 0; h < graphe.station[i].nombre_nom; ++h){
// 						printf("%c", graphe.station[i].nom_station[h]);
// 					}
// 					printf("\n");
// 				}
// 			}
			
// 		}
// 	}

// 	if(cmd[0] == 'r'){
// 		/*TEST DE LA FONCTION INITIALISE_RESEAU*/
// 		for (int i = 0; i < graphe.nb_sommets; ++i)
// 		{
// 			for (int j = 0; j < graphe.nb_sommets; ++j)
// 			{
// 				if(graphe.reseau[i][j].ponderation == 88888) continue;
// 				printf("station : %d %d term :%d %d\n", graphe.station[j - 1].num_sommet, graphe.station[i].num_sommet, graphe.reseau[i][j].terminus, graphe.reseau[j][i].terminus);
// 			}
// 		}
// 	}

// 	if(cmd[0] == 'h'){
// 		printf("l : lister les stations\n");
// 		printf("q : quitter le menu\n");
// 		printf("r : afficher le reseau\n");
// 		printf("n : afficher le nombres de stations\n");
// 		printf("c : calcul le plus court chemin entre deux stations\n");
// 	}

// 	if(cmd[0] == 'n'){
// 		printf("%d stations trouvées\n", graphe.nb_sommets);
// 	}
	
// 	if(cmd[0] == 'c'){
// 		//graphe = calcul_plus_court_chemin(graphe, 0000, 0007);
// 	}
// }


// int main(int argc, char* argv[])
// {
// 	char buffer[64];
// 	do{
// 		printf(">");
// 											//sert uniquement pour l'idee a developper
// 		fgets(buffer, 64, stdin);
// 	}while(choix(buffer));
	
// }