/**
 * @file carte.h
 * @author Nour ELBESSI
 * @brief  Interface Carte : interface en charge
 * des informations des cartes jeu.
 * @date 2022-03-07
 */

#ifndef CARTE_H
#define CARTE_H

/**
 * @brief type abstrait pour la faction qu'on définira dans carte.c
 *
 */
typedef struct StructureCarte *Carte;

/**
 * @brief
 * Déclaration des constantes et variables globales relative aux cartes. Nombre de carte fixe à 8, et une énumération des nom de cartes, ainsi qu'une déclaration des effets.
 *
 */

const int nb_cartes = 8;

typedef enum nom_carte
{
    FISE,
    FISA,
    FC,
    EcologIIE,
    lIIEns,
    Soiree_sans_alcool,
    Alcool,
    Cafe,
    The,
    Ecocup,
    Reprographie,
    Isolation_batiment,
    Parcous_sobriete_mumerique,
    Heures_supplementaites,
    Kahina_Bouchama,
    Kevin_Goilard,
    Massinissa_Merabet,
    Vitera_Y,
    Jonas_Senizergues,
    Fetia_Bannour,
    Catherine_Dubois,
    AnneLaure_Ligozat,
    Guillaume_Burel,
    Christophe_Mouilleron,
    Thomas_lim,
    Julien_forest,
    Dimitri_watel,
    Djibril_Aurelien_Dembele_Cabot,
    Eric_Lejeune,
    Lucienne_Pacave,
    Katrin_Salhab,
    Laurent_Prevel
} nom_carte;

char *nom_carte[32] = {"FISE", "FISA", "FC", "EcologIIE", "lIIEns", "Soiree_sans_alcool", "Alcool",
                       "Cafe", "The", "Ecocup", "Reprographie", "Isolation_batiment", "Parcous_sobriete_mumerique",
                       "Heures supplementaites", "Kahina Bouchama", "Kevin Goilard", "Massinissa Merabet",
                       "Vitera Y", "Jonas Senizergues", "Fetia Bannour", "Catherine Dubois", "Anne Laure Ligozat",
                       "Guillaume Burel", "Christophe Mouilleron", "Thomas lim", "Julien Forest", "Dimitri watel",
                       "Djibril Aurelien Dembele Cabot", "Eric Lejeune", "Lucienne Pacave", "Katrin Salhab",
                       "Laurent Prevel"};

char *description[32] = {
    "La faction qui a posé cette carte gagne 1 point DDRS.",
    "La faction qui a posé cette carte gagne 2 points DDRS si le nombre de cartes retournées sur le plateau (y compris celle-ci) est pair, et 0 sinon.",
    "La faction qui a posé cette carte gagne 4 points DDRS si au moins une autre carte FC est retournée sur le plateau et 0 sinon",
    "La faction qui a posé cette carte gagne 1 point DDRS par carte FISE/FISA/FC retournée.",
    "Prenez toutes les cartes FISE/FISA/FC retournées, retirez les du plateau, mélangez les et reposez les face cachées une par une sur la gauche de la carte la plus en haut à gauche du plateau, dans cet ordre. Les prochaines cartes à être retournées sont ces cartes là.",
    "Si au moins une carte alcool est retournée, supprimez toutes les cartes FISE/FISA/FC retournées du plateau. Supprimez ensuite la première et la dernière ligne du plateau. Sinon la faction qui a posé cette carte gagne 5 points DDRS.",
    "Supprimez du plateau toutes les cartes qui touchent cette carte-ci (mais laissez la carte Alcool sur le plateau).",
    "Supprimez toutes les cartes Thé et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.",
    "Supprimez toutes les cartes Café et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.",
    "Cette carte est sans effet",
    "La faction adverse de celle qui a posé cette carte perd 1 points DDRS pour chaque paire de cartes retournées et identiques sur le plateau. (S'il y a 3 cartes identiques, cela fait 3 paires).",
    "Chaque faction gagne 1 point DDRS par carte non retournée et non supprimée du plateau qu'elle a posée sur le plateau.",
    "Retournez toutes les cartes non retournées les plus à gauche et à droite de chaque ligne, sans appliquer leur effet.",
    "La faction adverse de celle qui a posé cette carte perd 3 points DDRS par carte Heures supplémentaires retournée sur le plateau (y compris celle-ci).",
    "Supprimez une carte non retournée du plateau choisie au hasard.",
    "Supprimez une ligne au hasard, la faction qui a posé cette carte gagne 2 points DDRS par carte supprimée ainsi.",
    "La faction qui a posé cette carte réactive l'effet de la dernière carte retournée avant Massinissa Merabet, en faisant comme elle l'avait posée elle-même, même si ce n'est pas le cas.",
    "La faction qui a le moins de points DDRS gagne 3 points DDRS.",
    "Supprimez toutes les cartes Heures supplémentaires retournées du plateau.",
    "Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes de la ligne et de la colonne où est posée cette carte (y compris celle-ci). Sinon la faction qui a posé cette carte gagne 1 point DDRS par carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest et Dimitri Watel retournée sur le plateau.",
    "Supprimez la première et la dernière cartes de la ligne et de la colonne où est posée cette carte.",
    "Pour chaque carte EcologIIE, Ecocup, Isolation du bâtiment et parcours Sobriété numérique retournée, la faction qui a posé cette carte gagne 3 points DDRS et la dernière carte non retournée du plateau est supprimée. (L'effet continue même si Anne-Laure Ligozat ou une des 4 cartes précédemment mentionnées est supprimée).",
    "Si la faction adverse de celle qui a posé cette carte a plus de points DDRS, la seconde lui vole 3 points DDRS.",
    "Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes retournées du plateau sauf les cartes Christophe Mouilleron et Heures supplémentaires.",
    "Si Julien Forest n'est par retourné sur le plateau, la faction qui a posé cette carte gagne 3 points DDRS par carte FISE retournée sur le plateau. Sinon la faction adverse perd 1 point DDRS par carte FISE retournée sur le plateau.",
    "La faction qui a posé cette carte gagne 6 points DDRS par carte FISE retournée sur le plateau si au moins une carte Café est retournée sur le plateau.",
    "La faction qui a posé cette carte gagne 3 points DDRS par carte FISA ou FC retournée sur le plateau si au moins une carte Thé est retournée sur le plateau.",
    "S'il y a plus de 3 cartes retournées sur la ligne de cette carte, la faction qui a posé cette carte gagne 5 points DDRS.",
    "Prenez au hasard 5 cartes retournées du plateau (ou toutes les cartes retournées du plateau s'il y a moins de 5). Si une de ces cartes est une carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest ou Dimitri Watel, mélangez les et placez les à gauche de la case la plus à gauche de la première ligne. Les prochaines cartes à être retournées sont ces cartes là. Sinon, supprimez ces cartes du plateau.",
    "S'il y a une carte FISA retournée dans la même ligne ou la même colonne que cette carte, la faction qui a posé cette carte gagne 5 points DDRS.",
    "Si les cartes Djibril-Aurélien Djembele-Cabeau, Eric Lejeune et Lucienne Pacavé sont retournées, la faction qui a posé cette carte gagne 10 points DDRS. Sinon, retournez toutes les cartes dans la même ligne de cette carte sans appliquer leurs effets.",
    "Si Laurent Prével est la dernière carte retournée du plateau, la faction qui a posé cette carte gagne la manche, quel que soit le nombre de points DDRS des deux factions."};

/**************************************************
 * Création des prototypes des getters et setters
 ***************************************************/

/**
 * @brief Prototype de get_nom qui permet de récupérer le nom de la carte
 *
 * @param c
 * @return char*
 */

char *get_nom(Carte c);

/**
 * @brief Prototype de set_nom qui permet d'initialiser le nom de la carte.
 *
 * @param c
 * @param nom_carte
 */
void set_nom(Carte c, char *nom_carte);

/**
 * @brief Prototype de get_description qui permet de récupérer la description de la carte
 *
 * @param c
 * @return char*
 */
char *get_description(Carte c);

/**
 * @brief Prototype de set_description qui permet d'initialiser la description de la carte.
 *
 * @param c
 * @param description_carte
 */
void set_description(Carte c, char *description_carte);

/**
 * @brief Prototype de get_nb_occ qui permet de récupérer le nombre d'occurence d'une carte
 *
 * @param c
 * @return int
 */
int get_nb_occ(Carte c);

/**
 * @brief Prototype de get_est_cachee qui permet de récupérer un entier qui indique si la face est cachée ou pas.
 *
 * @param c
 * @return int
 */
int get_est_cachee(Carte c);

/**
 * @brief Prototype de set_est_cachee qui permet de changer la valeur associé à la face d'une carte: 0 Face non cachée et 1 face cachée
 *
 * @param c
 * @param x
 */
void set_est_cachee(Carte c, int x);

#endif