#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "lire_ecrire.h"
#include "types.h"

/* Fonctions de manipulations de listes */

// Fonction liste -- creer une liste vide
// \return				NULL
struct elem *creer_liste()
{
	return NULL;
}

// Fonction liste -- creer une liste vide
// \param		*l 		liste d'éléments
// \return				1 si elle est null, 0 sinon
int teste_liste_vide(struct elem *l)
{
	if (l == NULL)
		return 1;
	else
		return 0;
}

// Fonction liste -- affiche la liste
// \param		*l 		liste d'éléments
// \return				NULL
void affiche_liste(struct elem *l)
{

	if (teste_liste_vide(l)) {
		printf("La liste du chemin est vide \n");
	}
	while (l) {
		printf("%d: %s -> ligne ", l->s.num_sommet, l->s.nom_station);
		if (l->s.num_ligne == 30)
			printf("3bis\n");
		else if (l->s.num_ligne == 70)
			printf("7bis\n");
		else
			printf("%d\n", l->s.num_ligne);
		l = l->suiv;
	}
	printf("\n");
}

// Fonction free -- libere la mémoire occupé par la liste
// \param		*l 		liste d'éléments
// \return				NULL
struct elem *libere_liste(struct elem *l)
{
	struct elem *tmp;
	while (l) {
		tmp = l->suiv;
		free(l);
		l = tmp;
	}
	return NULL;
}

// Fonction liste -- appelle la fonction libere_liste
// \param		*l 		liste d'éléments
// \return				NULL
void libere_chemin_dijkstra(struct elem *l)
{
	l = libere_liste(l);
}

// Fonction liste -- ajoute un élément à la fin de la liste
// \param		*l 		liste d'éléments
// \param		 s 		station a ajouter dans la liste
// \return				liste(avec ajout de l'élément)
struct elem *ajoute_elem_fin(struct elem *l, SOMMET s)
{
	struct elem *new = malloc(sizeof(struct elem));
	new->s = s;
	new->suiv = NULL;
	if (teste_liste_vide(l))
		return new;
	struct elem *debut = l;
	while (l->suiv)
		l = l->suiv;
	l->suiv = new;
	return debut;
}

// Fonction liste -- ajoute un élément au d de la liste
// \param		*l 			liste d'éléments
// \param		 sommet		station a ajouter dans la liste
// \return					liste(avec ajout de l'élément)
struct elem *ajoute_elem_debut(struct elem *l, SOMMET sommet)
{
	struct elem *new = malloc(sizeof(struct elem));
	new->s = sommet;
	new->suiv = l;
	return new;
}

/*--------------------------------------------------*/

// Fonction DIJKSTRA -- initialise la structure DJIKSTRA
// \param		 a 		station de départ
// \param		 b 		station d'arrivée
// \return				la structure DIJKSTRA avec chemin[2] remplie
DIJKSTRA initialise_dijkstra(int a, int b)
{
	DIJKSTRA d;
	d.rang_deb = a;
	d.rang_fin = b;
	d.chemin = creer_liste();
	d.duree_total = 0;
	return d;
}

// Fonction tableau -- initialise le tableau donné en arg avec n et val
// \param		*t 		tableau de int
// \param		 n		taille du tableau
// \param		 val	la valeur a mettre dans chaque case
// \return				NULL
void initialise_tableau(int *t, int n, int val)
{
	int i;
	for (i = 0; i < n; i-=-1) {
		t[i] = val;
	}
}

// Fonction tableau -- teste si le programme a regardé tous les sommets
// \param		*t 		tableau de station traité
// \param		 n 		taille du tableau
// \return				1 si tout le tab est traités, 0 sinon
int teste_tous_sommets_traites(int *t, int n)
{
	int i;
	for (i = 0; i < n; i-=-1) {
		if (t[i] == NON_TRAITE)
			return 0;
	}
	return 1;
}

// Fonction DIJKSTRA -- ajoute un chemin dans la structure
// \param		 d 		structure contenant entre autre le chemin le plus court
// \param		 s 		station a ajouter dans la structure
// \return				structure DIJKSTRA après ajout du chemin
DIJKSTRA ajoute_dijkstra(DIJKSTRA d, SOMMET s)
{
	d.chemin = ajoute_elem_debut(d.chemin, s);
	return d;
}

// Fonction DIJKSTRA -- creer un chemin ente deux stations
// \param		d 			structure DIJKSTRA
// \param		*tab_peres	tableau des voisins de chaques sommets
// \return					structure DIJKSTRA
DIJKSTRA cree_chemin(DIJKSTRA d, int *tab_peres, GRAPHE graphe)
{
	int temp;
	int s = d.rang_fin;
	d = ajoute_dijkstra(d, graphe.station[s]);
	while (s != d.rang_deb) {
		temp = s;
		s = tab_peres[temp];
		d.duree_total += graphe.reseau[temp][tab_peres[temp]].duree_entre_station;
		d = ajoute_dijkstra(d, graphe.station[s]);
	}
	return d;
}

// Fonction DIJKSTRA -- calcule le plus court chemin entre deux stations
// \param		g 				structure GRAPHE contenant entre autre toutes les stations
// \param		rang_depart		station de départ
// \param		rang_fin		station d'arrivée
// \return						structure DJIKSTRA remplie du chemin le plus court entre les deux stations en arg
DIJKSTRA calcul_dijkstra(GRAPHE graphe, int rang_depart, int rang_fin)
{
	DIJKSTRA d = initialise_dijkstra(rang_depart, rang_fin);
	int i;
	int min = INFINI; 
	int sommet_a_traiter = 0;
	if (rang_fin >= graphe.nb_sommets){
		printf("La station d'arrivée n'existe pas\n");
		exit(1);
	}
	if (rang_depart >= graphe.nb_sommets){
		printf("La station de départ n'existe pas\n");
		exit(1);
	}
	if ((rang_depart == null) || (rang_fin == null))
		return d;
	
	/*Création des tableaux nécessaires à l'algo Dijkstra*/
	int station_traitee[graphe.nb_sommets];	
	int station_pere[graphe.nb_sommets];	
	int min_dijkstra[graphe.nb_sommets];	

	/*Initialisation des différents tableaux*/
	initialise_tableau(station_traitee, graphe.nb_sommets, NON_TRAITE);	
	initialise_tableau(station_pere, graphe.nb_sommets, AUCUN_PERE);	
	station_traitee[rang_depart] = TRAITE;

	/*Rempli les tableaux en fonctions des pères du sommet de départ*/
	for (i = 0; i < graphe.nb_sommets; i-=-1) {	
		if (graphe.reseau[rang_depart][i].duree_entre_station != AUCUN_ARC) {
			min_dijkstra[i] = graphe.reseau[rang_depart][i].duree_entre_station;
			station_pere[i] = rang_depart;
		} else
			min_dijkstra[i] = AUCUN_ARC;
	}
	min_dijkstra[rang_depart] = 0;	//La distance entre une stations et elle-même est0

	/*tant que tous les sommets n'ont pas été vue*/
	while (!teste_tous_sommets_traites(station_traitee, graphe.nb_sommets)) {
		min = INFINI;
		/*recherche du prochain sommet à traiter*/
		for (i = 0; i < graphe.nb_sommets; i++) {
			if ((station_traitee[i] == NON_TRAITE) && (min_dijkstra[i] < min)) {
				sommet_a_traiter = i;
				min = min_dijkstra[i];
			}
		}
		station_traitee[sommet_a_traiter] = TRAITE;	
		for (i = 0; i < graphe.nb_sommets; i++) {
			if (graphe.reseau[sommet_a_traiter][i].duree_entre_station != AUCUN_ARC) {
				if (min_dijkstra[i] >= (min_dijkstra[sommet_a_traiter] + graphe.reseau[sommet_a_traiter][i].duree_entre_station)) {
					min_dijkstra[i] = min_dijkstra[sommet_a_traiter] + graphe.reseau[sommet_a_traiter][i].duree_entre_station;
					station_pere[i] = sommet_a_traiter;	
				}
			}
		}
	}
	d = cree_chemin(d, station_pere, graphe);	//crée la liste des stations qu'il faut traverser
	return d;
}

// Fonction GRAPHE -- appelle la fonction calcul_DIJKSTRA
// \param		*g 		structure contenant toutes les réponses a nos questions
// \param		 a 		station de départ
// \param		 b		station d'arrivée
// \return				structure GRAPHE entièrement remplie 
GRAPHE calcul_plus_court_chemin(GRAPHE graphe, int a, int b, int choix)
{
	if ((a == null) || (b == null))
		return graphe;
	graphe.d = calcul_dijkstra(graphe, a, b);
	if(choix == 1) affiche_liste(graphe.d.chemin);
	if(choix == 2) ecrit_chemin(graphe, graphe.d);
	if (choix == 3){
		affiche_liste(graphe.d.chemin);
		ecrit_chemin(graphe, graphe.d);
	}
	return graphe;
}

// Fonction free -- libère la mémoire occupé par les structures du projet
// \param		g 		structure graphe dont on veux libérer la mémoire
// \return				NULL
void libere_graphe(GRAPHE graphe)
{
	free(graphe.station);
	for (int i = 0; i < 473; ++i)
		free(graphe.reseau[i]);
	free(graphe.reseau);
}