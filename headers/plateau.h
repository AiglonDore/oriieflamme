/**
 * @file plateau.h
 * @author Nour Elbessi & Valentin Gardel
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
#include "structure.h"

/**
 * @brief type abstrait pour le plateau de jeu
 *
 */
typedef struct s_plateau *Plateau;

/**
 * @brief Prototype de creation_plateau qui permet d'initialiser une carte.
 *
 * @return Plateau
 */

Plateau creation_plateau();

/**************************************************
 * Création des prototypes des getters et setters
 ***************************************************/

/**
 * @brief Prototype de get_carte_at.
 *
 * @param p
 * @param i coordonnée horizontale de la carte souhaitée
 * @param j coordonnée verticale de la carte souhaitée
 * @return Carte
 */
Carte get_carte_at(Plateau p, int i, int j);

/**
 * @brief Prototype de get_factions qui permet de récupérer les factions en jeu.
 *
 * @param p
 * @return Factions_en_jeu
 */
Factions_en_jeu get_factions(Plateau p);

/**
 * @brief Prototype de get_coord_derniere_carte_posee.
 *
 * @param p
 * @return Coord
 */
Coord get_coord_derniere_carte_posee(Plateau p);

/**
 * @brief Prototype de get_coord_derniere_carte_retournee.
 *
 * @param p
 * @return Coord
 */
Coord get_coord_derniere_carte_retournee(Plateau p);

/**
 * @brief Prototype de get_coord_avant_derniere_carte_retournee.
 *
 * @param p
 * @return Coord
 */
Coord get_coord_avant_derniere_carte_retournee(Plateau p);

/**
 * @brief Prototype de get_derniere_carte_retournee.
 *
 * @param p
 * @return Carte
 */
Carte get_derniere_carte_retournee(Plateau p);

/**
 * @brief Prototype de get_avant_derniere_carte_retournee.
 *
 * @param p
 * @return Carte
 */
Carte get_avant_derniere_carte_retournee(Plateau p);

/**
 * @brief Prototype de get_coord_carte_haut_gauche.
 *
 * @param p
 * @return Coord
 */
Coord get_coord_carte_haut_gauche(Plateau p);

/**
 * @brief Prototype de get_coord_carte_bas_droite.
 *
 * @param p
 * @return Coord
 */
Coord get_coord_carte_bas_droite(Plateau p);

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
 * @brief Prototype de get_colonne_gauche.
 *
 * @param p
 * @return int
 */
int get_colonne_gauche(Plateau p);

/**
 * @brief Prototype de get_colonne_droite.
 *
 * @param p
 * @return int
 */
int get_colonne_droite(Plateau p);

/**
 * @brief Prototype de set_numero_manche
 *
 * @param p
 * @param manche
 * @return int
 */

int set_numero_manche(Plateau p, int x);
/**************************************************
 * Création des prototypes des fonctions du plateau
 ***************************************************/

/**
 * @brief Crée la pioche avec les 32 cartes de l'énoncé pour la faction donnée
 * @param f faction valide (le pointeur doit être valide)
 *
 */
void init_pioche(Faction f);

/**
 * @brief Crée un plateau et les deux factions qui joueront dessus
 * @return le plateau initialisé
 *
 */
Plateau init_plateau();

/**
 * @brief Libère la mémoire associée au plateau de jeu et aux deux factions
 * @param p plateau valide (le pointeur doit être valide)
 *
 */
void libere_plateau(Plateau p);

/**
 * @brief Initialise une nouvelle manche ou indique que le jeu est terminé
 * @param p plateau valide (le pointeur doit être valide)
 * @return 1 si la partie continue, 0 si le jeu est terminé
 *
 */
int nouvelle_manche(Plateau p);

/**
 * @brief Détermine la faction qui joue en premier et renvoie la liste des deux factions du jeu dont le premier élément est la faction qui joue en premier
 * @param p plateau valide (le pointeur doit être valide)
 * @return la liste des des factions du jeu
 *
 */
Factions_en_jeu factions_plateau(Plateau p);

/**
 * @brief Permet à une faction de poser une carte face cachée sur le plateau
 * @param c carte valide
 * @param p plateau valide (le pointeur doit être valide)
 * @param i position en abscisse dans le plateau souhaitée pour la carte
 * @param j position en ordonnée dans le plateau souhaitée pour la carte
 *
 */
void poser_carte(Carte c, Plateau p, int i, int j);

/**
 * @brief Active les effets de la carte FISE
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_FISE(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte FISA
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_FISA(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte FC
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_FC(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte EcologIIE
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_EcologIIE(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte lIIEns
 * @param p plateau valide (le pointeur doit être valide)
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_lIIEns(Plateau p, Coord coord);

/**
 * @brief Active les effets de la carte Soirée sans alcool
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Soiree_sans_alcool(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Alcool
 * @param p plateau valide (le pointeur doit être valide)
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Alcool(Plateau p, Coord coord);

/**
 * @brief Active les effets de la carte Café
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Cafe(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Thé
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_The(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Ecocup
 * @param p plateau valide (le pointeur doit être valide)
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Ecocup(Plateau p, Coord coord);

/**
 * @brief Active les effets de la carte Reprographie
 * @param p plateau valide (le pointeur doit être valide)
 * @param f_adverse faction valide (le pointeur doit être valide), faction adverse de celle qui a déposé la carte
 * @param score_adverse score de la faction f_adverse
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Reprographie(Plateau p, Faction f_adverse, int score_adverse, Coord coord);

/**
 * @brief Active les effets de la carte Isolation du bâtiment
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param f_adverse faction valide (le pointeur doit être valide), faction adverse de celle qui a déposé la carte
 * @param score_adverse score de la faction f_adverse
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Isolation_du_batiment(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord);

/**
 * @brief Active les effets de la carte Parcours sobriété numérique
 * @param p plateau valide (le pointeur doit être valide)
 *
 */
void retourne_Parcours_sobriete_numerique(Plateau p);

/**
 * @brief Active les effets de la carte Heures supplémentaires
 * @param p plateau valide (le pointeur doit être valide)
 * @param f_adverse faction valide (le pointeur doit être valide), faction adverse de celle qui a déposé la carte
 * @param score_adverse score de la faction f_adverse
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Heures_supplementaires(Plateau p, Faction f_adverse, int score_adverse, Coord coord);

/**
 * @brief Active les effets de la carte Kahina Bouchama
 * @param p plateau valide (le pointeur doit être valide)
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Kahina_Bouchama(Plateau p, Coord coord);

/**
 * @brief Active les effets de la carte Kevin Goilard
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Kevin_Goilard(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Massinissa Merabet
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param f_adverse faction valide (le pointeur doit être valide), faction adverse de celle qui a déposé la carte
 * @param score_adverse score de la faction f_adverse
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Massinissa_Merabet(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord);

/**
 * @brief Active les effets de la carte Vitéra Y
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param f_adverse faction valide (le pointeur doit être valide), faction adverse de celle qui a déposé la carte
 * @param score_adverse score de la faction f_adverse
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Vitera_Y(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord);

/**
 * @brief Active les effets de la carte Jonas Senizergues
 * @param p plateau valide (le pointeur doit être valide)
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Jonas_Senizergues(Plateau p, Coord coord);

/**
 * @brief Active les effets de la carte Fetia Bannour
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Fetia_Bannour(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Catherine Dubois
 * @param p plateau valide (le pointeur doit être valide)
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Catherine_Dubois(Plateau p, Coord coord);

/**
 * @brief Active les effets de la carte Anne-Laure Ligozat
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_AnneLaure_Ligozat(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Guillaume Burel
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param f_adverse faction valide (le pointeur doit être valide), faction adverse de celle qui a déposé la carte
 * @param score_adverse score de la faction f_adverse
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Guillaume_Burel(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord);

/**
 * @brief Active les effets de la carte Christophe Mouilleron
 * @param p plateau valide (le pointeur doit être valide)
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Christophe_Mouilleron(Plateau p, Coord coord);

/**
 * @brief Active les effets de la carte Thomas Lim
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param f_adverse faction valide (le pointeur doit être valide), faction adverse de celle qui a déposé la carte
 * @param score_adverse score de la faction f_adverse
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Thomas_Lim(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord);

/**
 * @brief Active les effets de la carte Julien Forest
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Julien_Forest(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Dimitri Watel
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Dimitri_Watel(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Djibril-Aurélien Dembele-Cabot
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Djibril_Aurelien_Dembele_Cabot(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Eric Lejeune
 * @param p plateau valide (le pointeur doit être valide)
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Eric_Lejeune(Plateau p, Coord coord);

/**
 * @brief Active les effets de la carte Lucienne Pacavé
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Lucienne_Pacave(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Katrin Salhab
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Katrin_Salhab(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Laurent Prével
 * @param p plateau valide (le pointeur doit être valide)
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Laurent_Prevel(Plateau p, Coord coord);

/**
 * @brief Active les effets de la carte d'identifiant id
 * @param p plateau valide (le pointeur doit être valide)
 * @param id l'identifiant de la carte (son nom)
 * @param coord les coordonnées de la carte en question
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param f_adverse faction valide (le pointeur doit être valide), faction adverse de celle qui a déposé la carte
 * @param score score de la faction f
 * @param score_adverse score de la faction f_adverse
 *
 */
void switch_carte(Plateau p, id_carte id, Coord coord, Faction f, Faction f_adverse, int score, int score_adverse);

/**
 * @brief retourne la carte la plus en haut à gauche du plateau face visible et active son effet
 * @param p plateau valide (le pointeur doit être valide)
 * @return la carte que l'on a retourné face visible
 * @return NULL s'il n'y a plus aucune carte à retourner
 *
 */
Carte retourner_carte(Plateau p);

#endif // PLATEAU_H
