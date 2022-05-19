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
 * @brief Prototype de creation_plateau qui permet d'initialiser un plateau.
 *
 * @return Plateau alloué
 */

Plateau creation_plateau();

/**************************************************
 * Création des prototypes des getters et setters
 ***************************************************/

/**
 * @brief Prototype de get_carte_at.
 *
 * @param p Plateau de jeu.
 * @param i coordonnée horizontale de la carte souhaitée
 * @param j coordonnée verticale de la carte souhaitée
 * @return Carte à la position i, j sur le plateau
 */
Carte get_carte_at(Plateau p, int i, int j);

/**
 * @brief Prototype de get_factions qui permet de récupérer les factions en jeu.
 *
 * @param p Plateau de jeu.
 * @return Couple des factions sur le plateau
 */
Factions_en_jeu get_factions(Plateau p);

/**
 * @brief Prototype de get_coord_derniere_carte_posee.
 *
 * @param p Plateau de jeu.
 * @return Coordonnées de la dernière carte posée
 */
Coord get_coord_derniere_carte_posee(Plateau p);

/**
 * @brief Prototype de get_coord_derniere_carte_retournee.
 *
 * @param p Plateau de jeu.
 * @return Coordonnées de la dernière carte retournée
 */
Coord get_coord_derniere_carte_retournee(Plateau p);

/**
 * @brief Prototype de get_coord_avant_derniere_carte_retournee.
 *
 * @param p Plateau de jeu.
 * @return Coordonnée de l'avant-dernière carte retournée
 */
Coord get_coord_avant_derniere_carte_retournee(Plateau p);

/**
 * @brief Prototype de get_derniere_carte_retournee.
 *
 * @param p Plateau de jeu.
 * @return Dernière carte retournée
 */
Carte get_derniere_carte_retournee(Plateau p);

/**
 * @brief Prototype de get_avant_derniere_carte_retournee.
 *
 * @param p Plateau de jeu.
 * @return Avabt-dernière carte retournée
 */
Carte get_avant_derniere_carte_retournee(Plateau p);

/**
 * @brief Prototype de get_coord_carte_haut_gauche.
 *
 * @param p Plateau de jeu.
 * @return Coordonnées de la carte la plus en haut à gauche du plateau
 */
Coord get_coord_carte_haut_gauche(Plateau p);

/**
 * @brief Prototype de get_coord_carte_bas_droite.
 *
 * @param p Plateau de jeu.
 * @return Coordonnées de la carte la plus en bas à droite du plateau
 */
Coord get_coord_carte_bas_droite(Plateau p);

/**
 * @brief Prototype de get_numero_manche.
 *
 * @param p Plateau de jeu.
 * @return Numéro de la manche en cours
 */
int get_numero_manche(Plateau p);

/**
 * @brief Prototype de get_cartes_retournees_manche.
 *
 * @param p Plateau de jeu.
 * @return Nombre de cartes retournées sur le plateau
 */
int get_cartes_retournees_manche(Plateau p);

/**
 * @brief Prototype de get_cartes_non_retournees_manche.
 *
 * @param p Plateau de jeu.
 * @return Nombre de cartes non retournées sur le plateau
 */
int get_cartes_non_retournees_manche(Plateau p);

/**
 * @brief Prototype de get_colonne_gauche.
 *
 * @param p Plateau de jeu.
 * @return Numéro de la colonne la plus à gauche où se trouve une carte non NULL
 */
int get_colonne_gauche(Plateau p);

/**
 * @brief Prototype de get_colonne_droite.
 *
 * @param p Plateau de jeu.
 * @return Numéro de la colonne la plus à droite où se trouve une carte non NULL
 */
int get_colonne_droite(Plateau p);

/**
 * @brief Prototype de set_numero_manche
 *
 * @param p Plateau de jeu.
 * @param manche Numéro de la manche
 */
void set_numero_manche(Plateau p, int manche);

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
 * @brief Crée une faction initialisée
 * @param nom nom de la faction
 * @param manches_gagnees nombre de manches gagnées par la faction
 * @param a_remelange indique si la faction a déjà utilisé son joker ou non
 * @param dernier_vainqueur vaut 1 si la faction est celle qui a gagné la dernière manche, 0 sinon (et 0 en cas de première manche)
 * @return la faction initialisée
 *
 */
Faction init_faction(char *nom, int manches_gagnees, int a_remelange, int dernier_vainqueur);

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
 * @brief Active les effets de la carte Ascenseur en panne
 * @param p plateau valide (le pointeur doit être valide)
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Ascenseur_en_panne(Plateau p, Coord coord);

/**
 * @brief Active les effets de la carte Nour Elbessi
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Nour_Elbessi(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Thomas Roiseux
 * @param p plateau valide (le pointeur doit être valide)
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Thomas_Roiseux(Plateau p, Coord coord);

/**
 * @brief Active les effets de la carte Clémence Juste
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param f_adverse faction valide (le pointeur doit être valide), faction adverse de celle qui a déposé la carte
 * @param score_adverse score de la faction f_adverse
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Clemence_Juste(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord);

/**
 * @brief Active les effets de la carte Examen
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Examen(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Échec
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param f_adverse faction valide (le pointeur doit être valide), faction adverse de celle qui a déposé la carte
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Echec(Plateau p, Faction f, int score, Faction f_adverse, Coord coord);

/**
 * @brief Active les effets de la carte Droit
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Droit(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte OCaml
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_OCaml(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Stefania Dumbrava
 * @param p plateau valide (le pointeur doit être valide)
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Stefania_Dumbrava(Plateau p, Coord coord);

/**
 * @brief Active les effets de la carte Nicolas Brunel
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Nicolas_Brunel(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte TP de Statistiques
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_TP_statistiques(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Juhuyn Park
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Juhuyn_Park(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Angela Pineda
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Angela_Pineda(Plateau p, Faction f, int score, Coord coord);

/**
 * @brief Active les effets de la carte Dièse
 * @param p plateau valide (le pointeur doit être valide)
 * @param f faction valide (le pointeur doit être valide), faction qui a déposé la carte
 * @param score score de la faction f
 * @param coord les coordonnées de la carte en question sur le plateau
 *
 */
void retourne_Diese(Plateau p, Faction f, int score, Coord coord);

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
 * @return -1 s'il n'y a plus aucune carte à retourner, sinon l'id de la carte retournée
 *
 */
int retourner_carte(Plateau p);

#endif // PLATEAU_H
