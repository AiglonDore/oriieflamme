/**
 * @file faction.h
 * @author Nour ELBESSI
 * @brief  Interface faction : interface en charge des informations et des manipulations propre d'une faction.
 * @date 2022-03-07
 */

#ifndef FACTION_H
#define FACTION_H

/**
 * @brief type abstrait pour la faction qu'on définira dans faction.c
 *
 */
typedef struct StructureFactions *Faction;

#include "structure.h"

/**
 * @brief Prototype de creation_faction qui permet d'initialiser une faction
 *
 * @return Faction
 */

Faction creation_faction();

/*****************************************
 * Prototypes des fonctions
 ****************************************/

/**
 * @brief Savoir si une faction a utilisé l'option de remélanger sa main et boîte à idée et de repiocher des cartes.
 * @param f une faction
 * @return 0 si la main n'a pas été remélangé
 * @return 1 si la main a été remélangé
 */

int a_remelange(Faction f);

/**
 * @brief Permet à une faction de vider sa main, mélanger sa pioche et repiocher ses cartes
 * @param f une faction
 */
void melanger(Faction f);

/**
 * @brief Permet à une faction de vider sa main
 * @param f une faction
 */
void vider_sa_main(Faction f);

/**
 * @brief Permet à une faction de mélanger sa pioche
 * @param f une faction
 */

void melanger_pioche(Faction f);

/**
 * @brief Permet à une faction de repiocher ses cartes
 * @param f une faction
 */
void piocher(Faction f);

/**
 * @brief Permet de supprimer une faction et de libérer son espace mémoire alloué
 * @param f une faction
 */
void supprimer_faction(Faction f);

/**************************************************
 * Création des prototypes des getters et setters
 ***************************************************/

/**
 * @brief Prototype de get_nom qui permet de récupérer le nom de la faction
 *
 * @param f Faction
 * @return Nom de la faction
 */

char *get_nom_faction(Faction f);

/**
 * @brief Prototype de set_nom qui permet d'initialiser le nom de la faction
 *
 * @param f Faction
 * @param nom_faction Nom de la faction
 */
void set_nom_faction(Faction f, char *nom_faction);

/**
 * @brief Prototype de get_nb_manches_gagnees qui permet de récupérer le nombre de manches gagnées d'une faction
 *
 * @param f Faction
 * @return Nombre de manches gagnées par la faction
 */
int get_nb_manches_gagnees(Faction f);

/**
 * @brief Prototype de set_nb_manches_gagnees qui permet d'initialiser le nombre de manches gagnées d'une faction
 *
 * @param f Faction
 * @param x Nombre de manches gagnées par la faction
 */
void set_nb_manches_gagnees(Faction f, int x);

/**
 * @brief Prototype de get_pts_DDRS_manche qui permet de récupérer le nombre de points DDRS de la manche en cours d'une faction
 *
 * @param f Faction
 * @return Nombre de points DDRS de la faction pour la manche en cours
 */
int get_pts_DDRS_manche(Faction f);

/**
 * @brief Prototype de set_pts_DDRS_manche qui permet d'initialiser le nombre de points DDRS de la manche en cours d'une faction
 *
 * @param f Faction
 * @param x Nombre de points DDRS de la faction pour la manche en cours
 */
void set_pts_DDRS_manche(Faction f, int x);

/**
 * @brief Prototype de get_a_remelange qui permet de récupérer un entier qui indique si la faction a utilisé son option ou pas.
 *
 * @param f Faction
 * @return Vaut 1 si la faction a déjà utilisé son joker dans le jeu, 0 sinon
 */
int get_a_remelange(Faction f);

/**
 * @brief Prototype de set_a_remelange qui permet d'initialiser si la faction a utilisé ou non son option
 *
 * @param f Faction
 * @param x Vaut 1 si la faction a déjà utilisé son joker dans le jeu, 0 sinon
 */
void set_a_remelange(Faction f, int x);

/**
 * @brief Prototype de get_main qui permet de récupérer la main de la faction
 *
 * @param f Faction
 * @return Main de la faction
 */

Carte *get_main(Faction f);

/**
 * @brief Prototype de set_main qui permet d'initialiser la main de la faction
 *
 * @param f Faction
 * @param main Main de la faction
 */

void set_main(Faction f, Carte *main);

/**
 * @brief Prototype de set_pioche qui permet d'initialiser la pioche de la faction
 *
 * @param f Faction
 * @param p Pioche de la faction
 */

void set_pioche(Faction f, Pioche p);

#endif