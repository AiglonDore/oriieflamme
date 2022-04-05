/**
 * @file faction.c
 * @author Nour Elbessi & Valentin Gardel
 * @brief Implantation de l'interface en charge des informations et des manipulations propres à une faction
 * @version 0.1
 * @date 2022-04-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdlib.h>
#include "../headers/plateau.h"
#include "../headers/carte.h"
#include "../headers/faction.h"
#include "../headers/structure.h"

/**
 * @brief type concret pour la faction, a_remelange vaut 1 si la main a été remélangée, 0 sinon
 *
 */
typedef struct StructureFactions
{
    char *nom;
    int nb_manches_gagnees;
    int pts_DDRS_manche;
    int a_remelange;
    int carte_anl_retournee;
    Pioche pioche;
    Main main;
};

int a_remelange(Faction f)
{
    return f->a_remelange;
}

void melanger(Faction f)
{
    vider_sa_main(f);
    melanger_pioche(f);
    piocher(f);
    free(f->nom);
}

void vider_sa_main(Faction f)
{
    int i; // pour la boucle for
    for (i = 0; i < 8; i += 1)
    {
        Carte c;
        c = f->main[i];             // on prend la carte de la main
        ajout_pioche(f->pioche, c); // on la remet dans la pioche
        f->main[i] = NULL;          // on met le pointeur NULL à la place de la carte dans la main
    }
}

void melanger_pioche(Faction f)
{

    // On dépile et on stocke les cartes dans un tableau
    Carte pioche[32];
    int i; // pour la boucle for
    for (i = 0; i < 32; i += 1)
    {
        pioche[i] = enleve_pioche(f->pioche);
    }

    // On mélange ce tableau : on crée pioche_melange que l'on remplit à partir de pioche en générant un indice aléatoire de 0 à 31
    int t[32]; // ce tableau sert à savoir si l'indice généré a déjà été généré (t[i]=1 si i déjà sorti, 0 sinon)
    Carte pioche_melange[32];
    int c = 0;           // sert à compter le nombre de cartes rentrées dans pioche_melange
    int n = rand() % 32; // génère un nombre entier aléatoire entre 0 et 31
    while (c != 32)
    {
        while (t[n] == 1)
        {                    // tant que l'indice a déjà été traité
            n = rand() % 32; // génère un nombre entier aléatoire entre 0 et 31
        }
        pioche_melange[c] = pioche[n]; // on remplit pioche_melange grâce à pioche
        t[n] = 1;                      // on indique que n a été traité
        c += 1;                        // on indique qu'une carte a été ajoutée à pioche_melange, on donne l'indice pour la prochaine
    }

    // On empile les cartes alors mélangées
    int j; // pour la boucle for
    for (j = 0; j < 32; j += 1)
    { // on empile les cartes de telle sorte que le sommet soit pioche_melange[0] : choix arbitraire
        ajout_pioche(f->pioche, pioche_melange[31 - i]);
    }
}

void piocher(Faction f)
{
    int i; // pour la boucle for
    for (i = 0; i < 8; i += 1)
    {
        f->main[i] = enleve_pioche(f->pioche); // on remplit la main en dépilant la pioche
    }
}

/**************************************************
 * Implémentation des getters et setters
 ***************************************************/

char *get_nom_faction(Faction f)
{
    return f->nom;
}

void set_nom_faction(Faction f, char *nom_faction)
{
    f->nom = nom_faction;
}

int get_nb_maches_gagnees(Faction f)
{
    return f->nb_manches_gagnees;
}

void set_nb_manches_gagnees(Faction f, int x)
{
    f->nb_manches_gagnees = x;
}

int get_pts_DDRS_manche(Faction f)
{
    return f->pts_DDRS_manche;
}

void set_pts_DDRS_manche(Faction f, int x)
{
    f->pts_DDRS_manche = x;
}

int get_a_remelange(Faction f)
{
    return f->a_remelange;
}

void set_a_remelange(Faction f, int x)
{
    f->a_remelange = x;
}

int get_carte_anl_retournee(Faction f)
{
    return f->carte_anl_retournee;
}

void set_carte_anl_retournee(Faction f, int x)
{
    f->carte_anl_retournee = x;
}

Carte *get_main(Faction f)
{
    return f->main;
}

void set_main(Faction f, Carte *main)
{
    int i;
    for (i = 0; i < 8; i += 1)
    {
        f->main[i] = main[i];
    }
}

Pioche get_pioche(Faction f)
{
    return f->pioche;
}