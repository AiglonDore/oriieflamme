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

/**************************************************
 * Création des prototypes des getters et setters
 ***************************************************/

/**
 * @brief Prototype de get_nom qui permet de récupérer le nom de la faction
 *
 * @param f
 * @return char*
 */

char *get_nom_faction(Faction f);

/**
 * @brief Prototype de set_nom qui permet d'initialiser le nom de la faction
 *
 * @param f
 * @param nom_faction
 */
void set_nom_faction(Faction f, char *nom_faction);

/**
 * @brief Prototype de get_nb_manches_gagnees qui permet de récupérer le nombre de manches gagnées d'une faction
 *
 * @param f
 * @return int
 */
int get_nb_manches_gagnees(Faction f);

/**
 * @brief Prototype de set_nb_manches_gagnees qui permet d'initialiser le nombre de manches gagnées d'une faction
 *
 * @param f
 * @param x
 */
void set_nb_maches_gagnees(Faction f, int x);

/**
 * @brief Prototype de get_pts_DDRS_manche qui permet de récupérer le nombre de points DDRS de la manche en cours d'une faction
 *
 * @param f
 * @return int
 */
int get_pts_DDRS_manche(Faction f);

/**
 * @brief Prototype de set_pts_DDRS_manche qui permet d'initialiser le nombre de points DDRS de la manche en cours d'une faction
 *
 * @param f
 * @param x
 */
void set_pts_DDRS_manche(Faction f, int x);

/**
 * @brief Prototype de get_a_remelange qui permet de récupérer un entier qui indique si la faction a utilisé son option ou pas.
 *
 * @param f
 * @return int
 */
int get_a_remelange(Faction f);

/**
 * @brief Prototype de set_a_remelange qui permet d'initialiser si la faction a utilisé ou non son option
 *
 * @param f
 * @param x
 */
void set_a_remelange(Faction f, int x);

/**
 * @brief Prototype de get_carte_anl_retournee qui permet de récupérer un entier qui indique si la faction a retourné sa carte Anne-Laure Ligozat ou non.
 *
 * @param f
 * @return int
 */
int get_carte_anl_retournee(Faction f);

/**
 * @brief Prototype de set_carte_anl_retournee qui permet d'initialiser si la faction a retourné sa carte Anne-Laure Ligozat ou non.
 *
 * @param f
 * @param x
 */
void set_carte_anl_retournee(Faction f, int x);

/**
 * @brief Prototype de get_main qui permet de récupérer la main de la faction
 *
 * @param f
 * @return Carte *
 */

Carte *get_main(Faction f);

/**
 * @brief Prototype de set_main qui permet d'initialiser la main de la faction
 *
 * @param f
 * @param main
 */

void set_main(Faction f, Carte *main);

/**
 * @brief Prototype de get_pioche qui permet de récupérer la pioche de la faction
 *
 * @param f
 * @return Pioche
 */

Pioche get_pioche(Faction f);

#endif