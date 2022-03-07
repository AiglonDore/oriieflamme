#ifndef INTERFACE_H
#define INTERFACE_H

#include "carte.h"
#include "faction.h"
#include "plateau.h"

/**
 * @brief Fonction qui affiche le plateau de jeu
 * @param p plateau de jeu (pointeur devant être valide)
 * @return rien
 * @author Thomas Roiseux
 */
void affiche_plateau(Plateau p);

/**
 * @brief Fonction qui affiche la main de la faction pointée par f
 * @return rien
 * @param f faction en jeu
 * @author Thomas Roiseux
 */
void affiche_main(Faction f);

#endif //INTERFACE_H