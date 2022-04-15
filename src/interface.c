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

char * nom_faction(Faction f)
{
    char *name = malloc(256*sizeof(char));
    printf("%s, comment souhaitez-vous vous appeler?\n",get_nom_faction(f));
    fgets(name,256,stdin);
    return name;
}

void affiche_plateau(Plateau p)
{
    for (int i = 0; i < 129; i++)
    {
        for (int j = 0; j < 129; j++)
        {
            if (get_plateau_jeu(p)[i][j] != NULL)
            {
                Carte tmp = get_plateau_jeu(p)[i][j];
                if (get_est_cachee(tmp))
                {
                    printf("Cachée ");
                }
                else
                {
                    printf("%s (%s) ",get_nom(tmp),get_nom_faction(get_proprietaire(tmp)));
                }
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void affiche_main(Faction f)
{
    Carte* main = get_main(f);
    for (int i = 0; i < 8; i++)
    {
        if (main[i] != NULL)
        {
            printf("%s\n",get_nom(main[i]));
            affiche_effet(main[i]);
        }
    }
}

int utiliser_option(Faction f)
{
    printf("%s, voulez-vous utiliser votre super pouvoir?[y/n]",get_nom(f));
    return fgetc(stdin) == 'y';
}

Carte a_poser_face_cachee_sur_plateau(Faction f)
{
    affiche_main(f);
    int nb_cartes = 0;
    for (int i = 0; i < 8; i++)
    {
        if (get_main(f)[i]) nb_cartes++;
    }
    printf("Quelle carte souhaitez-vous jouer? [1-%d]",nb_cartes);
    int ans = -1;
    while (scanf("%d",&ans) == 0 || (ans < 1 && ans > nb_cartes))
    {
        printf("Valeur incorrecte: elle doit être entre 1 et %d.",nb_cartes);
    }
    int count = 0;
    int ret = -1;
    for (int i = 0; i < 8; i++)
    {
        if (count == ans -1)
        {
            ret = i;
            break;
        }
        if (get_main(f)[i] != NULL) count++;
    }
    return get_main(f)[ret];
}

void affiche_effets(Carte c)
{
    printf("Effet de la carte \"%s\": \"%s\".\n",get_nom(c),get_description(c));
}