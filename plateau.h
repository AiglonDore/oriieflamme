/**
 * @file plateau.h
 * @author Valentin Gardel (valentin.gardel@ensiie.fr)
 * @brief Interface pour gérer le plateau de jeu et le déroulement de la partie
 * @version 0.1
 * @date 2022-03-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _PLATEAU_H
#define _PLATEAU_H
#include "carte.h"
#include "faction.h"

/**
 * @brief type concret pour les listes de factions
 * 
 */

struct Factions_en_jeu {
  Faction left;
  Faction right;
};

typedef struct Factions_en_jeu Factions_en_jeu;

/**
 * @brief type abstrait pour le plateau de jeu
 * 
 */

typedef struct s_plateau * Plateau;

/**
 * @brief crée un plateau et les deux factions qui joueront dessuss
 * @return le plateau initialisé
 * 
 */

Plateau init_plateau();

/**
 * @brief libère la mémoire associée au plateau de jeu et aux deux factions
 * @param p plateau valide (le pointeur doit être valide)
 * 
 */

void libere_plateau(Plateau p);

/**
 * @brief initialise une nouvelle manche ou indique que le jeu est terminé
 * @param p plateau valide (le pointeur doit être valide)
 * @return 0 si la partie continue, 1 si le jeu est terminé
 * 
 */

int nouvelle_manche(Plateau p);

/**
 * @brief renvoie la liste des deux factions du jeu
 * @param p plateau valide (le pointeur doit être valide)
 * @return la liste des des factions du jeu
 * 
 */

Factions_en_jeu factions_plateau(Plateau p);

/**
 * @brief permet à une faction de poser une carte face cachée sur le plateau
 * @param c carte valide
 * @param p plateau valide (le pointeur doit être valide)
 * @param i position en abscisse dans le plateau souhaitée pour la carte
 * @param j position en ordonnée dans le plateau souhaitée pour la carte
 * 
 */

void poser_carte(Carte c, Plateau p, int i, int j);

/**
 * @brief permet à une faction de retourner une carte face visible et activer son effet
 * @param c carte valide
 * @param p plateau valide (le pointeur doit être valide)
 * 
 */

void retourner_carte(Carte c, Plateau p);

#endif // PLATEAU_H
