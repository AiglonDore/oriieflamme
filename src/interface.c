/**
 * @file interface.c
 * @author Thomas Roiseux (thomas.roiseux@ensiie.fr)
 * @brief Implémentation de interface.h
 * @version 0.1
 * @date 2022-04-05
 */

#include "../headers/interface.h"

#include <stdio.h>
#include <stdlib.h>

void affiche_plateau(Plateau p)
{

}

void affiche_effets(Carte c)
{
    printf("Effet de la carte \"%s\": \"%s\".\n",get_nom(c),get_description(c));
}