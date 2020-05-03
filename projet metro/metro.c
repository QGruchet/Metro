#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphe.h"
#include "lire_ecrire.h"
#include "types.h"
// Fonction choix -- analyse le cmd et lance la fonction qui correspond
// \param		cmd 			tableau dynamique qui contient la commande de l'user
// \param		graphe 			structure graphe
// \return						0
 int choix(const char* cmd, GRAPHE graphe){

	if(cmd[0] == 'q' && cmd[1] == 'u' && cmd[2] == 'i' && cmd[3] == 't' && cmd[4] == 't' && cmd[5] == 'e' && cmd[6] == 'r'){
		return printf("\tBye Bye. Revenez vite chez &-BonVoyage !\n"), 0;
	}
	if(cmd[0] == 'l' && cmd[1] == 's'){

		if(cmd[2] == '-' && cmd[3] == 'a'){
			for(int i = 0; i < graphe.nb_sommets; i-=-1){
				printf("  numero %d | ", graphe.station[i].num_sommet);
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
						printf("  numero %d | ", graphe.station[i].num_sommet);
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
				printf("  station : n°%d et n°%d terminus station : n°%d et n°%d\n", graphe.station[j - 1].num_sommet, graphe.station[i].num_sommet, graphe.reseau[i][j].terminus, graphe.reseau[j][i].terminus);
			}
		}
	}

	if(cmd[0] == 'n' && cmd[1] == 'o' && cmd[2] == 'm' && cmd[3] == 'b' && cmd[4] == 'r' && cmd[5] == 'e' ){
		printf("  %d stations trouvées\n", graphe.nb_sommets);
	}
	
 	if(cmd[0] == 'c' && cmd[1] == 'a' && cmd[2] == 'l' && cmd[3] == 'c' && cmd[4] == 'u' && cmd[5] == 'l'){
 		if(cmd[6] == '-' && cmd[7] == 'a'){
			int deb, fin = 0;
			printf("\tOH SH*T HERE WE GO AGAIN !\n");
			printf("  Veuillez rentrer le numero de la station de départ : ");
			scanf("%d", &deb);
			printf("\tStation de départ : %s\n", graphe.station[deb].nom_station);
			printf("  Veuillez rentrer le numero de la station d'arrivée : ");
			scanf("%d", &fin);
			printf("\tStation d'arrivee : %s\n\n", graphe.station[fin].nom_station);
			graphe = calcul_plus_court_chemin(graphe, deb, fin, 2);
		}
		if(cmd[6] == '-' && cmd[7] == 'r'){
			srand(time(0));
			int deb, fin = 0;
			deb = rand() % 376;
			fin = rand() % 376;
			printf("\tStation de départ : %s\n\n", graphe.station[deb].nom_station);
			printf("\tStation d'arrivee : %s\n\n", graphe.station[fin].nom_station);
			graphe = calcul_plus_court_chemin(graphe, deb, fin, 3);
		}
		if(cmd[6] == '-' && cmd[7] == 'l'){
			int deb, fin = 0;
			printf("\tOH SH*T HERE WE GO AGAIN !\n");
			printf("  Veuillez rentrer le numero de la station de départ : ");
			scanf("%d", &deb);
			
			printf("\tStation de départ : %s\n", graphe.station[deb].nom_station);
			printf(  "Veuillez rentrer le numero de la station d'arrivée : ");
			scanf("%d", &fin);
			printf("\tStation d'arrivee : %s\n\n", graphe.station[fin].nom_station);
			graphe = calcul_plus_court_chemin(graphe, deb, fin, 1);
		}
		if(cmd[6] == '-' && cmd[7] == 't'){
			int deb, fin = 0;
			printf("\tOH SH*T HERE WE GO AGAIN !\n");
			printf("  Veuillez rentrer le numero de la station de départ : ");
			scanf("%d", &deb);
			printf("\tStation de départ : %s\n", graphe.station[deb].nom_station);
			printf(  "Veuillez rentrer le numero de la station d'arrivée : ");
			scanf("%d", &fin);
			printf("\tStation d'arrivee : %s\n\n", graphe.station[fin].nom_station);
			graphe = calcul_plus_court_chemin(graphe, deb, fin, 3);
		}
		if(cmd[7] ==' ' || cmd[7] == '\n'){
			printf("  Veuillez rajouter un argument après la commande (-a, -t ou -l)\n");
		}
 	}

 	if(cmd[0] == 'h' && cmd[1] == 'e' && cmd[2] == 'l' && cmd[3] == 'p'){
		printf("\thelp : affiche le guide des commandes disponibles\n");
		printf("\tls-l : liste les stations par ligne\n");
		printf("\tls-a : liste les stations par ordre alphabetique\n");
		printf("\treseau : affiche le reseau\n");
		printf("\tnombre : affiche le nombres de stations\n");
		printf("\tcalcul-l : affiche le trajet suivi par l'algo (permet de débugg)\n");
		printf("\tcalcul-a : affiche le trajet sous forme d'un affichage\n");
		printf("\tcalcul-t : affiche le trajet sous forme d'affichage + debugg\n");
		printf("\tcalcul-r : affiche un trajet aléatoire sous forme d'affichage + debugg\n");
		printf("\tquitter : quitte le programme\n");
	}

 	return -1;
}

// Fonction pincipale -- 
// \param		arc 			nombre d'argument 
// \param		argc[] 			argument
// \return						0 en cas de reussite
int main(int argc, char* argv[])
{
	printf("   Bienvenue dans l'appli &-BonVoyage. Cette application permet de trouver son trajet (le plus rapide) à traversle metropolitain Parisien. Tapez 'help' pour obtenir la liste des commandes disponibles.\n");
	printf("   P.S: N'oubliez pas de quitter le programme pour libérer la mémoire. La Direction.\n\n\n");
	char buffer[64];
	GRAPHE graphe;
	graphe = compte_nb_sommets(NOMFIC, graphe);
	graphe = initialise_stations(NOMFIC, graphe);
	graphe = initialise_reseau(NOMFIC, graphe);
	
 	do{
 		printf("  >>");
 											
 		fgets(buffer, 64, stdin);
 	}while(choix(buffer, graphe));
 	libere_graphe(graphe);
	
}