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

const int nb_maches_gagnantes = 2;

/**
 * @brief type abstrait pour le plateau de jeu
 *
 */

typedef struct s_plateau *Plateau;

/**
 * @brief crée la pioche avec les 32 cartes de l'énoncé pour la faction donnée
 * @param f faction valide (le pointeur doit être valide)
 *
 */

void init_pioche(Faction f);

/**
 * @brief crée un plateau et les deux factions qui joueront dessus
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
 * @return 1 si la partie continue, 0 si le jeu est terminé
 *
 */

int nouvelle_manche(Plateau p);

/**
 * @brief détermine la faction qui joue en premier et renvoie la liste des deux factions du jeu dont le premier élément est la faction qui joue en premier
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

/**************************************************
 * Création des prototypes des getters et setters
 ***************************************************/

/**
 * @brief Prototype de get_plateau_jeu.
 *
 * @param p
 * @return Plateau_jeu
 */
Plateau_jeu get_plateau_jeu(Plateau p);

/**
 * @brief Prototype de get_factions qui permet de récupérer les factions en jeu.
 *
 * @param p
 * @return Factions_en_jeu
 */
Factions_en_jeu get_factions(Plateau p);

/**
 * @brief Prototype de get_derniere_carte_posee.
 *
 * @param p
 * @return Coord
 */
Coord get_derniere_carte_posee(Plateau p);

/**
 * @brief Prototype de get_derniere_carte_retournee.
 *
 * @param p
 * @return Coord
 */
Coord get_derniere_carte_retournee(Plateau p);

/**
 * @brief Prototype de get_avant_derniere_carte_retournee.
 *
 * @param p
 * @return Coord
 */
Coord get_avant_derniere_carte_retournee(Plateau p);

/**
 * @brief Prototype de get_carte_haut_gauche.
 *
 * @param p
 * @return Coord
 */
Coord get_carte_haut_gauche(Plateau p);

/**
 * @brief Prototype de get_carte_bas_droite.
 *
 * @param p
 * @return Coord
 */
Coord get_carte_bas_droite(Plateau p);

/**
 * @brief Prototype de get_numero_manche.
 *
 * @param p
 * @return int
 */
int get_numero_manche(Plateau p);

/**
 * @brief Prototype de get_cartes_retournees_manche.
 *
 * @param p
 * @return int
 */
int get_cartes_retournees_manche(Plateau p);

/**
 * @brief Prototype de get_cartes_non_retournees_manche.
 *
 * @param p
 * @return int
 */
int get_cartes_non_retournees_manche(Plateau p);

/**
 * @brief retourne la carte la plus en haut à gauche du plateau face visible et active son effet
 * @param p plateau valide (le pointeur doit être valide)
 * @return la carte que l'on a retourné face visible
 * @return NULL s'il n'y a plus aucune carte à retourner
 *
 */

Carte retourner_carte(Plateau p);

#endif // PLATEAU_H
