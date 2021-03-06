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
#include <string.h>
#include <unistd.h>

char *nom_faction(Faction f)
{
    char *name = malloc(256 * sizeof(char));
    printf("%s, comment souhaitez-vous vous appeler?\n", get_nom_faction(f));
    scanf("%s", name);
    return name;
}

void affiche_plateau(Plateau p)
{
    Coord haut_gauche = get_coord_carte_haut_gauche(p);
    Coord bas_droite = get_coord_carte_bas_droite(p);
    printf("          ");
    for (int j = get_colonne_gauche(p); j <= get_colonne_droite(p); j++)
        printf("Col. %d ", j);
    printf("\n");
    for (int i = haut_gauche.i; i <= bas_droite.i; i++)
    {
        printf("Ligne %d: ", i);
        for (int j = get_colonne_gauche(p); j <= get_colonne_droite(p); j++)
        {
            if (get_carte_at(p, i, j) != NULL)
            {
                Carte tmp = get_carte_at(p, i, j);
                if (get_est_cachee(tmp))
                {
                    printf("Cachée ");
                }
                else
                {
                    printf("%s (%s) ", get_nom(tmp), get_nom_faction(get_proprietaire(tmp)));
                }
            }
            else
            {
                printf("NULL ");
            }
        }
        printf("\n");
    }
}

void affiche_main(Faction f)
{
    printf("%s, voici votre main:\n", get_nom_faction(f));
    Carte *main = get_main(f);
    for (int i = 0; i < 8; i++)
    {
        if (main[i] != NULL)
        {
            printf("*%s\n", get_nom(main[i]));
            affiche_effets(get_id(main[i]));
        }
        else
        {
            printf("NULL\n");
        }
    }
}

int utiliser_option(Faction f)
{
    printf("%s, voulez-vous utiliser votre super pouvoir?[y/n]\n", get_nom_faction(f));
    char buf[1];
    scanf("%s", buf);
    return (!strcmp(buf, "y")) || (!strcmp(buf, "Y"));
}

Carte a_poser_face_cachee_sur_plateau(Faction f)
{
    int nb_cartes = 0;
    for (int i = 0; i < 8; i++)
    {
        if (get_main(f)[i])
            nb_cartes++;
    }
    printf("Quelle carte souhaitez-vous jouer? [1-%d]\n", nb_cartes);
    int ans = -1;
    while (scanf("%d", &ans) == 0 || ans < 1 || ans > nb_cartes)
    {
        printf("Valeur incorrecte: elle doit être entre 1 et %d.\n", nb_cartes);
    }
    int count = 0;
    int ret = 0;
    for (int i = 0; i < 8; i++)
    {
        if (get_main(f)[i] != NULL)
        {
            count++;
        }
        if (count == ans)
        {
            ret = i;
            break;
        }
    }
    return get_main(f)[ret];
}

void affiche_effets(int id)
{
    printf("Effet de la carte \"%s\": \"%s\".\n", get_nom_carte_vg(id), get_description_vg(id));
}

void affiche_vainqueur(Plateau p)
{
    Factions_en_jeu fct = get_factions(p);
    if (get_nb_manches_gagnees(fct.left) == 2)
    {
        printf("Le vainqueur de la partie est : \"%s\".\n", get_nom_faction(fct.left));
    }
    else
    {
        printf("Le vainqueur de la partie est : \"%s\".\n", get_nom_faction(fct.right));
    }
    printf("Mais cette victoire n'est pas encore officialisée!\n");
    printf("Il faut encore attendre le jury de validation pour que la victoire soit validée et définitive.\n");
    sleep(1);
    printf("Mail de Laurent Prével: jury de validation de la victoire\n");
    printf("Le jury va se réunir et évaluer la partie afin de valider ou non votre victoire... Ah, il manque un représentant de la DFP. Où est Julien Forest?\n");
    sleep(3);
    printf("Ca sent la cigarette! L'Homme des Cavernes, pardon, Julien Forest arrive par l'ascenceur (son café n'a pas réussi à l'empêcher de dormir). Il va donc pouvoir présider le jury pour valider votre victoire!");
}

Coord demande_position(Plateau p)
{
    Coord previous = get_coord_derniere_carte_posee(p);
    if (previous.i == -1 && previous.j == -1) // On n'affiche pas le plateau car il n'y a aucune carte posée.
    {
        Coord ret;
        ret.i = -1;
        ret.j = -1;
        printf("%s, vous êtes le premier à jouer! Votre carte sera posé au milieu du plateau!!\n", get_nom_faction(get_factions(p).left)); // On rappelle que le plateau de jeu est infini.
        return ret;
    }
    affiche_plateau(p);
    printf("Veuillez choisir où vous souhaitez poser la carte en saisissant le numéro associé:\n");
    int counter = 0;
    Coord available[129 * 129];
    for (int i = 0; i < 129; i++)
    {
        for (int j = 0; j < 129; j++)
        {
            if (get_carte_at(p, i, j) != NULL) // Si la case n'est pas nulle, alors il y a ue carte posée
            {
                if (i == 0 && j == 0) // Coin en haut à gauche
                {
                    if (get_carte_at(p, i, j + 1) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i;
                        tmp.j = j + 1;
                        printf("%d: (%d,%d)\n", counter + 1, i, j + 1);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i + 1, j) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i + 1;
                        tmp.j = j;
                        printf("%d: (%d,%d)\n", counter + 1, i + 1, j);
                        available[counter] = tmp;
                        counter++;
                    }
                }
                else if (i == 0 && j == 128) // Coin en haut à droite
                {
                    if (get_carte_at(p, i + 1, j) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i + 1;
                        tmp.j = j;
                        printf("%d: (%d,%d)\n", counter + 1, i + 1, j);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i - 1, j) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i - 1;
                        tmp.j = j;
                        printf("%d: (%d,%d)\n", counter + 1, i - 1, j);
                        available[counter] = tmp;
                        counter++;
                    }
                }
                else if (i == 128 && j == 0) // Coin en bas à gauche
                {
                    if (get_carte_at(p, i - 1, j) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i - 1;
                        tmp.j = j;
                        printf("%d: (%d,%d)\n", counter + 1, i - 1, j);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i, j + 1) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i;
                        tmp.j = j + 1;
                        printf("%d: (%d,%d)\n", counter + 1, i, j + 1);
                        available[counter] = tmp;
                        counter++;
                    }
                }
                else if (i == 128 && j == 128) // Coin en bas à droite
                {
                    if (get_carte_at(p, i, j - 1) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i;
                        tmp.j = j - 1;
                        printf("%d: (%d,%d)\n", counter + 1, i, j - 1);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i - 1, j) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i - 1;
                        tmp.j = j;
                        printf("%d: (%d,%d)\n", counter + 1, i - 1, j);
                        available[counter] = tmp;
                        counter++;
                    }
                }
                else if (i == 0) // Première ligne hors coins
                {
                    if (get_carte_at(p, i, j + 1) == NULL) // Point intérieur
                    {
                        Coord tmp;
                        tmp.i = i;
                        tmp.j = j + 1;
                        printf("%d: (%d,%d)\n", counter + 1, i, j + 1);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i + 1, j) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i + 1;
                        tmp.j = j;
                        printf("%d: (%d,%d)\n", counter + 1, i + 1, j);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i, j - 1) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i;
                        tmp.j = j - 1;
                        printf("%d: (%d,%d)\n", counter + 1, i, j - 1);
                        available[counter] = tmp;
                        counter++;
                    }
                }
                else if (i == 128) // Dernière ligne hors coins
                {
                    if (get_carte_at(p, i, j + 1) == NULL) // Point intérieur
                    {
                        Coord tmp;
                        tmp.i = i;
                        tmp.j = j + 1;
                        printf("%d: (%d,%d)\n", counter + 1, i, j + 1);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i, j - 1) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i;
                        tmp.j = j - 1;
                        printf("%d: (%d,%d)\n", counter + 1, i, j - 1);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i - 1, j) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i - 1;
                        tmp.j = j;
                        printf("%d: (%d,%d)\n", counter + 1, i - 1, j);
                        available[counter] = tmp;
                        counter++;
                    }
                }
                else if (j == 0) // Première colonne hors coins
                {
                    if (get_carte_at(p, i, j + 1) == NULL) // Point intérieur
                    {
                        Coord tmp;
                        tmp.i = i;
                        tmp.j = j + 1;
                        printf("%d: (%d,%d)\n", counter + 1, i, j + 1);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i + 1, j) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i + 1;
                        tmp.j = j;
                        printf("%d: (%d,%d)\n", counter + 1, i + 1, j);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i - 1, j) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i - 1;
                        tmp.j = j;
                        printf("%d: (%d,%d)\n", counter + 1, i - 1, j);
                        available[counter] = tmp;
                        counter++;
                    }
                }
                else if (j == 128) // Dernière colonne hors coins
                {
                    if (get_carte_at(p, i + 1, j) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i + 1;
                        tmp.j = j;
                        printf("%d: (%d,%d)\n", counter + 1, i + 1, j);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i, j - 1) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i;
                        tmp.j = j - 1;
                        printf("%d: (%d,%d)\n", counter + 1, i, j - 1);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i - 1, j) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i - 1;
                        tmp.j = j;
                        printf("%d: (%d,%d)\n", counter + 1, i - 1, j);
                        available[counter] = tmp;
                        counter++;
                    }
                }
                else // Points intérieurs
                {
                    if (get_carte_at(p, i, j + 1) == NULL) // Point intérieur
                    {
                        Coord tmp;
                        tmp.i = i;
                        tmp.j = j + 1;
                        printf("%d: (%d,%d)\n", counter + 1, i, j + 1);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i + 1, j) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i + 1;
                        tmp.j = j;
                        printf("%d: (%d,%d)\n", counter + 1, i + 1, j);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i, j - 1) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i;
                        tmp.j = j - 1;
                        printf("%d: (%d,%d)\n", counter + 1, i, j - 1);
                        available[counter] = tmp;
                        counter++;
                    }
                    if (get_carte_at(p, i - 1, j) == NULL)
                    {
                        Coord tmp;
                        tmp.i = i - 1;
                        tmp.j = j;
                        printf("%d: (%d,%d)\n", counter + 1, i - 1, j);
                        available[counter] = tmp;
                        counter++;
                    }
                }
            }
        }
    }
    int item = 0;
    while (scanf("%d", &item) == 0 || item < 1 || item > counter)
    {
        printf("Veuillez saisir un nombre entier compris entre 1 et %d: ", counter);
    }
    return available[item - 1];
}

void affiche_ddrs(Plateau p)
{
    Factions_en_jeu factions = get_factions(p);
    printf("%s, vos points DDRS sont: %d.\n", get_nom_faction(factions.left), get_pts_DDRS_manche(factions.left));
    printf("%s, vos points DDRS sont: %d.\n", get_nom_faction(factions.right), get_pts_DDRS_manche(factions.right));
}