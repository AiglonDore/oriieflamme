/**
 * @file plateau.c
 * @author Nour Elbessi & Valentin Gardel
 * @brief Implémentation de l'interface pour gérer le plateau de jeu et le déroulement de la partie
 * @version 0.1
 * @date 2022-03-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdlib.h>
#include "../headers/plateau.h"
#include "../headers/carte.h"
#include "../headers/faction.h"
#include "../headers/structure.h"
#include "../headers/interface.h"

/**
 * @brief type concret vers lequel pointe le plateau de jeu
 *
 */

struct s_plateau
{
    Plateau_jeu plateau_jeu;
    Factions_en_jeu factions;
    Coord derniere_carte_posee;
    Coord derniere_carte_retournee;
    Coord avant_derniere_carte_retournee;
    Coord carte_haut_gauche_cachee;
    Coord carte_bas_droite_cachee;
    Coord carte_haut_gauche;
    Coord carte_bas_droite;
    int numero_manche;
    int cartes_retournees_manche;
    int cartes_non_retournees_manche;
};

Plateau creation_plateau()
{
    return (malloc(sizeof(struct s_plateau)));
}
/**************************************************
 * Implémentation des prototypes des getters
 ***************************************************/

Carte **get_plateau_jeu(Plateau p)
{
    return (Carte **)p->plateau_jeu;
}

Factions_en_jeu get_factions(Plateau p)
{
    return p->factions;
}

Coord get_derniere_carte_posee(Plateau p)
{
    return p->derniere_carte_posee;
}

Coord get_derniere_carte_retournee(Plateau p)
{
    return p->derniere_carte_retournee;
}

Coord get_avant_derniere_carte_retournee(Plateau p)
{
    return p->avant_derniere_carte_retournee;
}

Coord get_carte_haut_gauche(Plateau p)
{
    return p->carte_haut_gauche;
}

Coord get_carte_bas_droite(Plateau p)
{
    return p->carte_bas_droite;
}

int get_numero_manche(Plateau p)
{
    return p->numero_manche;
}

int get_cartes_retournees_manche(Plateau p)
{
    return p->cartes_retournees_manche;
}

int get_cartes_non_retournees_manche(Plateau p)
{
    return p->cartes_non_retournees_manche;
}

/********************************************************
 * Implémentation des prototypes des fonctions du plateau
 ********************************************************/

void init_pioche(Faction f)
{
    int i;
    Pioche pioche = creation_pioche_vide();
    pioche = get_pioche(f);
    for (i = 0; i < 32; i += 1)
    {
        int j = nb_occ[i];
        while (j != 0)
        {
            Carte c = creation_carte();
            set_id(c, i);
            set_nom(c, nom_carte[i]);
            set_proprietaire(c, f);
            set_description(c, description[i]);
            set_nb_occ(c, nb_occ[i]);
            set_est_cachee(c, 1);
            ajout_pioche(pioche, c);
            j -= 1;
        }
    }
}

Plateau init_plateau()
{
    Plateau p = creation_plateau();
    // On initialise le numéro de manche
    p->numero_manche = 0;
    // On initialise les factions
    Faction faction1 = creation_faction();
    Faction faction2 = creation_faction();
    set_nom_faction(faction1, "Faction 1");
    set_nom_faction(faction2, "Faction 2");
    char *a = nom_faction(faction1);
    char *b = nom_faction(faction2);
    set_nom_faction(faction1, a);
    set_nom_faction(faction2, b);
    set_nb_manches_gagnees(faction1, 0);
    set_nb_manches_gagnees(faction2, 0);
    set_carte_anl_retournee(faction1, 0);
    set_carte_anl_retournee(faction2, 0);
    p->factions.left = faction1;
    p->factions.right = faction2;
    // Le reste de l'initialisation est commun à chaque début de manche et se fera dans nouvelle_manche
    return p;
}

void libere_plateau(Plateau p)
{
    init_pioche(p->factions.left);
    init_pioche(p->factions.right);
    free(get_pioche(p->factions.left));
    free(get_pioche(p->factions.right));
    free(p->factions.left);
    free(p->factions.right);
    return;
}

int nouvelle_manche(Plateau p)
{
    // Lorsqu'une manche se termine
    if (p->numero_manche != 0)
    {
        int score_left = get_pts_DDRS_manche(p->factions.left);
        int score_right = get_pts_DDRS_manche(p->factions.right);
        int manches_gagnees_left = get_nb_manches_gagnees(p->factions.left);
        int manches_gagnees_right = get_nb_manches_gagnees(p->factions.right);
        Carte carte = p->plateau_jeu[p->derniere_carte_retournee.i][p->derniere_carte_retournee.j];
        id_carte id = get_id(carte);
        Faction f = get_proprietaire(carte);
        if (id == Laurent_Prevel)
        {
            if (f == p->factions.left)
            {
                set_nb_manches_gagnees(p->factions.left, manches_gagnees_left + 1);
            }
            else
            {
                set_nb_manches_gagnees(p->factions.right, manches_gagnees_right + 1);
            }
        }
        else
        {
            if (score_left < score_right)
            {
                set_nb_manches_gagnees(p->factions.right, manches_gagnees_right + 1);
            }
            else if (score_left > score_right)
            {
                set_nb_manches_gagnees(p->factions.left, manches_gagnees_left + 1);
            }
            else
            { // égalité
                Carte carte = p->plateau_jeu[p->carte_haut_gauche.i][p->carte_haut_gauche.j];
                Faction f = get_proprietaire(carte);
                if (f == p->factions.left)
                {
                    set_nb_manches_gagnees(p->factions.left, manches_gagnees_left + 1);
                }
                else
                {
                    set_nb_manches_gagnees(p->factions.right, manches_gagnees_right + 1);
                }
            }
        }
    }
    // On regarde si une faction a gagné
    if (get_nb_manches_gagnees(p->factions.left) == 2 || get_nb_manches_gagnees(p->factions.right) == 2)
    {
        return 0;
    }
    // On initialise les scores des factions
    set_pts_DDRS_manche(p->factions.left, 0);
    set_pts_DDRS_manche(p->factions.right, 0);
    // On réinitialise les pioches et les mains des factions
    init_pioche(p->factions.left);
    init_pioche(p->factions.right);
    Carte main[8] = {NULL};
    set_main(p->factions.left, main);
    set_main(p->factions.right, main);
    // On initialise le plateau de jeu
    int i, j;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            p->plateau_jeu[i][j] = NULL;
        }
    }
    // On initialise les paramètres du plateau (on a choisi -1 arbitraitement)
    p->cartes_retournees_manche = 0;
    p->cartes_non_retournees_manche = 0;

    p->numero_manche += 1;

    p->derniere_carte_posee.i = -1;
    p->derniere_carte_posee.j = -1;

    p->derniere_carte_retournee.i = -1;
    p->derniere_carte_retournee.j = -1;

    p->avant_derniere_carte_retournee.i = -1;
    p->avant_derniere_carte_retournee.j = -1;

    p->carte_bas_droite_cachee.i = -1;
    p->carte_bas_droite_cachee.j = -1;
    p->carte_haut_gauche_cachee.i = -1;
    p->carte_haut_gauche_cachee.j = -1;

    p->carte_bas_droite.i = -1;
    p->carte_bas_droite.j = -1;
    p->carte_haut_gauche.i = -1;
    p->carte_haut_gauche.j = -1;

    return 1;
}

Factions_en_jeu factions_plateau(Plateau p)
{
    int m = p->numero_manche;
    if (m == 1 || m == 3)
    {                       // 1ère ou 3ème manche donc on choisit aléatoirement si on échange factions.left et factions.right ou pas
        int i = rand() % 2; // génère 0 ou 1 de manière aléatoire
        if (i == 0)
        {
            return p->factions;
        }
        else
        {
            Faction f = p->factions.left;
            p->factions.left = p->factions.right;
            p->factions.right = f;
            return p->factions;
        }
    }
    else
    { // 2ème manche donc on fait jouer en premier l'autre faction cette fois-ci
        Faction f = p->factions.left;
        p->factions.left = p->factions.right;
        p->factions.right = f;
        return p->factions;
    }
}

void poser_carte(Carte c, Plateau p, int i, int j)
{ // on suppose que i et j sont légales
    Coord derniere_carte = p->derniere_carte_posee;
    p->cartes_non_retournees_manche += 1;
    // Cas de la première carte à poser
    if (derniere_carte.i == -1 && derniere_carte.j == -1)
    {
        p->plateau_jeu[64][64] = c;
        p->derniere_carte_posee.i = 64;
        p->derniere_carte_posee.j = 64;
        p->carte_bas_droite.i = 64;
        p->carte_bas_droite.j = 64;
        p->carte_haut_gauche.i = 64;
        p->carte_haut_gauche.j = 64;
        p->carte_bas_droite_cachee.i = 64;
        p->carte_bas_droite_cachee.j = 64;
        p->carte_haut_gauche_cachee.i = 64;
        p->carte_haut_gauche_cachee.j = 64;
        return;
    }
    p->plateau_jeu[i][j] = c;
    p->derniere_carte_posee.i = i;
    p->derniere_carte_posee.j = j;
    // On change éventuellement les coordonnées des cartes en haut à gauche et en bas à droite
    if (j <= p->carte_bas_droite.j && i > p->carte_bas_droite.i)
    {
        p->carte_bas_droite.i = i;
        p->carte_bas_droite.j = j;
        p->carte_bas_droite_cachee.i = i;
        p->carte_bas_droite_cachee.j = j;
        return;
    }
    else if (j >= p->carte_haut_gauche.j && i < p->carte_haut_gauche.i)
    {
        p->carte_haut_gauche.i = i;
        p->carte_haut_gauche.j = j;
        p->carte_haut_gauche_cachee.i = i;
        p->carte_haut_gauche_cachee.j = j;
        return;
    }
}

void actualiser_constantes_cas_general(Plateau p, Coord coord)
{
    // Actualisation des constantes
    p->avant_derniere_carte_retournee.i = p->derniere_carte_retournee.i;
    p->avant_derniere_carte_retournee.j = p->derniere_carte_retournee.j;
    p->derniere_carte_retournee.i = coord.i;
    p->derniere_carte_retournee.j = coord.j;
}

void bonus_anl(Faction f, int score, Faction f_adverse, int score_adverse)
{
    int anl_f = get_carte_anl_retournee(f);
    int anl_f_adv = get_carte_anl_retournee(f_adverse);
    if (anl_f == 1)
    {
        score += 3;
        set_pts_DDRS_manche(f, score);
    }
    if (anl_f_adv == 1)
    {
        score_adverse += 3;
        set_pts_DDRS_manche(f_adverse, score_adverse);
    }
}

void retourne_FISE(Plateau p, Faction f, int score, Coord coord)
{
    set_pts_DDRS_manche(f, score + 1);
    actualiser_constantes_cas_general(p, coord);
}

void retourne_FISA(Plateau p, Faction f, int score, Coord coord)
{
    if (p->cartes_retournees_manche % 2 == 0)
    {
        set_pts_DDRS_manche(f, score + 2);
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_FC(Plateau p, Faction f, int score, Coord coord)
{
    int i, j;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_id(carte) == FC && get_est_cachee(carte) == 0)
            {
                set_pts_DDRS_manche(f, score + 4);
                break;
            }
        }
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_EcologIIE(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord)
{
    bonus_anl(f, score, f_adverse, score_adverse);
    int pts_gagnes = 0;
    int i, j;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && (get_id(carte) == FISE || get_id(carte) == FISA || get_id(carte) == FC))
            {
                pts_gagnes += 1;
            }
        }
    }
    set_pts_DDRS_manche(f, score + pts_gagnes);
    actualiser_constantes_cas_general(p, coord);
}

void retourne_lIIEns(Plateau p, Coord coord)
{
    // On enlève les cartes FISE/FISA/FC retournées du plateau, on les stocke dans a_retirer
    Carte a_retirer[16]; // il y a 16 cartes sur le plateau
    int nb_a_retirer = 0;
    int i, j;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && (get_id(carte) == FISE || get_id(carte) == FISA || get_id(carte) == FC))
            {
                p->plateau_jeu[i][j] = NULL;
                a_retirer[nb_a_retirer] = carte;
                nb_a_retirer += 1;
            }
        }
    }
    // On mélange ce tableau en générant un entier aléatoire entre 0 et nb_a_retirer-1
    if (nb_a_retirer == 0)
    {
        actualiser_constantes_cas_general(p, coord);
        return;
    }
    int t[nb_a_retirer]; // ce tableau sert à savoir si l'indice généré a déjà été généré (t[i]=1 si i déjà sorti, 0 sinon)
    Carte melange[nb_a_retirer];
    int c = 0;                     // sert à compter le nombre de cartes rentrées dans melange
    int n = rand() % nb_a_retirer; // génère un nombre entier aléatoire entre 0 et nb_a_retirer-1
    while (c != nb_a_retirer)
    {
        while (t[n] == 1)
        {                              // tant que l'indice a déjà été traité
            n = rand() % nb_a_retirer; // génère un nombre entier aléatoire entre 0 et nb_a_retirer-1
        }
        melange[c] = a_retirer[n]; // on remplit melange grâce à a_retirer
        t[n] = 1;                  // on indique que n a été traité
        c += 1;                    // on indique qu'une carte a été ajoutée à melange, on donne l'indice pour la prochaine
    }
    // On les repose face cachée à gauche de la carte en haut à gauche du plateau
    for (i = 0; i < nb_a_retirer; i += 1)
    {
        Coord coord = p->carte_haut_gauche;
        set_est_cachee(melange[i], 1);
        poser_carte(melange[i], p, coord.i - 1, coord.j);
    }
    // Actualisation des constantes du plateau
    p->cartes_non_retournees_manche += nb_a_retirer;
    p->cartes_retournees_manche -= nb_a_retirer;
    p->avant_derniere_carte_retournee.i = p->derniere_carte_retournee.i;
    p->avant_derniere_carte_retournee.j = p->derniere_carte_retournee.j;
    p->derniere_carte_retournee.i = coord.i;
    p->derniere_carte_retournee.j = coord.j;
}

void retourne_Soiree_sans_alcool(Plateau p, Faction f, int score, Coord coord)
{
    int i, j;
    int alcool_retourne = 0;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Alcool)
            {
                alcool_retourne = 1;
            }
        }
    }
    if (alcool_retourne == 1)
    {
        for (i = 0; i < 129; i += 1)
        {
            for (j = 0; j < 129; j += 1)
            {
                Carte carte = p->plateau_jeu[i][j];
                if (carte != NULL && get_est_cachee(carte) == 0 && (get_id(carte) == FISE || get_id(carte) == FISA || get_id(carte) == FC))
                {
                    p->plateau_jeu[i][j] = NULL;
                    p->cartes_retournees_manche -= 1;
                }
            }
        }
        int premiere_ligne = p->carte_haut_gauche.i;
        int derniere_ligne = p->carte_bas_droite.i;
        for (j = 0; j < 129; j += 1)
        {
            Carte c1 = p->plateau_jeu[premiere_ligne][j];
            if (c1 != NULL)
            {
                if (get_est_cachee(c1) == 0)
                {
                    p->cartes_retournees_manche -= 1;
                }
                else
                {
                    p->cartes_non_retournees_manche -= 1;
                }
                p->plateau_jeu[premiere_ligne][j] = NULL;
            }
            Carte c2 = p->plateau_jeu[derniere_ligne][j];
            if (c2 != NULL)
            {
                if (get_est_cachee(c2) == 0)
                {
                    p->cartes_retournees_manche -= 1;
                }
                else
                {
                    p->cartes_non_retournees_manche -= 1;
                }
                p->plateau_jeu[derniere_ligne][j] = NULL;
            }
        }
    }
    else
    {
        set_pts_DDRS_manche(f, score + 5);
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Alcool(Plateau p, Coord coord)
{
    Carte c1 = p->plateau_jeu[coord.i - 1][coord.j];
    if (c1 != NULL)
    {
        if (get_est_cachee(c1) == 0)
        {
            p->cartes_retournees_manche -= 1;
        }
        else
        {
            p->cartes_non_retournees_manche -= 1;
        }
        p->plateau_jeu[coord.i - 1][coord.j] = NULL;
    }
    Carte c2 = p->plateau_jeu[coord.i + 1][coord.j];
    if (c2 != NULL)
    {
        if (get_est_cachee(c2) == 0)
        {
            p->cartes_retournees_manche -= 1;
        }
        else
        {
            p->cartes_non_retournees_manche -= 1;
        }
        p->plateau_jeu[coord.i + 1][coord.j] = NULL;
    }
    Carte c3 = p->plateau_jeu[coord.i][coord.j - 1];
    if (c3 != NULL)
    {
        if (get_est_cachee(c3) == 0)
        {
            p->cartes_retournees_manche -= 1;
        }
        else
        {
            p->cartes_non_retournees_manche -= 1;
        }
        p->plateau_jeu[coord.i][coord.j - 1] = NULL;
    }
    Carte c4 = p->plateau_jeu[coord.i][coord.j + 1];
    if (c4 != NULL)
    {
        if (get_est_cachee(c4) == 0)
        {
            p->cartes_retournees_manche -= 1;
        }
        else
        {
            p->cartes_non_retournees_manche -= 1;
        }
        p->plateau_jeu[coord.i][coord.j + 1] = NULL;
    }
    actualiser_constantes_cas_general(p, coord);
}
void retourne_Cafe(Plateau p, Faction f, int score, Coord coord)
{
    int i, j;
    int ecocup_retourne = 0;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && (get_id(carte) == Alcool || get_id(carte) == The))
            {
                p->plateau_jeu[i][j] = NULL;
                p->cartes_retournees_manche -= 1;
            }
            else if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Ecocup)
            {
                ecocup_retourne = 1;
            }
        }
    }
    if (ecocup_retourne == 0)
    {
        set_pts_DDRS_manche(f, score - 1);
    }
    else
    {
        set_pts_DDRS_manche(f, score + 1);
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_The(Plateau p, Faction f, int score, Coord coord)
{
    int i, j;
    int ecocup_retourne = 0;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && (get_id(carte) == Alcool || get_id(carte) == Cafe))
            {
                p->plateau_jeu[i][j] = NULL;
                p->cartes_retournees_manche -= 1;
            }
            else if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Ecocup)
            {
                ecocup_retourne = 1;
            }
        }
    }
    if (ecocup_retourne == 0)
    {
        set_pts_DDRS_manche(f, score - 1);
    }
    else
    {
        set_pts_DDRS_manche(f, score + 1);
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Ecocup(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord)
{
    bonus_anl(f, score, f_adverse, score_adverse);
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Reprographie(Plateau p, Faction f_adverse, int score_adverse, Coord coord)
{
    int cartes_retournees[32] = {0};
    int i, j;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (get_est_cachee(carte) == 0)
            {
                id_carte id = get_id(carte);
                cartes_retournees[(int)id] += 1;
            }
        }
    }
    int nb_paires = 0;
    for (i = 0; i < 32; i += 1)
    {
        int n = cartes_retournees[i];
        nb_paires += (n * (n - 1)) / 2;
    }
    set_pts_DDRS_manche(f_adverse, score_adverse - nb_paires);
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Isolation_du_batiment(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord)
{
    bonus_anl(f, score, f_adverse, score_adverse);
    int i, j;
    int pts_gagnes_f = 0;
    int pts_gagnes_f_adverse = 0;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 1 && get_proprietaire(carte) == f)
            {
                pts_gagnes_f += 1;
            }
            else if (carte != NULL && get_est_cachee(carte) == 1 && get_proprietaire(carte) == f_adverse)
            {
                pts_gagnes_f_adverse += 1;
            }
        }
    }
    set_pts_DDRS_manche(f, score + pts_gagnes_f);
    set_pts_DDRS_manche(f_adverse, score_adverse + pts_gagnes_f_adverse);
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Parcours_sobriete_numerique(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse)
{
    bonus_anl(f, score, f_adverse, score_adverse);
    int i;
    int i_avt_d = p->avant_derniere_carte_retournee.i;
    int j_avt_d = p->avant_derniere_carte_retournee.j;
    int i_d = p->derniere_carte_retournee.i;
    int j_d = p->derniere_carte_retournee.j;
    for (i = 0; i < 129; i += 1)
    {
        int j = 0;
        while (j <= 128 && (p->plateau_jeu[i][j] == NULL || get_est_cachee(p->plateau_jeu[i][j]) == 0))
        {
            j += 1;
        }
        if (j != 129)
        {
            set_est_cachee(p->plateau_jeu[i][j], 0);
            p->cartes_non_retournees_manche -= 1;
            p->cartes_retournees_manche += 1;
            i_avt_d = i_d;
            j_avt_d = j_d;
            i_d = i;
            j_d = j;
        }
        j = 128;
        while (j >= 0 && (p->plateau_jeu[i][j] == NULL || get_est_cachee(p->plateau_jeu[i][j]) == 0))
        {
            j -= 1;
        }
        if (j != -1)
        {
            set_est_cachee(p->plateau_jeu[i][j], 0);
            p->cartes_non_retournees_manche -= 1;
            p->cartes_retournees_manche += 1;
            p->derniere_carte_retournee.i = i;
            p->derniere_carte_retournee.j = j;
            i_avt_d = i_d;
            j_avt_d = j_d;
            i_d = i;
            j_d = j;
        }
    }
    p->avant_derniere_carte_retournee.i = i_avt_d;
    p->avant_derniere_carte_retournee.j = j_avt_d;
    p->derniere_carte_retournee.i = i_d;
    p->derniere_carte_retournee.j = j_d;
}

void retourne_Heures_supplementaires(Plateau p, Faction f_adverse, int score_adverse, Coord coord)
{
    int i, j;
    int malus = 0;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Heures_supplementaires)
            {
                malus -= 3;
            }
        }
    }
    set_pts_DDRS_manche(f_adverse, score_adverse + malus);
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Kahina_Bouchama(Plateau p, Coord coord)
{
    if (p->cartes_non_retournees_manche == 0)
    {
        actualiser_constantes_cas_general(p, coord);
        return;
    }
    int numero_carte_supprimer = rand() % p->cartes_non_retournees_manche + 1;
    int cartes_vues = 0;
    int i = 0, j = 0;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 1)
            {
                cartes_vues += 1;
            }
            if (numero_carte_supprimer == cartes_vues)
            {
                p->plateau_jeu[i][j] = NULL;
                p->cartes_non_retournees_manche -= 1;
                actualiser_constantes_cas_general(p, coord);
                return;
            }
        }
    }
}

void retourne_Kevin_Goilard(Plateau p, Faction f, int score, Coord coord)
{
    int ligne_suppression = rand() % 129; // nombre aléatoire entre 0 et 128
    int cartes_supprimees = 0;
    int j;
    for (j = 0; j < 129; j += 1)
    {
        Carte carte = p->plateau_jeu[ligne_suppression][j];
        if (carte != NULL)
        {
            if (get_est_cachee(carte) == 0)
            {
                p->plateau_jeu[ligne_suppression][j] = NULL;
                cartes_supprimees += 1;
                p->cartes_retournees_manche -= 1;
            }
            else
            {
                p->plateau_jeu[ligne_suppression][j] = NULL;
                cartes_supprimees += 1;
                p->cartes_non_retournees_manche -= 1;
            }
        }
    }
    set_pts_DDRS_manche(f, score + 2 * cartes_supprimees);
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Massinissa_Merabet(Plateau p, Faction f, Coord coord)
{
    if (p->cartes_retournees_manche == 0)
    {
        actualiser_constantes_cas_general(p, coord);
        return;
    }
    Coord carte_a_traiter = p->derniere_carte_retournee;
    Carte carte = p->plateau_jeu[carte_a_traiter.i][carte_a_traiter.j];
    if (get_id(carte) == Massinissa_Merabet)
    {
        if (p->cartes_retournees_manche == 1)
        {
            actualiser_constantes_cas_general(p, coord);
            return;
        }
        carte_a_traiter = p->avant_derniere_carte_retournee;
        carte = p->plateau_jeu[carte_a_traiter.i][carte_a_traiter.j];
    }
    set_proprietaire(carte, f);
    id_carte id = get_id(carte);
    Faction f_adverse = f == p->factions.left ? p->factions.right : p->factions.left;
    int score = get_pts_DDRS_manche(f);
    int score_adverse = get_pts_DDRS_manche(f_adverse);
    switch_carte(p, id, carte_a_traiter, f, f_adverse, score, score_adverse);
    // Actualisation des constantes du plateau
    p->derniere_carte_retournee.i = coord.i;
    p->derniere_carte_retournee.j = coord.j;
}

void retourne_Vitera_Y(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord)
{
    if (score < score_adverse)
    {
        set_pts_DDRS_manche(f, score + 3);
        return;
    }
    if (score > score_adverse)
    {
        set_pts_DDRS_manche(f_adverse, score_adverse + 3);
        return;
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Jonas_Senizergues(Plateau p, Coord coord)
{
    int i, j;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Heures_supplementaires)
            {
                p->plateau_jeu[i][j] = NULL;
                p->cartes_retournees_manche -= 1;
            }
        }
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Fetia_Bannour(Plateau p, Faction f, int score, Coord coord)
{
    int i, j;
    int heures_sup_retournees = 0;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Heures_supplementaires)
            {
                int k;
                for (k = 0; k < 129; k += 1)
                {
                    Carte c1 = p->plateau_jeu[i][k];
                    if (c1 != NULL)
                    {
                        if (get_est_cachee(c1) == 0)
                        {
                            p->cartes_retournees_manche -= 1;
                        }
                        else
                        {
                            p->cartes_non_retournees_manche -= 1;
                        }
                        p->plateau_jeu[i][k] = NULL;
                    }
                    Carte c2 = p->plateau_jeu[k][j];
                    if (c2 != NULL)
                    {
                        if (get_est_cachee(c2) == 0)
                        {
                            p->cartes_retournees_manche -= 1;
                        }
                        else
                        {
                            p->cartes_non_retournees_manche -= 1;
                        }
                        p->plateau_jeu[k][j] = NULL;
                    }
                }
                heures_sup_retournees = 1;
            }
        }
    }
    if (heures_sup_retournees == 1)
    {
        actualiser_constantes_cas_general(p, coord);
        return;
    }
    else
    {
        int pts_gagnes = 0;
        int i, j;
        for (i = 0; i < 129; i += 1)
        {
            for (j = 0; j < 129; j += 1)
            {
                Carte carte = p->plateau_jeu[i][j];
                if (carte != NULL && get_est_cachee(carte) == 0 &&
                    (get_id(carte) == Catherine_Dubois || get_id(carte) == AnneLaure_Ligozat || get_id(carte) == Guillaume_Burel ||
                     get_id(carte) == Christophe_Mouilleron || get_id(carte) == Thomas_Lim || get_id(carte) == Julien_Forest || get_id(carte) == Dimitri_Watel))
                {
                    pts_gagnes += 1;
                }
            }
        }
        set_pts_DDRS_manche(f, score + pts_gagnes);
        actualiser_constantes_cas_general(p, coord);
    }
}

void retourne_Catherine_Dubois(Plateau p, Coord coord)
{
    int j = 0;
    while (j <= 128 && p->plateau_jeu[coord.i][j] == NULL)
    {
        j += 1;
    }
    if (j != 129)
    {
        Carte c1 = p->plateau_jeu[coord.i][j];
        if (get_est_cachee(c1) == 0)
        {
            p->cartes_retournees_manche -= 1;
        }
        else
        {
            p->cartes_non_retournees_manche -= 1;
        }
        p->plateau_jeu[coord.i][j] = NULL;
    }
    int i = 0;
    while (i <= 128 && p->plateau_jeu[i][coord.j] == NULL)
    {
        i += 1;
    }
    if (i != 129)
    {
        Carte c2 = p->plateau_jeu[i][coord.j];
        if (get_est_cachee(c2) == 0)
        {
            p->cartes_retournees_manche -= 1;
        }
        else
        {
            p->cartes_non_retournees_manche -= 1;
        }
        p->plateau_jeu[i][coord.j] = NULL;
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_AnneLaure_Ligozat(Plateau p, Faction f, int score, Coord coord)
{
    set_carte_anl_retournee(f, 1);
    int i, j;
    int pts_gagnes = 0;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && (get_id(carte) == EcologIIE || get_id(carte) == Ecocup || get_id(carte) == Isolation_batiment || get_id(carte) == Parcours_sobriete_numerique))
            {
                pts_gagnes += 3;
            }
        }
    }
    set_pts_DDRS_manche(f, score + pts_gagnes);
    Coord bas_droite = p->carte_bas_droite;
    Carte c1 = p->plateau_jeu[bas_droite.i][bas_droite.j];
    if (get_est_cachee(c1) == 0)
    {
        p->cartes_retournees_manche -= 1;
    }
    else
    {
        p->cartes_non_retournees_manche -= 1;
    }
    p->plateau_jeu[bas_droite.i][bas_droite.j] = NULL;
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Guillaume_Burel(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord)
{
    if (score_adverse > score)
    {
        set_pts_DDRS_manche(f, score + 3);
        set_pts_DDRS_manche(f_adverse, score_adverse - 3);
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Christophe_Mouilleron(Plateau p, Coord coord)
{
    int i, j;
    int heures_sup_retournees = 0;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Heures_supplementaires)
            {
                heures_sup_retournees = 1;
            }
        }
    }
    if (heures_sup_retournees == 1)
    {
        for (i = 0; i < 129; i += 1)
        {
            for (j = 0; j < 129; j += 1)
            {
                Carte carte = p->plateau_jeu[i][j];
                if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) != Christophe_Mouilleron && get_id(carte) != Heures_supplementaires)
                {
                    p->plateau_jeu[i][j] = NULL;
                    p->cartes_retournees_manche -= 1;
                }
            }
        }
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Thomas_Lim(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord)
{
    int i, j;
    int JF_retourne = 0;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Julien_Forest)
            {
                JF_retourne = 1;
            }
        }
    }
    int nb_FISE;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == FISE)
            {
                nb_FISE += 1;
            }
        }
    }
    if (JF_retourne == 0)
    {
        set_pts_DDRS_manche(f, score + 3 * nb_FISE);
    }
    else
    {
        set_pts_DDRS_manche(f_adverse, score_adverse - nb_FISE);
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Julien_Forest(Plateau p, Faction f, int score, Coord coord)
{
    int i, j;
    int cafe_retourne = 0;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Cafe)
            {
                cafe_retourne = 1;
            }
        }
    }
    int nb_FISE;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == FISE)
            {
                nb_FISE += 1;
            }
        }
    }
    if (cafe_retourne == 1)
    {
        set_pts_DDRS_manche(f, score + 6 * nb_FISE);
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Dimitri_Watel(Plateau p, Faction f, int score, Coord coord)
{
    int i, j;
    int the_retourne = 0;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == The)
            {
                the_retourne = 1;
            }
        }
    }
    int nb_FISA_FC;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && (get_id(carte) == FISA || get_id(carte) == FC))
            {
                nb_FISA_FC += 1;
            }
        }
    }
    if (the_retourne == 1)
    {
        set_pts_DDRS_manche(f, score + 3 * nb_FISA_FC);
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Djibril_Aurelien_Dembele_Cabot(Plateau p, Faction f, int score, Coord coord)
{
    int j;
    int nb_retournees_ligne = 0;
    for (j = 0; j < 129; j += 1)
    {
        Carte carte = p->plateau_jeu[coord.i][j];
        if (get_est_cachee(carte) == 0)
        {
            nb_retournees_ligne += 1;
        }
    }
    if (nb_retournees_ligne >= 3)
    {
        set_pts_DDRS_manche(f, score + 5);
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Eric_Lejeune(Plateau p, Coord coord)
{
    int a_choisir = p->cartes_retournees_manche < 5 ? p->cartes_retournees_manche : 5;
    int *t = malloc(a_choisir * sizeof(int));
    t[0] = rand() % p->cartes_retournees_manche + 1; // nombre aléatoire entre 1 et le nombre de cartes retournées inclus
    int k;
    for (k = 1; k < a_choisir; k += 1)
    {
        int est_deja_tombe = 1;
        int n;
        while (est_deja_tombe == 1)
        {
            n = rand() % p->cartes_retournees_manche + 1;
            est_deja_tombe = 0;
            int j;
            for (j = 0; j < k; j += 1)
            {
                if (n == t[j])
                {
                    est_deja_tombe = 1;
                }
            }
        }
        t[k] = n;
    }
    Carte *supp = malloc(a_choisir * sizeof(Carte));
    int *indice_i = malloc(a_choisir * sizeof(int));
    int *indice_j = malloc(a_choisir * sizeof(int));
    int remplissage = 0;
    int compte_cartes_retournees = 0;
    int i, j;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (get_est_cachee(carte) == 0)
            {
                compte_cartes_retournees += 1;
                int k;
                for (k = 0; k < a_choisir; k += 1)
                {
                    if (t[k] == compte_cartes_retournees)
                    {
                        supp[remplissage] = carte;
                        indice_i[remplissage] = i;
                        indice_j[remplissage] = j;
                        remplissage += 1;
                    }
                }
            }
        }
    }
    int est_prof = 0;
    for (i = 0; i < a_choisir; i += 1)
    {
        if (get_id(supp[i]) == Catherine_Dubois || get_id(supp[i]) == AnneLaure_Ligozat || get_id(supp[i]) == Guillaume_Burel ||
            get_id(supp[i]) == Christophe_Mouilleron || get_id(supp[i]) == Thomas_Lim || get_id(supp[i]) == Julien_Forest || get_id(supp[i]) == Dimitri_Watel)
        {
            est_prof = 1;
        }
    }
    if (est_prof == 1)
    {
        int *t = malloc(a_choisir * sizeof(int)); // ce tableau sert à savoir si l'indice généré a déjà été généré (t[i]=1 si i déjà sorti, 0 sinon)
        Carte *melange = malloc(a_choisir * sizeof(Carte));
        int c = 0;                  // sert à compter le nombre de cartes rentrées dans melange
        int n = rand() % a_choisir; // génère un nombre entier aléatoire entre 0 et a_choisir-1
        while (c != a_choisir)
        {
            while (t[n] == 1)
            {                           // tant que l'indice a déjà été traité
                n = rand() % a_choisir; // génère un nombre entier aléatoire entre 0 et a_choisir-1
            }
            melange[c] = supp[n]; // on remplit melange grâce à c
            t[n] = 1;             // on indique que n a été traité
            c += 1;               // on indique qu'une carte a été ajoutée à melange, on donne l'indice pour la prochaine
        }
        // On les repose face cachée à gauche de la carte en haut à gauche du plateau
        for (i = 0; i < a_choisir; i += 1)
        {
            Coord coord = p->carte_haut_gauche;
            int t = coord.i - 1;
            p->cartes_retournees_manche -= 1;
            poser_carte(melange[i], p, t, coord.j);
        }
        free(t);
        int i;
        for (i = 0; i < a_choisir; i += 1)
        {
            melange[i] = NULL;
        }
        free(melange);
    }
    else
    {
        for (i = 0; i < a_choisir; i += 1)
        {
            p->plateau_jeu[indice_i[i]][indice_j[i]] = NULL;
            p->cartes_retournees_manche -= 1;
        }
    }
    free(indice_i);
    free(indice_j);
    for (i = 0; i < a_choisir; i += 1)
    {
        supp[i] = NULL;
    }
    free(supp);
    free(t);
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Lucienne_Pacave(Plateau p, Faction f, int score, Coord coord)
{
    int k;
    for (k = 0; k < 129; k += 1)
    {
        Carte carte1 = p->plateau_jeu[k][coord.j];
        Carte carte2 = p->plateau_jeu[coord.i][k];
        if (get_id(carte1) == FISA || get_id(carte2) == FISA)
        {
            set_pts_DDRS_manche(f, score + 5);
            return;
        }
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Katrin_Salhab(Plateau p, Faction f, int score, Coord coord)
{
    int DADC = 0;
    int EL = 0;
    int LP = 0;
    int i, j;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0)
            {
                if (get_id(carte) == Djibril_Aurelien_Dembele_Cabot)
                {
                    DADC = 1;
                }
                if (get_id(carte) == Eric_Lejeune)
                {
                    EL = 1;
                }
                if (get_id(carte) == Lucienne_Pacave)
                {
                    LP = 1;
                }
            }
        }
    }
    if (DADC == 1 && EL == 1 && LP == 1)
    {
        set_pts_DDRS_manche(f, score + 10);
    }
    else
    {
        for (j = 0; j < 129; j += 1)
        {
            Carte c = p->plateau_jeu[coord.i][j];
            if (c != NULL)
            {
                if (get_est_cachee(c) == 1)
                {
                    set_est_cachee(p->plateau_jeu[coord.i][j], 0);
                    p->cartes_retournees_manche += 1;
                    p->cartes_non_retournees_manche -= 1;
                }
            }
        }
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Laurent_Prevel(Plateau p, Coord coord)
{
    actualiser_constantes_cas_general(p, coord);
}

void switch_carte(Plateau p, id_carte id, Coord coord, Faction f, Faction f_adverse, int score, int score_adverse)
{
    switch (id)
    {
    case FISE:
    {
        retourne_FISE(p, f, score, coord);
        break;
    }
    case FISA:
    {
        retourne_FISA(p, f, score, coord);
        break;
    }
    case FC:
    {
        retourne_FC(p, f, score, coord);
        break;
    }
    case EcologIIE:
    {
        retourne_EcologIIE(p, f, score, f_adverse, score_adverse, coord);
        break;
    }
    case lIIEns:
    {
        retourne_lIIEns(p, coord);
        break;
    }
    case Soiree_sans_alcool:
    {
        retourne_Soiree_sans_alcool(p, f, score, coord);
        break;
    }
    case Alcool:
    {
        retourne_Alcool(p, coord);
        break;
    }
    case Cafe:
    {
        retourne_Cafe(p, f, score, coord);
        break;
    }
    case The:
    {
        retourne_The(p, f, score, coord);
        break;
    }
    case Ecocup:
    {
        retourne_Ecocup(p, f, score, f_adverse, score_adverse, coord);
        break;
    }
    case Reprographie:
    {
        retourne_Reprographie(p, f_adverse, score_adverse, coord);
        break;
    }
    case Isolation_batiment:
    {
        retourne_Isolation_du_batiment(p, f, score, f_adverse, score_adverse, coord);
        break;
    }
    case Parcours_sobriete_numerique:
    {
        retourne_Parcours_sobriete_numerique(p, f, score, f_adverse, score_adverse);
        break;
    }
    case Heures_supplementaires:
    {
        retourne_Heures_supplementaires(p, f_adverse, score_adverse, coord);
        break;
    }
    case Kahina_Bouchama:
    {
        retourne_Kahina_Bouchama(p, coord);
        break;
    }
    case Kevin_Goilard:
    {
        retourne_Kevin_Goilard(p, f, score, coord);
        break;
    }
    case Massinissa_Merabet:
    {
        retourne_Massinissa_Merabet(p, f, coord);
        break;
    }
    case Vitera_Y:
    {
        retourne_Vitera_Y(p, f, score, f_adverse, score_adverse, coord);
        break;
    }
    case Jonas_Senizergues:
    {
        retourne_Jonas_Senizergues(p, coord);
        break;
    }
    case Fetia_Bannour:
    {
        retourne_Fetia_Bannour(p, f, score, coord);
        break;
    }
    case Catherine_Dubois:
    {
        retourne_Catherine_Dubois(p, coord);
        break;
    }
    case AnneLaure_Ligozat:
    {
        retourne_AnneLaure_Ligozat(p, f, score, coord);
        break;
    }
    case Guillaume_Burel:
    {
        retourne_Guillaume_Burel(p, f, score, f_adverse, score_adverse, coord);
        break;
    }
    case Christophe_Mouilleron:
    {
        retourne_Christophe_Mouilleron(p, coord);
        break;
    }
    case Thomas_Lim:
    {
        retourne_Thomas_Lim(p, f, score, f_adverse, score_adverse, coord);
        break;
    }
    case Julien_Forest:
    {
        retourne_Julien_Forest(p, f, score, coord);
        break;
    }
    case Dimitri_Watel:
    {
        retourne_Dimitri_Watel(p, f, score, coord);
        break;
    }
    case Djibril_Aurelien_Dembele_Cabot:
    {
        retourne_Djibril_Aurelien_Dembele_Cabot(p, f, score, coord);
        break;
    }
    case Eric_Lejeune:
    {
        retourne_Eric_Lejeune(p, coord);
        break;
    }
    case Lucienne_Pacave:
    {
        retourne_Lucienne_Pacave(p, f, score, coord);
        break;
    }
    case Katrin_Salhab:
    {
        retourne_Katrin_Salhab(p, f, score, coord);
        break;
    }
    case Laurent_Prevel:
    {
        retourne_Laurent_Prevel(p, coord);
        break;
    }
    default:
        break;
    }
}

Carte retourner_carte(Plateau p)
{
    // On identifie la carte à retourner, on la retourne
    if (p->cartes_non_retournees_manche == 0)
    {
        return NULL;
    }
    Coord coord = p->carte_haut_gauche_cachee;
    Carte c = p->plateau_jeu[coord.i][coord.j];
    id_carte id = get_id(c);
    set_est_cachee(c, 0);
    p->cartes_non_retournees_manche -= 1;
    p->cartes_retournees_manche += 1;
    // On identifie la fonction propriétaire de la carte et la fonction adverse à celle-ci
    Faction f = get_proprietaire(c);
    Faction f_adverse = f == p->factions.left ? p->factions.right : p->factions.left;
    int score = get_pts_DDRS_manche(f);
    int score_adverse = get_pts_DDRS_manche(f_adverse);

    // On active l'effet de la carte
    switch_carte(p, id, coord, f, f_adverse, score, score_adverse);

    // Actualisation des cartes en haut à gauche et en bas à droite
    int i, j;
    // Cartes en haut à gauche
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            if (p->plateau_jeu[i][j] != NULL)
            {
                p->carte_haut_gauche.i = i;
                p->carte_haut_gauche.j = j;
                break;
            }
        }
    }
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            if (p->plateau_jeu[i][j] != NULL && get_est_cachee(p->plateau_jeu[i][j]) == 1)
            {
                p->carte_haut_gauche_cachee.i = i;
                p->carte_haut_gauche_cachee.j = j;
                break;
            }
        }
    }
    // Cartes en bas à droite
    for (i = 128; i >= 0; i -= 1)
    {
        for (j = 128; j >= 0; j -= 1)
        {
            if (p->plateau_jeu[i][j] != NULL)
            {
                p->carte_haut_gauche.i = i;
                p->carte_haut_gauche.j = j;
                break;
            }
        }
    }
    for (i = 128; i >= 0; i -= 1)
    {
        for (j = 128; j >= 0; j -= 1)
        {
            if (p->plateau_jeu[i][j] != NULL && get_est_cachee(p->plateau_jeu[i][j]) == 1)
            {
                p->carte_haut_gauche_cachee.i = i;
                p->carte_haut_gauche_cachee.j = j;
                break;
            }
        }
    }
    return c;
}