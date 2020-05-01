#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lire_ecrire.h"
#include "graphe.h"
#include "types.h"

// Fonction sommet -- compte le nombre de ligne dans le fichier
// \param		*nomFichier		nom du fichier a ouvrir
// \return						nombre de ligne au total
GRAPHE compte_nb_sommets(char *nomFichier, GRAPHE graphe)
{
	printf("Initialisations du nombres de stations...");
	FILE *f = fopen(nomFichier, "r");
	int i = 0;
	char c = ' ';
	char d = ' ';
	while (i < 3) {		//On ignore les 3 premieres lignes
		c = fgetc(f);
		if (c == '\n')
			i++;
	}
	i = 1;
	while(d != 'E')
	{
		c = fgetc(f);
		if (c == '\n') {
			d = fgetc(f);
			if (d == 'V') {
				i++;
			}
		}
	}
	fclose(f);
	printf("DONE\n");
	graphe.nb_sommets = i;
	return graphe;
}

// Fonction GRAPHE -- remplie la structure avec toutes les infos des stations (nom, numéro, ligne etc...)
// \param		*nomFichier		nom du fichier a ouvrir
// \param 		 graphe 		structure GRAPHE à remplir
// \return						GRAPHE
GRAPHE initialise_stations(char *nomFichier, GRAPHE graphe)
{
	printf("Recuperations des infos sur les stations...");
	FILE *f = fopen(nomFichier, "r");
	char c =' ';
	int num_station;
	int num_ligne;
	int i = 0;
	int j = 0;
	graphe.station = malloc(sizeof(SOMMET) * graphe.nb_sommets);

	while (i < 3) {		//on lit les 3 premières lignes qui ne sont que des commentaires
		c = fgetc(f);
		if (c == '\n')
			i++;
	}
	//pour chaque sommet, on lit son numero de sommet, son numero de ligne, et son nom
	//chaque sommet correspond à une station d'une ligne
	//Attention: on peut avoir plusieurs stations avec le même nom (pas la même ligne)
	for (int h = 0; h < graphe.nb_sommets; h++) {
		c = fgetc(f);
		if(c == 'V'){
			fscanf(f, "%d %d ", &num_station, &num_ligne);
			j = 0;
			do { //lecture du nom de la station
				c = fgetc(f);
				graphe.station[h].nom_station[j] = c;
				j++;
			}while(c != '\n');
			graphe.station[h].nom_station[j - 1] = '\0';
			graphe.station[h].nombre_nom = j;
			graphe.station[h].num_sommet = num_station;
			graphe.station[h].num_ligne = num_ligne;
		}
	}
	fclose(f);
	printf("DONE\n");
	return graphe;
}

// Fonction GRAPHE -- remplie la structure GRAPHE avec toutes les liaisons entre stations
// \param		*nomFichier		nom du fichier a ouvrir
// \param		 graphe 		structure a remplir
// \return						GRAPHE
GRAPHE initialise_reseau(char *nomFichier, GRAPHE graphe)
{
	printf("Initialisations du reseaux du Metropolitain...");
	FILE *f = fopen(nomFichier, "r");
	char c, d = ' ';
	graphe.reseau = malloc(sizeof(LIAISON*)*473);
	for (int i = 0; i < 473; ++i)
	{
		graphe.reseau[i] = malloc(sizeof(LIAISON) * 473);
	}

	while (d != 'E') {	//on lit jusqu'à lire le 'E' signifiant le début des LIAISONs
		c = fgetc(f);
		if (c == '\n')
			d = fgetc(f);
	}
	d = ungetc(d, f);
	int test = 0;
	int station1, station2, duree, term1, term2;
	int i, j;
	//on met d'abord aucun terminus et aucune liaison entre chaque sommet
	//comme ça les sommets avec les mêmes noms n'auront pas de terminus car c'est juste un changement de ligne
	for (i = 0; i < graphe.nb_sommets; i++) {
		for (j = 0; j < graphe.nb_sommets; j++) {
			graphe.reseau[i][j].terminus = NOEUD;
			graphe.reseau[i][j].duree_entre_station = AUCUN_ARC;
		}
	}
	while (test != 1) {	//on lit le fichier jusqu'à la fin
		fscanf(f, "%c %d %d %d %d %d ", &c, &station1, &station2, &duree,
		       &term1, &term2);
		d = fgetc(f);
		if (d == EOF)
			test = 1;
		d = ungetc(d, f);
		//ponder correspond à la ponderondération dans une liaison
		//direc1 correspond au terminus entre le premier et le deuxieme sommet
		//direc2 correspond au terminus entre le deuxieme et le premier sommet
		graphe.reseau[station1][station2].duree_entre_station = duree;
		graphe.reseau[station1][station2].terminus = term1;
		//le symétrique est aussi initialisé car les lignes de metro vont dans les 2 sens
		graphe.reseau[station2][station1].duree_entre_station = duree;
		graphe.reseau[station2][station1].terminus = term2;
	}
	fclose(f);
	printf("DONE\n");
	return graphe;
}

// Fonction rendu -- affiche dans le terminal le chemin a suivre pour arriver à bon port
// \param		graphe 			structure graphe
// \param		d 				structure DIJKSTRA
// \return						NULL
void ecrit_chemin(GRAPHE graphe, DIJKSTRA d)
{
	int h, m, s;
	h = d.duree_total/3600;
	m = d.duree_total/60;
	s = d.duree_total - (h * 3600 + m * 60);
	struct elem *p1 = d.chemin;
	struct elem *p2 = d.chemin->suiv;
	struct elem *temp;
	printf("- Station de depart : %s.\n", graphe.station[d.rang_deb].nom_station);
	printf("- Station d'arrivee : %s.\n", graphe.station[d.rang_fin].nom_station);
	if(graphe.station[d.rang_deb].num_sommet == graphe.station[d.rang_fin].num_sommet){
		printf(" >> Vous etes déjà à destination (%s)\n", graphe.station[d.rang_fin].nom_station);
		ecrit_duree_trajet(graphe, d, 0, 0, 0);
	}

	while (!teste_liste_vide(p2)) {
		if ((graphe.reseau[p1->s.num_sommet][p2->s.num_sommet].terminus != NOEUD) && ((p1->s.num_sommet) == d.rang_deb)) 
		{
			switch(p1->s.num_ligne)
			{
				case(30):
					printf("- Prenez la ligne 3bis\n");
					break;
				case(70):
					printf("- Prenez la ligne 7bis\n");
					break;
				default:
					printf("prenez la ligne %d\n", p1->s.num_ligne);
					break;
			}
		}
		
		//si on change de ligne
		if (graphe.reseau[p1->s.num_sommet][p2->s.num_sommet].terminus == NOEUD)
		{
			printf("- A %s, prenez la ligne ", p1->s.nom_station);

			if (p1->s.num_ligne == 30) printf("3bis");
			else if (p1->s.num_ligne == 70) printf("7bis");
			else printf("%d ", p1->s.num_ligne);

			printf("Jusqu'a %s\n", p2->s.nom_station);

			// if (p2->s.num_sommet != d.rang_fin) {
			// 	temp = p2->suiv;
			// 	//printf("direction : %s", graphe.station[graphe.reseau[p2->s.num_sommet][temp->s.num_sommet].terminus].nom_station);
			// 	printf("\n");
			// } else printf("\n");
		}
		p1 = p1->suiv;
		p2 = p2->suiv;
	}
	printf("Vous êtes arrivé a : %s\n", graphe.station[d.rang_fin].nom_station);
	ecrit_duree_trajet(graphe, d, h, m, s);
}

// Fonction duree -- affiche la durée total du projet
// \param		graphe 			structure GRAPHE
// \param		d 				structure DIJKSTRA
// \param		heure			le nombre d'heures du trajet
// \param		minute			le nombre de minutes du trajet
// \param		seconde			le nombre de secondes du trajet
// \return						GRAPHE
void ecrit_duree_trajet(GRAPHE graphe, DIJKSTRA d, int heure, int minute, int seconde){
	printf("- Duree total du trajet : %d heure(s), %d minute(s), %d seconde(s)\n", heure, minute, seconde);
}