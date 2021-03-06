/**
 * @file carte.c
 * @author Nour Elbessi
 * @brief Implantation de l'interface en charge des informations des cartes du jeu
 * @version 0.1
 * @date 2022-03-22
 *
 * @copyright Copyright (c) 2022
 *
 */

/**
 * @brief type concret pour la faction, est_cachee vaut 1 si la carte est posée face cachée, 0 sinon
 *
 */

#include <stdlib.h>
#include "../headers/carte.h"
#include "../headers/faction.h"
#include "../headers/structure.h"

struct StructureCarte
{
    id_carte id;
    Faction proprietaire;
    char *nom;
    char *description;
    int nb_occ;
    int est_cachee;
};

Carte creation_carte()
{
    return (malloc(sizeof(struct StructureCarte)));
}

Carte nouvelle_carte(id_carte id, Faction f)
{
    Carte c = creation_carte();                 // on créé ladite carte
    set_id(c, id);                              // on lui associe son identifiant
    set_nom(c, get_nom_carte_vg(id));           // on lui associe son nom
    set_proprietaire(c, f);                     // on lui associe son propriétaire
    set_description(c, get_description_vg(id)); // on lui associe sa descrption
    set_nb_occ(c, get_nb_occ_vg(id));           // on lui associe son nb d'occurences
    set_est_cachee(c, 1);
    return (c);
}

/**
 * @brief
 * Déclaration des constantes et variables globales relative aux cartes. Nombre de carte fixe à 8 ainsi qu'une déclaration des effets.
 *
 */

const int nb_cartes = 8;

char *nom_carte[32] = {"FISE", "FISA", "FC", "EcologIIE", "lIIEns", "Soiree_sans_alcool", "Alcool",
                       "Cafe", "The", "Ecocup", "Reprographie", "Isolation_batiment", "Parcours_sobriete_mumerique",
                       "Heures supplementaires", "Kahina Bouchama", "Kevin Goilard", "Massinissa Merabet",
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

int nb_occ[32] = {4, 4, 4, 2, 2, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

/**************************************************
 * Implémentation des getters et setters
 ***************************************************/

id_carte get_id(Carte c)
{
    return c->id;
}

void set_id(Carte c, id_carte id)
{
    c->id = id;
}

Faction get_proprietaire(Carte c)
{
    return c->proprietaire;
}

void set_proprietaire(Carte c, Faction f)
{
    c->proprietaire = f;
}

char *get_nom(Carte c)
{
    return c->nom;
}

void set_nom(Carte c, char *nom_carte)
{
    c->nom = nom_carte;
}

char *get_description(Carte c)
{
    return c->description;
}

void set_description(Carte c, char *description_carte)
{
    c->description = description_carte;
}

int get_nb_occ(Carte c)
{
    return c->nb_occ;
}

void set_nb_occ(Carte c, int x)
{
    c->nb_occ = x;
}

int get_est_cachee(Carte c)
{
    return c->est_cachee;
}

void set_est_cachee(Carte c, int x)
{
    c->est_cachee = x;
}

int get_nb_occ_vg(int i)
{
    return nb_occ[i];
}

char *get_nom_carte_vg(int i)
{
    return nom_carte[i];
}

char *get_description_vg(int i)
{
    return description[i];
}