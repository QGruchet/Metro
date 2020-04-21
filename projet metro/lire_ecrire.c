
// lire_ecrire.c du projet Metro
// Contient les fonctions relatives à la lecture de metro.txt et à l'écriture dans le terminal

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lire_ecrire.h"
#include "graphe.h"

#include "types.h"

// Fonction qui compte le nombre de sommets dans le fichier (nom en argument)
int compte_nb_sommets(char *nomFichier)
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
	return i;
}

// Fonction qui lit le fichier nomFichier et remplit la structure GRAPHE
GRAPHE initialise_stations(char *nomFichier, GRAPHE graphe)
{
	printf("Recuperations des infos sur les stations...");
	FILE *f = fopen(nomFichier, "r");
	char c =' ';
	int num_station;
	int num_ligne;
	int i = 0;
	int j = 0;
	graphe.station = malloc(sizeof(SOMMET) * 375);

	while (i < 3) {		//on lit les 3 premières lignes qui ne sont que des commentaires
		c = fgetc(f);
		if (c == '\n')
			i++;
	}
	//pour chaque sommet, on lit son numero de sommet, son numero de ligne, et son nom
	//chaque sommet correspond à une station d'une ligne
	//Attention: on peut avoir plusieurs stations avec le même nom (pas la même ligne)
	for (int h = 0; h < graphe.nb_sommets - 1; h++) {
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

/*SOMMET initialise_sommet(char* nomFichier, int n){
	SOMMET s;
	int tmp;

	FILE *f = fopen(nomFichier, 'r');
	for(int i = 0; i < 375; ++i){
		tmp = fgetc(f);
		if(i == n){

		}
	}

}*/

// Fonction qui lit le fichier nomFichier et initialise les arcs entre les sommets
GRAPHE initialise_reseau(char *nomFichier, GRAPHE graphe)
{
	printf("Initialisations du reseaux du Metropolitain...");
	FILE *f = fopen(nomFichier, "r");
	char c, d = ' ';
	graphe.reseau = malloc(sizeof(ARC) * 375);
	for (int i = 0; i < 1000; ++i)
	{
		graphe.reseau[i] = calloc(375, sizeof(ARC*));
	}

	while (d != 'E') {	//on lit jusqu'à lire le 'E' signifiant le début des arcs
		c = fgetc(f);
		if (c == '\n')
			d = fgetc(f);
	}
	d = ungetc(d, f);
	int test = 0;
	int station1, station2, ponder, term1, term2;
	int i, j;
	//on met d'abord aucun terminus et aucun arc entre chaque sommet
	//comme ça les sommets avec les mêmes noms n'auront pas de terminus car c'est juste un changement de ligne
	for (i = 0; i < graphe.nb_sommets; i++) {
		for (j = 0; j < graphe.nb_sommets; j++) {
			graphe.reseau[i][j].terminus = PAS_DE_TERMINUS;
			graphe.reseau[i][j].ponderation = AUCUN_ARC;
		}
	}
	while (test != 1) {	//on lit le fichier jusqu'à la fin
		fscanf(f, "%c %d %d %d %d %d ", &c, &station1, &station2, &ponder,
		       &term1, &term2);
		d = fgetc(f);
		if (d == EOF)
			test = 1;
		d = ungetc(d, f);
		//ponder correspond à la ponderondération dans un arc
		//direc1 correspond au terminus entre le premier et le deuxieme sommet
		//direc2 correspond au terminus entre le deuxieme et le premier sommet
		graphe.reseau[station1][station2].ponderation = ponder;
		graphe.reseau[station1][station2].terminus = term1;
		//le symétrique est aussi initialisé car les lignes de metro vont dans les 2 sens
		graphe.reseau[station2][station1].ponderation = ponder;
		graphe.reseau[station2][station1].terminus = term2;
	}
	fclose(f);
	printf("DONE\n");
	return graphe;
}

// Fonction qui calcule le nombre d'heures en fonction d'une durée
int calcul_heures(int duree)
{
	return duree / 3600;
}

// Fonction qui calcule le nombre de minutes en fonction d'une durée
int calcul_minutes(int duree)
{
	return duree / 60;
}

// Fonction qui écrit le plus court chemin entre les 2 sommets sélectionnés dans le terminal
void ecrit_chemin(GRAPHE graphe, DIJKSTRA d)
{
	int h, m, s;
	h = calcul_heures(d.duree);
	m = calcul_minutes(d.duree - h);
	s = d.duree - (h * 3600 + m * 60);
	struct elem *p1 = d.chemin;
	struct elem *p2 = d.chemin->suiv;
	struct elem *temp;
	printf("- Station de depart : %s.\n", graphe.station[d.rang_deb].nom_station);
	printf("- Station d'arrivee : %s.\n", graphe.station[d.rang_fin].nom_station);
	while (!teste_liste_vide(p2)) {
		if ((graphe.reseau[p1->s.num_sommet][p2->s.num_sommet].terminus != PAS_DE_TERMINUS) && ((p1->s.num_sommet) == d.rang_deb)) 
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
			// if (p1->s.num_ligne == 30)
			// 	printf("- Prenez la ligne 3bis");
			// else if (p1->s.num_ligne == 70)
			// 	printf("- Prenez la ligne 7bis");
			// else
			// 	printf("- Prenez la ligne %d", p1->s.num_ligne);

			// printf(" direction %s. \n", graphe.station[graphe.reseau[p1->s.num_sommet][temp->s.num_sommet].terminus].nom_station);
		}
		//si on change de ligne
		if (graphe.reseau[p1->s.num_sommet][p2->s.num_sommet].terminus == PAS_DE_TERMINUS)
		{
			printf("- A %s, prenez la ligne ", p1->s.nom_station);

			if (p1->s.num_ligne == 30) printf("3bis");
			else if (p1->s.num_ligne == 70) printf("7bis");
			else printf("%d ", p1->s.num_ligne);

			if (p2->s.num_sommet != d.rang_fin) {
				temp = p2->suiv;
				printf("direction %s.\n", graphe.station[graphe.reseau[p2->s.num_sommet][temp->s.num_sommet].terminus].nom_station);
			} else printf("\n");
		}
		p1 = p1->suiv;
		p2 = p2->suiv;
	}
	//écrit le temps qu'il faut pour aller entre 2 sommets
	printf("- Vous devriez arriver à %s dans ",
	       graphe.station[d.rang_fin].nom_station);
	if (h > 1)
		printf("%d heures ", h);
	else if (h == 1)
		printf("%d heure ", h);
	if (m > 1)
		printf("%d minutes ", m);
	else if (m == 1)
		printf("%d minute ", m);
	if (s > 1)
		printf("%d secondes.\n", s);
	else if (s == 1)
		printf("%d seconde.\n", s);
	printf("------------------------------------------------------------");
	printf("\n\n");
}