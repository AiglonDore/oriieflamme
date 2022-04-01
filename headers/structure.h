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

struct Coord_carte {
  int i;
  int j;
};

/**
 * @brief Alias pour les coordonnées d'une carte
 * 
 */

typedef struct Coord_carte Coord_carte;

/**
 * @brief type abstrait pour la pioche d'une faction
 * 
 */

typedef struct s_pioche *Pioche;

/**
 * @brief type concret pour la main d'une faction
 * 
 */

typedef Carte Main[8];

#endif // STRUCTURE_H
