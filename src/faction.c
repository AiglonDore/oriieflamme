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
#include <stdio.h>
#include "../headers/plateau.h"
#include "../headers/carte.h"
#include "../headers/faction.h"
#include "../headers/structure.h"

/**
 * @brief type concret pour la faction, a_remelange vaut 1 si la main a été remélangée, 0 sinon
 *
 */

struct StructureFactions
{
    char *nom;
    int nb_manches_gagnees;
    int pts_DDRS_manche;
    int a_remelange;
    Pioche pioche;
    Main main;
};

Faction creation_faction()
{
    return (malloc(sizeof(struct StructureFactions)));
}

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
    Carte pioche[47] = {NULL};
    int i; // pour la boucle for
    for (i = 0; i < 47; i += 1)
    {
        pioche[i] = enleve_pioche(f->pioche);
    }

    // On mélange ce tableau
    int t[47] = {0}; // ce tableau sert à savoir si l'indice généré a déjà été généré (t[i]=1 si i déjà sorti, 0 sinon)
    Carte pioche_melange[47] = {NULL};
    int c = 0; // sert à compter le nombre de cartes rentrées dans pioche_melange
    int n, k;
    while (c != 47)
    {
        n = rand() % (47 - c); // génère un nombre entier aléatoire entre 0 et 46-c
        k = 0;                 // compteur dans t[]
        for (i = 0; i < 47; i += 1)
        {
            if (t[i] == 0)
            {
                k += 1;
                if (k == n)
                {
                    pioche_melange[c] = pioche[i]; // on remplit pioche_melange grâce à pioche
                    t[i] = 1;                      // on indique que i a été traité
                    c += 1;                        // on indique qu'une carte a été ajoutée à pioche_melange, on donne l'indice pour la prochaine
                    break;
                }
            }
        }
    }

    // On empile les cartes alors mélangées
    int j; // pour la boucle for
    for (j = 0; j < 47; j += 1)
    { // on empile les cartes de telle sorte que le sommet soit pioche_melange[0] : choix arbitraire
        ajout_pioche(f->pioche, pioche_melange[46 - i]);
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

void supprimer_faction(Faction f)
{
    set_pioche(f, NULL);
    free(f->pioche); // la pioche a déjà été vidée
    int i;
    for (i = 0; i < 8; i += 1)
    {
        f->main[i] = NULL;
    }
    free(f->nom);
    f = NULL;
    free(f);
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

int get_nb_manches_gagnees(Faction f)
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
void set_pioche(Faction f, Pioche p)
{
    f->pioche = p;
}