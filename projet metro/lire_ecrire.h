
// lire_ecrire.h du projet Metro
// Contient les signatures des fonctions de lire_ecrire.c

#include "types.h"
#include "graphe.h"

#ifndef __LIRE_ECRIRE_H
#define __LIRE_ECRIRE_H

int compte_nb_sommets(char *nomFichier);
GRAPHE initialise_stations(char *nomFichier, GRAPHE g);
GRAPHE initialise_reseau(char *nomFichier, GRAPHE g);
void ecrit_chemin(GRAPHE g, DIJKSTRA d);

#endif