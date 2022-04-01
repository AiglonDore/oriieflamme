/**
 * @file plateau.c
 * @author Nour Elbessi & Valentin Gardel
 * @brief Implantation de l'interface en charge des informations et des manipulations propres à une faction
 * @version 0.1
 * @date 2022-03-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../headers/plateau.h"
#include "../headers/carte.h"
#include "../headers/faction.h"
#include "../headers/structure.h"

/**
 * @brief type concret pour la faction
 *
 */
typedef struct StructureFactions
{
    char *nom;
    int nb_manches_gagnees;
    int pts_DDRS_manche;
    Pioche pioche;
    Main main;
};

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