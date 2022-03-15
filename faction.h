/**
 * @file faction.h
 * @author Nour ELBESSI
 * @brief  Interface faction : interface en charge 
 * des informations et des manipulations propre d'une faction.
 * @date 2022-03-07
 */

#ifndef FACTION_H
#define FACTION_H

#include "carte.h"

// Déclaration de faction (type abstrait)
typedef struct StructureFactions *Faction;

//Les prototypes des fonctions de faction.c
// extern LISTE_T uneVariableListeGlobale;

void a_remelange();
//une fonction permettant à une faction d'utiliser l'option ci-dessus.

void vider_sa_main(StructureCarte tab_carte[]);
void melanger_pioche(StructureCarte tab_carte[], int n);
void repiocher(StructureCarte tab_carte[]);

#endif