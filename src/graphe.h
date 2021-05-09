#include "def.h"

#ifndef __GRAPHE_H
#define __GRAPHE_H

typedef struct sommet {
	int num_sommet;			//< numéro du sommet dans metro.txt
	int num_ligne;			//< numéro de la ligne du sommet
	int nombre_nom;			//< nombre de lettres contenues dans le nom de la staion
	char nom_station[64];	//< nom de la station
} SOMMET;

typedef struct liaison {
	int terminus;				//< numéro du sommet du terminus, NOEUD si c'est un noeud
	int duree_entre_station;	//< durée de trajet entre deux stations
} LIAISON;

typedef struct dijkstra {
	int rang_deb;			//< numéro du sommet de départ
	int rang_fin;			//< numéro du sommet d'arrivée
	int duree_total;		//< durée total du trajet
	struct elem *chemin;	//< liste des stations parcouru
} DIJKSTRA;

typedef struct graphe {
	SOMMET chemin[2];		//< tableau contenant station d'arrivée et station de départ
	DIJKSTRA d;				//< contient le plus court chemin entre les stations
	int nb_sommets;			//< nombre total de sommet 
	SOMMET *station;		//< tableau des stations(sommet)
	LIAISON **reseau;		//< tableau des liaisons entre stations
} GRAPHE;

struct elem {	
	SOMMET s;
	struct elem *suiv;
};

int teste_liste_vide(struct elem *l);
void affiche_liste(struct elem *l);
struct elem *libere_liste(struct elem *l);
void libere_chemin_dijkstra(struct elem *l);

GRAPHE initialise_graphe(int n);
DIJKSTRA calcul_dijkstra(GRAPHE graphe, int rang_sommet_depart, int rang_fin);
GRAPHE calcul_plus_court_chemin(GRAPHE graphe, int a, int b, int choix);
void libere_graphe(GRAPHE graphe);

#endif