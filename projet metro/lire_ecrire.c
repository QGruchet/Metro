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
	printf("  Initialisations du nombres de stations...");
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
	printf("  Recuperations des infos sur les stations...");
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

// Fonction GRAPHE -- compte le nombre de liaisons total dans le graphe
// \param		*nomFichier		nom du fichier a ouvrir
// \return						nombre total de liaisons
int compte_nb_liaison(char* nomFichier){
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
	while(d != EOF)
	{
		c = fgetc(f);
		if (c == '\n') {
			d = fgetc(f);
			if (d == 'E') {
				i++;
			}
		}
	}
	fclose(f);
	return i;
}

// Fonction GRAPHE -- remplie la structure GRAPHE avec toutes les liaisons entre stations
// \param		*nomFichier		nom du fichier a ouvrir
// \param		 graphe 		structure a remplir
// \return						GRAPHE
GRAPHE initialise_reseau(char *nomFichier, GRAPHE graphe)
{
	printf("  Initialisations du reseaux du Metropolitain...");
	FILE *f = fopen(nomFichier, "r");
	char c, d = ' ';
	int nb_liaisons_tot = compte_nb_liaison(nomFichier);

	graphe.reseau = malloc(sizeof(LIAISON*)*nb_liaisons_tot);
	for (int i = 0; i < nb_liaisons_tot; ++i)
	{
		graphe.reseau[i] = malloc(sizeof(LIAISON) * nb_liaisons_tot);
	}

	while (d != 'E') {	//on lit jusqu'au ligne commencant par E
		c = fgetc(f);
		if (c == '\n')
			d = fgetc(f);
	}
	d = ungetc(d, f);
	int test = 0;
	int station1, station2, duree, term1, term2;
	int i, j;

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

		graphe.reseau[station1][station2].duree_entre_station = duree;
		graphe.reseau[station1][station2].terminus = term1;

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
	if(graphe.station[d.rang_deb].num_sommet == graphe.station[d.rang_fin].num_sommet){
		printf(" >> Vous etes déjà à destination (%s).\n", graphe.station[d.rang_fin].nom_station);
		ecrit_duree_trajet(graphe, d, 0, 0, 0);
	}

	while (!teste_liste_vide(p2)) {
		if ((graphe.reseau[p1->s.num_sommet][p2->s.num_sommet].terminus != NOEUD) && ((p1->s.num_sommet) == d.rang_deb)) 
		{
			switch(p1->s.num_ligne)
			{
				case(30):
					printf("- Prenez la ligne 3bis direction %s.\n", graphe.station[graphe.reseau[p1->s.num_sommet][p2->s.num_sommet].terminus].nom_station);
					break;
				case(70):
					printf("- Prenez la ligne 7bis direction %s.\n", graphe.station[graphe.reseau[p1->s.num_sommet][p2->s.num_sommet].terminus].nom_station);
					break;
				default:
					printf("- Prenez la ligne %d direction %s.\n", p1->s.num_ligne, graphe.station[graphe.reseau[p1->s.num_sommet][p2->s.num_sommet].terminus].nom_station);
					break;
			}
		}
		
		//si on change de ligne
		if (graphe.reseau[p1->s.num_sommet][p2->s.num_sommet].terminus == NOEUD )//&& p2->s.num_sommet != d.rang_fin)
		{
			printf("- A %s, prenez la ligne ", p1->s.nom_station);

			if (p2->s.num_ligne == 30) printf("3bis ");
			else if (p2->s.num_ligne == 70) printf("7bis ");
			else printf("%d ", p2->s.num_ligne);
			if (p2->s.num_sommet != d.rang_fin) {
				temp = p2->suiv;
				printf("direction %s.\n", graphe.station[graphe.reseau[p2->s.num_sommet][temp->s.num_sommet].terminus].nom_station);
			} 
			//else printf("Jusqu'a %s.\n", graphe.station[d.rang_fin].nom_station);
		}
		p1 = p1->suiv;
		p2 = p2->suiv;
	}
	printf("  Vous devriez arrivé a %s dans ", graphe.station[d.rang_fin].nom_station);
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
	printf("%d heure(s), %d minute(s), %d seconde(s).\n", heure, minute, seconde);
}