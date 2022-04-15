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
    return c->nom;
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