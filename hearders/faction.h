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

/*****************************************
 * Prototypes des fonctions
 ****************************************/

/**
 * @brief Savoir si une faction a itilisé l'option de remélanger sa main et boîte à idée et de repiocher des cartes.
 * @param f une faction
 * @return 0 si la main n'a pas été remélangé 
 * @return 1 si la main a été remélangé
 */

int a_remelange(Faction f);

/**
 * @brief Permet à une faction de vider sa main, 
 * vider sa pioche et repiocher ses cartes
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

#endif