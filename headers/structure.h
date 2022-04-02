/**
 * @file structure.h
 * @author Valentin Gardel (valentin.gardel@ensiie.fr)
 * @brief Interface pour gérer le plateau de jeu et le déroulement de la partie
 * @version 0.1
 * @date 2022-04-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _STRUCTURE_H
#define _STRUCTURE_H
#include "carte.h"
#include "faction.h"

/**
 * @brief type concret pour le plateau de jeu
 * 
 */

typedef Carte Plateau_jeu[129][129];

/**
 * @brief Structure pour les couples de factions
 * 
 */

struct Factions_en_jeu {
  Faction left;
  Faction right;
};

/**
 * @brief Alias pour les couples de factions
 * 
 */

typedef struct Factions_en_jeu Factions_en_jeu;

/**
 * @brief Structure pour stocker les coordonnées d'une carte sur la grille 2D
 * 
 */

struct Coord {
  int i;
  int j;
};

/**
 * @brief Alias pour les coordonnées d'une carte
 * 
 */

typedef struct Coord Coord;


/**
 * @brief type concret pour la main d'une faction
 * 
 */

typedef Carte Main[8];

/**
 * @brief type abstrait pour la pioche d'une faction
 * 
 */

typedef struct s_pioche *Pioche;

/**
 * @brief Savoir si une faction a itilisé l'option de remélanger sa main et boîte à idée et de repiocher des cartes.
 * @param f une faction
 * @return 0 si la main n'a pas été remélangé 
 * @return 1 si la main a été remélangé
 */

Pioche creation_pioche_vide();

/**
 * @brief indique si la pioche est vide ou non
 * @param p une pioche valide
 * @return 0 si la pioche n'est pas vide
 * @return 1 si la pioche est vide
 */

int pioche_est_vide(Pioche p);

/**
 * @brief ajoute la carte à la pioche au sommet de celle-ci
 * @param p une pioche valide
 * @param c une carte valide
 */

void ajout_pioche(Pioche p, Carte c);

/**
 * @brief enlève la carte au sommet de la pioche (on suppose la pioche non vide)
 * @param p une pioche valide
 * @return la carte qui a été retirée
 */

Carte enleve_pioche(Pioche p);

#endif // STRUCTURE_H
