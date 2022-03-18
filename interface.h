/**
 * @file interface.h
 * @author Thomas Roiseux (thomas.roiseux@ensiie.fr)
 * @brief Interface entre le plateau de jeu et le joueur
 * @version 0.1
 * @date 2022-03-07
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include "carte.h"
#include "faction.h"
#include "plateau.h"

/**
 * @brief Structure de couples d'entiers.
 * 
 */
struct IntCouple {
    int left;
    int right;
};

/**
 * @brief Alias pour les structures de couple
 * 
 */
typedef struct IntCouple IntCouple;

/**
 * @brief Fonction qui affiche le plateau de jeu
 * @param p plateau de jeu (pointeur devant être valide)
 * @return rien
 */
void affiche_plateau(Plateau p);

/**
 * @brief Fonction qui affiche la main de la faction pointée par f
 * @return rien
 * @param f faction en jeu
 */
void affiche_main(Faction f);

/**
 * @brief Fonction qui demande si la faction pointée par f veut utiliser son option
 * @param f faction en jeu
 * @return 0 non
 * @return 1 oui
 */
int utiliser_option(Faction f);

/**
 * @brief Fonction qui demande la carte qui sera posée face cachée sur le plateau.
 * @param f faction en jeu
 * @return Carte carte choisie par la faction f et posée sur le plateau.
 */
Carte a_poser_face_cachee_sur_plateau(Faction f);

/**
 * @brief Affiche les effets de la carte c si elle est posée et retournée sur le plateau p.
 * @param p Plateau de jeu.
 * @param c Carte dont on veut afficher les effets
 */
void affiche_effets(Plateau p, Carte c);

/**
 * @brief Affiche le vainquer de la partie.
 * @param p Plateau de jeu.
 */
void affiche_vainqueur(Plateau p);

/**
 * @brief Fonction qui demande à quelle position doit être placée la carte
 * 
 * @param p Plateau de jeu.
 */
IntCouple demande_position(Plateau p);
#endif //INTERFACE_H