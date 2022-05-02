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

const int nb_manches_gagnantes = 2;

/**
 * @brief type concret vers lequel pointe le plateau de jeu
 *
 */

struct s_plateau
{
    Plateau_jeu plateau_jeu;
    Factions_en_jeu factions;
    Coord coord_derniere_carte_posee;
    Coord coord_derniere_carte_retournee;
    Carte derniere_carte_retournee;
    Coord coord_avant_derniere_carte_retournee;
    Carte avant_derniere_carte_retournee;
    Coord coord_carte_haut_gauche_cachee;
    Coord coord_carte_bas_droite_cachee;
    Coord coord_carte_haut_gauche;
    Coord coord_carte_bas_droite;
    int numero_manche;
    int cartes_retournees_manche;
    int cartes_non_retournees_manche;
    int colonne_gauche;
    int colonne_droite;
};

Plateau creation_plateau()
{
    return (malloc(sizeof(struct s_plateau)));
}
/*********************************************************
 * Implémentation des prototypes des getters et setters
 *********************************************************/

Carte get_carte_at(Plateau p, int i, int j)
{
    return p->plateau_jeu[i][j];
}

Factions_en_jeu get_factions(Plateau p)
{
    return p->factions;
}

Coord get_coord_derniere_carte_posee(Plateau p)
{
    return p->coord_derniere_carte_posee;
}

Coord get_coord_derniere_carte_retournee(Plateau p)
{
    return p->coord_derniere_carte_retournee;
}

Coord get_coord_avant_derniere_carte_retournee(Plateau p)
{
    return p->coord_avant_derniere_carte_retournee;
}

Carte get_derniere_carte_retournee(Plateau p)
{
    return p->derniere_carte_retournee;
}

Carte get_avant_derniere_carte_retournee(Plateau p)
{
    return p->avant_derniere_carte_retournee;
}

Coord get_coord_carte_haut_gauche(Plateau p)
{
    return p->coord_carte_haut_gauche;
}

Coord get_coord_carte_bas_droite(Plateau p)
{
    return p->coord_carte_bas_droite;
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

int get_colonne_gauche(Plateau p)
{
    return p->colonne_gauche;
}

int get_colonne_droite(Plateau p)
{
    return p->colonne_droite;
}

void set_numero_manche(Plateau p, int manche)
{
    p->numero_manche = manche;
}
/********************************************************
 * Implémentation des prototypes des fonctions du plateau
 ********************************************************/

void init_pioche(Faction f)
{
    int i;
    Pioche pioche = creation_pioche_vide(); // allocation mémoire pour la pioche
    for (i = 0; i < 32; i += 1)
    {
        int j = get_nb_occ_vg(i); // on récupère le nb d'occurences de la carte d'indice i
        while (j != 0)            // on l'ajoute j fois
        {
            ajout_pioche(pioche, nouvelle_carte(i, f));
            j -= 1;
        }
    }
    set_pioche(f, pioche); // on initialise la pioche de f ainsi construite
}

Faction init_faction(char *nom, int manches_gagnees, int a_remelange)
{
    // On crée la faction
    Faction f = creation_faction();
    set_nom_faction(f, nom);
    set_nb_manches_gagnees(f, manches_gagnees);
    set_a_remelange(f, a_remelange);

    // On initialise son score
    set_pts_DDRS_manche(f, 0);
    init_pioche(f);
    Main main = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    set_main(f, main);
    return f;
}

Plateau init_plateau()
{
    // Allocation mémoire pour le plateau
    Plateau p = creation_plateau();

    // On initialise le numéro de manche
    p->numero_manche = 0;

    // On initialise les factions du plateau
    Faction f1 = init_faction("faction 1", 0, 0);
    Faction f2 = init_faction("faction 2", 0, 0);
    char *a = nom_faction(f1); // demande à la faction 1 comment ils souhaitent s'appeler
    char *b = nom_faction(f2); // demande à la faction 2 comment ils souhaitent s'appeler
    set_nom_faction(f1, a);
    set_nom_faction(f2, b);
    p->factions.left = f1;
    p->factions.right = f2;

    // On initialise le plateau de jeu à NULL
    int i, j;
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            p->plateau_jeu[i][j] = NULL;
        }
    }
    return p;
}

void libere_plateau(Plateau p)
{
    // On doit faire attention à libérer proprement les factions en jeu
    free(get_nom_faction(p->factions.left));
    free(get_nom_faction(p->factions.right));
    supprimer_faction(p->factions.left);
    supprimer_faction(p->factions.right);
    free(p);
}

int nouvelle_manche(Plateau p)
{
    // On traite d'abord le cas où une manche vient de se terminer (plus de cartes à retourner)
    if (p->numero_manche != 0)
    {
        int score_left = get_pts_DDRS_manche(p->factions.left);
        int score_right = get_pts_DDRS_manche(p->factions.right);
        int manches_gagnees_left = get_nb_manches_gagnees(p->factions.left);
        int manches_gagnees_right = get_nb_manches_gagnees(p->factions.right);
        Carte carte = p->derniere_carte_retournee;
        // On teste si la dernière carte retournée est Laurent Prével, si elle est devenue nulle c'est forcément une autre carte car Laurent Prével n'a pas d'effet particulier
        if (carte != NULL && get_id(carte) == Laurent_Prevel)
        {
            // si c'est le cas alors la faction propriétaire a gagné la manche
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
        else
        { // sinon on compare le nombre de points DDRS
            if (score_left < score_right)
            {
                set_nb_manches_gagnees(p->factions.right, manches_gagnees_right + 1);
            }
            else if (score_left > score_right)
            {
                set_nb_manches_gagnees(p->factions.left, manches_gagnees_left + 1);
            }
            else
            { // si il y a égalité on regarde la carte la plus en haut à gauche à la fin de la partie et on identifie son propriétaire qui sera le gagnant
                Carte carte = p->plateau_jeu[p->coord_carte_haut_gauche.i][p->coord_carte_haut_gauche.j];
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
        char *name_left = get_nom_faction(p->factions.left);
        char *name_right = get_nom_faction(p->factions.right);
        int joker_left = a_remelange(p->factions.left);
        int joker_right = a_remelange(p->factions.right);
        int gagne_left = get_nb_manches_gagnees(p->factions.left);
        int gagne_right = get_nb_manches_gagnees(p->factions.right);
        supprimer_faction(p->factions.left);
        supprimer_faction(p->factions.right);
        p->factions.left = NULL;
        p->factions.right = NULL;
        int i, j;
        for (i = 0; i < 129; i += 1)
        {
            for (j = 0; j < 129; j += 1)
            {
                if (p->plateau_jeu[i][j] != NULL)
                {
                    free(p->plateau_jeu[i][j]);
                    p->plateau_jeu[i][j] = NULL;
                }
            }
        }
        p->factions.left = init_faction(name_left, gagne_left, joker_left);
        p->factions.right = init_faction(name_right, gagne_right, joker_right);
    }
    // On regarde si une faction a gagné la partie
    if (get_nb_manches_gagnees(p->factions.left) == 2 || get_nb_manches_gagnees(p->factions.right) == 2)
    {
        return 0; // on retourne 0, la partie est terminée
    }
    // On initialise les paramètres du plateau (on a choisi -1 arbitraitement)
    p->cartes_retournees_manche = 0;
    p->cartes_non_retournees_manche = 0;

    p->numero_manche += 1;

    p->coord_derniere_carte_posee.i = -1;
    p->coord_derniere_carte_posee.j = -1;

    p->coord_derniere_carte_retournee.i = -1;
    p->coord_derniere_carte_retournee.j = -1;

    p->derniere_carte_retournee = NULL;

    p->coord_avant_derniere_carte_retournee.i = -1;
    p->coord_avant_derniere_carte_retournee.j = -1;

    p->avant_derniere_carte_retournee = NULL;

    p->coord_carte_bas_droite_cachee.i = -1;
    p->coord_carte_bas_droite_cachee.j = -1;
    p->coord_carte_haut_gauche_cachee.i = -1;
    p->coord_carte_haut_gauche_cachee.j = -1;

    p->coord_carte_bas_droite.i = -1;
    p->coord_carte_bas_droite.j = -1;
    p->coord_carte_haut_gauche.i = -1;
    p->coord_carte_haut_gauche.j = -1;

    p->colonne_droite = -1;
    p->colonne_gauche = -1;

    return 1; // le jeu continue
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
{
    Faction f = get_proprietaire(c);
    Carte *m = get_main(f);
    // On supprime la carte à poser de la main de la faction
    int k = 0;
    while (k < 8 && c != m[k])
    {
        k += 1;
    }
    if (k != 8 && c == m[k])
    {
        m[k] = NULL;
    }
    // On pose la carte sur le plateau (on a supposé que les coordonnées i et j sont cohérentes avec les règles du jeu)
    Coord derniere_carte = p->coord_derniere_carte_posee;
    p->cartes_non_retournees_manche += 1;
    // Cas de la première carte à poser : on regarde les coordonnées de la dernière carte posée
    if (derniere_carte.i == -1 && derniere_carte.j == -1)
    {
        // On la dispose au centre du plateau
        p->plateau_jeu[64][64] = c;
        p->coord_derniere_carte_posee.i = 64;
        p->coord_derniere_carte_posee.j = 64;
        p->coord_carte_bas_droite.i = 64;
        p->coord_carte_bas_droite.j = 64;
        p->coord_carte_haut_gauche.i = 64;
        p->coord_carte_haut_gauche.j = 64;
        p->coord_carte_bas_droite_cachee.i = 64;
        p->coord_carte_bas_droite_cachee.j = 64;
        p->coord_carte_haut_gauche_cachee.i = 64;
        p->coord_carte_haut_gauche_cachee.j = 64;
        p->colonne_gauche = 64;
        p->colonne_droite = 64;
    }
    else
    {
        p->plateau_jeu[i][j] = c;
        p->coord_derniere_carte_posee.i = i;
        p->coord_derniere_carte_posee.j = j;
        // On change éventuellement les indices des colonnes à gauche et à droite
        if (j < p->colonne_gauche)
        {
            p->colonne_gauche = j;
        }
        else if (j > p->colonne_droite)
        {
            p->colonne_droite = j;
        }
        // On change éventuellement les coordonnées des cartes en haut à gauche et en bas à droite
        if (j >= p->coord_carte_bas_droite.j && i >= p->coord_carte_bas_droite.i)
        {
            p->coord_carte_bas_droite.i = i;
            p->coord_carte_bas_droite.j = j;
            p->coord_carte_bas_droite_cachee.i = i;
            p->coord_carte_bas_droite_cachee.j = j;
        }
        else if (j <= p->coord_carte_haut_gauche.j && i <= p->coord_carte_haut_gauche.i)
        {
            p->coord_carte_haut_gauche.i = i;
            p->coord_carte_haut_gauche.j = j;
            p->coord_carte_haut_gauche_cachee.i = i;
            p->coord_carte_haut_gauche_cachee.j = j;
        }
    }
}

void actualiser_constantes_cas_general(Plateau p, Coord coord)
{
    // Actualisation des dernières cartes retournées du plateau lorsque l'on a retourné une carte située aux coordonnées coord
    p->avant_derniere_carte_retournee = p->derniere_carte_retournee;
    p->derniere_carte_retournee = p->plateau_jeu[coord.i][coord.j];
    p->coord_avant_derniere_carte_retournee = p->coord_derniere_carte_retournee;
    p->coord_derniere_carte_retournee.i = coord.i;
    p->coord_derniere_carte_retournee.j = coord.j;
}

void retourne_FISE(Plateau p, Faction f, int score, Coord coord)
{
    set_pts_DDRS_manche(f, score + 1); // on ajoute le bonus à la faction qui a posée la carte FISE
    actualiser_constantes_cas_general(p, coord);
}

void retourne_FISA(Plateau p, Faction f, int score, Coord coord)
{
    if (p->cartes_retournees_manche % 2 == 0) // on teste la parité du nombre de cartes retournées sur le plateau
    {
        set_pts_DDRS_manche(f, score + 2); // on ajoute le bonus à la faction qui a posée la carte FISA
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_FC(Plateau p, Faction f, int score, Coord coord)
{
    // On teste si une carte FC est retournée sur la plateau
    int i, j;
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_id(carte) == FC && get_est_cachee(carte) == 0)
            {
                // C'est le cas donc on ajoute le bonus à la faction qui a posée la carte FC
                set_pts_DDRS_manche(f, score + 4);
                actualiser_constantes_cas_general(p, coord);
                return; // On a fini
            }
        }
    }
    // On a trouvé aucune carte FC retournée sur le plateau, il ne se passe rien
    actualiser_constantes_cas_general(p, coord);
}

void retourne_EcologIIE(Plateau p, Faction f, int score, Coord coord)
{
    int pts_gagnes = 0;
    // On compte le nombre de cartes FISE, FISA et FC qui sont retournées sur le plateau
    int i, j;
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && (get_id(carte) == FISE || get_id(carte) == FISA || get_id(carte) == FC))
            {
                pts_gagnes += 1;
            }
        }
    }
    set_pts_DDRS_manche(f, score + pts_gagnes); // on ajoute le bonus à la faction qui a posée la carte EcologIIE
    actualiser_constantes_cas_general(p, coord);
}

void retourne_lIIEns(Plateau p, Coord coord)
{
    // On enlève les cartes FISE/FISA/FC retournées du plateau, on les stocke dans a_melanger
    int nb_a_retirer = 0;
    int i, j;
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && (get_id(carte) == FISE || get_id(carte) == FISA || get_id(carte) == FC))
            {
                nb_a_retirer += 1; // incrémentation du compteur qui sert aussi d'indexation dans a_retirer pour la prochaine carte
            }
        }
    }
    if (nb_a_retirer == 0)
    {
        actualiser_constantes_cas_general(p, coord);
        return;
    }
    Carte *a_melanger = malloc(nb_a_retirer * sizeof(Carte)); // cartes à mélanger
    int *indice_i = malloc(nb_a_retirer * sizeof(int));       // cartes à mélanger
    int *indice_j = malloc(nb_a_retirer * sizeof(int));       // cartes à mélanger
    int remplissage = 0;
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && (get_id(carte) == FISE || get_id(carte) == FISA || get_id(carte) == FC))
            {
                a_melanger[remplissage] = carte; // stockage dans a_melanger
                indice_i[remplissage] = i;
                indice_j[remplissage] = j;
                remplissage += 1;
            }
        }
    }
    // On mélange ce tableau en générant un entier aléatoire entre 0 et nb_a_retirer - 1
    Carte *melange = malloc(nb_a_retirer * sizeof(Carte));      // cartes mélangées
    int *t = (int *)calloc(nb_a_retirer, sizeof(int));          // ce tableau sert à savoir si l'indice généré a déjà été généré (t[i]=1 si i déjà sorti, 0 sinon)
    int *indice_i_melange = malloc(nb_a_retirer * sizeof(int)); // indices horizontaux cartes mélangées
    int *indice_j_melange = malloc(nb_a_retirer * sizeof(int)); // indices verticaux cartes mélangées
    int c = 0;                                                  // sert à compter le nombre de cartes rentrées dans melange
    int r = rand();
    int retour = (int)r / nb_a_retirer;
    int n = r - retour * nb_a_retirer; // génère un nombre entier aléatoire entre 0 et nb_a_retirer - 1
    while (c != nb_a_retirer)
    {
        while (t[n] == 1) // tant que l'indice a déjà été traité
        {
            r = rand();
            retour = (int)r / nb_a_retirer;
            n = r - retour * nb_a_retirer; // génère un nombre entier aléatoire entre 0 et nb_a_retirer - 1
        }
        melange[c] = a_melanger[n]; // on remplit nos tableaux à partir des précédents
        indice_i_melange[c] = indice_i[n];
        indice_j_melange[c] = indice_j[n];
        t[n] = 1; // on indique que n a été traité
        c += 1;   // on indique qu'une carte a été ajoutée à melange, on donne l'indice pour la prochaine
    }
    // On les repose face cachée à gauche de la carte en haut à gauche du plateau
    for (i = 0; i < nb_a_retirer; i += 1)
    {
        Coord coord = p->coord_carte_haut_gauche;
        id_carte id = get_id(melange[i]);
        Faction f = get_proprietaire(melange[i]);
        Carte carte_a_poser = nouvelle_carte(id, f);
        free(p->plateau_jeu[indice_i_melange[i]][indice_j_melange[i]]);
        p->plateau_jeu[indice_i_melange[i]][indice_j_melange[i]] = NULL;
        poser_carte(carte_a_poser, p, coord.i, coord.j - 1);
    }
    // Actualisation des constantes du plateau
    p->cartes_retournees_manche -= nb_a_retirer;
    actualiser_constantes_cas_general(p, coord);
    // Libération des tableaux melange et t
    free(a_melanger);
    free(melange);
    free(indice_i);
    free(indice_j);
    free(t);
    free(indice_i_melange);
    free(indice_j_melange);
}

void retourne_Soiree_sans_alcool(Plateau p, Faction f, int score, Coord coord)
{
    int i, j;
    int alcool_retourne = 0; // on teste si une carte alcool est retournée sur le plateau
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
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
        for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
        {
            for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
            {
                Carte carte = p->plateau_jeu[i][j];
                // Suppression des cartes FISE/FISA/FC retournées du plateau
                if (carte != NULL && get_est_cachee(carte) == 0 && (get_id(carte) == FISE || get_id(carte) == FISA || get_id(carte) == FC))
                {
                    free(p->plateau_jeu[i][j]);
                    p->plateau_jeu[i][j] = NULL;
                    p->cartes_retournees_manche -= 1;
                }
            }
        }
        // Suppression des première et dernière lignes du plateau
        // On pense à garder nos constantes valides
        int premiere_ligne = p->coord_carte_haut_gauche.i;
        int derniere_ligne = p->coord_carte_bas_droite.i;
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
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
                free(p->plateau_jeu[premiere_ligne][j]);
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
                free(p->plateau_jeu[derniere_ligne][j]);
                p->plateau_jeu[derniere_ligne][j] = NULL;
            }
        }
    }
    else
    {
        set_pts_DDRS_manche(f, score + 5); // ajout du bonus à la faction qui a posé la carte
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Alcool(Plateau p, Coord coord)
{
    // On supprime une par une les quatre cartes consécutives (potentiellement = NULL)
    // On veille à garder nos constantes valables
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
        free(p->plateau_jeu[coord.i - 1][coord.j]);
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
        free(p->plateau_jeu[coord.i + 1][coord.j]);
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
        free(p->plateau_jeu[coord.i][coord.j - 1]);
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
        free(p->plateau_jeu[coord.i][coord.j + 1]);
        p->plateau_jeu[coord.i][coord.j + 1] = NULL;
    }
    actualiser_constantes_cas_general(p, coord);
}
void retourne_Cafe(Plateau p, Faction f, int score, Coord coord)
{
    int i, j;
    int ecocup_retourne = 0;
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            // Suppression des cartes Thé et Alcool retournées sur le plateau
            if (carte != NULL && get_est_cachee(carte) == 0 && (get_id(carte) == Alcool || get_id(carte) == The))
            {
                free(p->plateau_jeu[i][j]);
                p->plateau_jeu[i][j] = NULL;
                p->cartes_retournees_manche -= 1;
            }
            // On teste si une carte Ecocup est retournée sur le plateau ou non
            else if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Ecocup)
            {
                ecocup_retourne = 1;
            }
        }
    }
    if (ecocup_retourne == 0)
    {
        set_pts_DDRS_manche(f, score - 1); // ajout du malus à la faction qui a posé la carte
    }
    else
    {
        set_pts_DDRS_manche(f, score + 1); // ajout du bonus à la faction qui a posé la carte
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_The(Plateau p, Faction f, int score, Coord coord)
{
    int i, j;
    int ecocup_retourne = 0;
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            // Suppression des cartes Café et Alcool retournées sur le plateau
            if (carte != NULL && get_est_cachee(carte) == 0 && (get_id(carte) == Alcool || get_id(carte) == Cafe))
            {
                free(p->plateau_jeu[i][j]);
                p->plateau_jeu[i][j] = NULL;
                p->cartes_retournees_manche -= 1;
            }
            // On teste si une carte Ecocup est retournée sur le plateau ou non
            else if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Ecocup)
            {
                ecocup_retourne = 1;
            }
        }
    }
    if (ecocup_retourne == 0)
    {
        set_pts_DDRS_manche(f, score - 1); // ajout du malus à la faction qui a posé la carte
    }
    else
    {
        set_pts_DDRS_manche(f, score + 1); // ajout du bonus à la faction qui a posé la carte
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Ecocup(Plateau p, Coord coord)
{
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Reprographie(Plateau p, Faction f_adverse, int score_adverse, Coord coord)
{
    int cartes_retournees[32] = {0}; // cartes_retournees[i] = k signifiera que la carte d'id i est retournée k fois sur le plateau
    int i, j;
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0)
            {
                id_carte id = get_id(carte);
                cartes_retournees[(int)id] += 1;
            }
        }
    }
    int nb_paires = 0;
    // S'il y a n cartes identiques retournées sur le plateau, on peut démontrer par récurrence sur n qu'il y a (n*(n-1))/2 paires
    for (i = 0; i < 32; i += 1)
    {
        int n = cartes_retournees[i];
        nb_paires += (n * (n - 1)) / 2;
    }
    set_pts_DDRS_manche(f_adverse, score_adverse - nb_paires); // ajout du malus à la faction adverse de celle qui a posé cette carte
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Isolation_du_batiment(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord)
{
    int i, j;
    int pts_gagnes_f = 0;         // nombre de cartes non retournées encore sur le plateau posées par la faction qui a posé cette carte
    int pts_gagnes_f_adverse = 0; // nombre de cartes non retournées encore sur le plateau posées par la faction adverse de celle qui a posé cette carte
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
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
    // Actualisation des scores des factions
    set_pts_DDRS_manche(f, score + pts_gagnes_f);
    set_pts_DDRS_manche(f_adverse, score_adverse + pts_gagnes_f_adverse);
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Parcours_sobriete_numerique(Plateau p)
{
    int i;
    // On récupère les informations sur les dernières cartes retournées
    // Cela nous permettra de garder actualiser nos constantes du plateau
    Carte avant_derniere = p->avant_derniere_carte_retournee;
    Carte derniere = p->derniere_carte_retournee;
    Coord coord_avant_derniere = p->coord_avant_derniere_carte_retournee;
    Coord coord_derniere = p->coord_derniere_carte_retournee;
    // Pour chaque ligne, on cherche la première et la dernière carte non retournée(s)
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        int j = 0;
        while (j <= 128 && (p->plateau_jeu[i][j] == NULL || get_est_cachee(p->plateau_jeu[i][j]) == 0))
        {
            j += 1;
        }
        if (j != 129) // si on en a trouvé une sur la ligne non nulle et cachée en partant de la gauche
        {
            set_est_cachee(p->plateau_jeu[i][j], 0);
            p->cartes_non_retournees_manche -= 1;
            p->cartes_retournees_manche += 1;
            avant_derniere = derniere;
            derniere = p->plateau_jeu[i][j];
            coord_avant_derniere = coord_derniere;
            coord_derniere.i = i;
            coord_derniere.j = j;

            // On recommence dans l'autre sens
            j = 128;
            while (j >= 0 && (p->plateau_jeu[i][j] == NULL || get_est_cachee(p->plateau_jeu[i][j]) == 0))
            {
                j -= 1;
            }
            if (j != -1) // si on en a trouvé une deuxième sur la ligne non nulle et cachée en partant de la droite
            {
                set_est_cachee(p->plateau_jeu[i][j], 0);
                p->cartes_non_retournees_manche -= 1;
                p->cartes_retournees_manche += 1;
                avant_derniere = derniere;
                derniere = p->plateau_jeu[i][j];
                coord_avant_derniere = coord_derniere;
                coord_derniere.i = i;
                coord_derniere.j = j;
            }
        }
    }
    // Actualisation des constantes du plateau
    p->avant_derniere_carte_retournee = avant_derniere;
    p->derniere_carte_retournee = derniere;
    p->coord_avant_derniere_carte_retournee = coord_avant_derniere;
    p->coord_derniere_carte_retournee = coord_derniere;
}

void retourne_Heures_supplementaires(Plateau p, Faction f_adverse, int score_adverse, Coord coord)
{
    int i, j;
    int malus = 0;
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            // Si la carte est Heures Supplémentaires et retournée sur le plateau
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Heures_supplementaires)
            {
                malus -= 3;
            }
        }
    }
    set_pts_DDRS_manche(f_adverse, score_adverse + malus); // Ajout du malus a la faction qui a posé cette carte
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Kahina_Bouchama(Plateau p, Coord coord)
{
    if (p->cartes_non_retournees_manche == 0) // dans ce cas, cette carte est la dernière à être retournée sur la plateau, on ne fait rien
    {
        actualiser_constantes_cas_general(p, coord);
        return;
    }
    int n = rand();
    int r = (int)n / p->cartes_non_retournees_manche;
    int numero_carte_supprimer = n + 1 - r * p->cartes_non_retournees_manche; // retourne un entier entre 1 et le nombre de cartes posées face cachée sur le plateau
    int cartes_vues = 0;                                                      // compteur
    // On parcourt tout le plateau jusqu'à la carte tirée au sort
    int i = 0, j = 0;
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 1)
            {
                cartes_vues += 1;                          // on incrémente notre compteur de cartes face cachée parcourues
                if (numero_carte_supprimer == cartes_vues) // on teste si nous sommes arrivés à la carte désirée
                {
                    free(p->plateau_jeu[i][j]);
                    p->plateau_jeu[i][j] = NULL; // on supprime la carte
                    p->cartes_non_retournees_manche -= 1;
                    actualiser_constantes_cas_general(p, coord);
                    return;
                }
            }
        }
    }
}

void retourne_Kevin_Goilard(Plateau p, Faction f, int score, Coord coord)
{
    int ligne_suppression = rand() % 129; // nombre aléatoire entre 0 et 128
    int cartes_supprimees = 0;
    int j;
    // On parcourt la ligne tirée au sort
    // On fait attention à préserver les constantes du plateau
    for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
    {
        Carte carte = p->plateau_jeu[ligne_suppression][j];
        if (carte != NULL)
        {
            if (get_est_cachee(carte) == 0)
            {
                free(p->plateau_jeu[ligne_suppression][j]);
                p->plateau_jeu[ligne_suppression][j] = NULL;
                cartes_supprimees += 1;
                p->cartes_retournees_manche -= 1;
            }
            else
            {
                free(p->plateau_jeu[ligne_suppression][j]);
                p->plateau_jeu[ligne_suppression][j] = NULL;
                cartes_supprimees += 1;
                p->cartes_non_retournees_manche -= 1;
            }
        }
    }
    set_pts_DDRS_manche(f, score + 2 * cartes_supprimees); // ajout du bonus à la faction qui a posé cette carte
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Massinissa_Merabet(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord)
{
    if (p->cartes_retournees_manche == 1) // dans ce cas, cette carte est la première à être retournée, on ne fait rien
    {
        actualiser_constantes_cas_general(p, coord);
        return;
    }
    Carte carte_a_traiter = p->derniere_carte_retournee; // on identifie la dernière carte retournée avant celle-ci
    Coord coord_carte_a_traiter = p->coord_derniere_carte_retournee;
    if (carte_a_traiter == NULL)
    {
        actualiser_constantes_cas_general(p, coord);
        return;
    }
    else if (get_id(carte_a_traiter) == Massinissa_Merabet) // il peut s'agir de Massinissa Merabet une et une seule fois (carte présente 1x dans chaque pioche)
    {
        if (p->cartes_retournees_manche == 2) // dans ce cas, les deux cartes Massinissa Merabet sont les deux seules à avoir été retournées, on ne fait rien
        {
            actualiser_constantes_cas_general(p, coord);
            return;
        }
        carte_a_traiter = p->avant_derniere_carte_retournee; // on change ici la carte à traiter en l'avant-dernière retournée forcément différente de Massinissa Merabet
        coord_carte_a_traiter = p->coord_avant_derniere_carte_retournee;
        if (carte_a_traiter == NULL)
        {
            actualiser_constantes_cas_general(p, coord);
            return;
        }
    }
    set_proprietaire(carte_a_traiter, f); // on change le propriétaire de cette carte en la faction qui a retourné la carte
    id_carte id = get_id(carte_a_traiter);
    actualiser_constantes_cas_general(p, coord);
    switch_carte(p, id, coord_carte_a_traiter, f, f_adverse, score, score_adverse);
}

void retourne_Vitera_Y(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord)
{
    if (score < score_adverse)
    {
        set_pts_DDRS_manche(f, score + 3); // ajout du bonus à la faction déficitaire, ici celle qui a posé la carte
        actualiser_constantes_cas_general(p, coord);
    }
    else if (score > score_adverse)
    {
        set_pts_DDRS_manche(f_adverse, score_adverse + 3); // ajout du bonus à l'autre faction qui se trouve déficitaire ici
        actualiser_constantes_cas_general(p, coord);
    }
    else
    {
        actualiser_constantes_cas_general(p, coord); // cas d'égalité, on ne fait rien
    }
}

void retourne_Jonas_Senizergues(Plateau p, Coord coord)
{
    int i, j;
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            // Suppression des cartes Heures Supplémentaires retournées sur le plateau
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Heures_supplementaires)
            {
                free(p->plateau_jeu[i][j]);
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
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            // Test si la carte Heures Supplémentaires est retournée sur le plateau
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Heures_supplementaires)
            {
                heures_sup_retournees = 1;
            }
        }
    }
    if (heures_sup_retournees == 1)
    {
        int k;
        for (k = 0; k < 129; k += 1)
        {
            // Suppression des cartes posées sur la même ligne que cette carte
            Carte c1 = p->plateau_jeu[coord.i][k];
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
                free(p->plateau_jeu[coord.i][k]);
                p->plateau_jeu[coord.i][k] = NULL;
            }
            // Suppression des cartes posées sur la même colonne que cette carte
            Carte c2 = p->plateau_jeu[k][coord.j];
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
                free(p->plateau_jeu[k][coord.j]);
                p->plateau_jeu[k][coord.j] = NULL;
            }
        }
        actualiser_constantes_cas_general(p, coord);
    }
    else
    {
        int pts_gagnes = 0;
        int i, j;
        for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
        {
            for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
            {
                Carte carte = p->plateau_jeu[i][j];
                // Test sur l'identité de la carte
                if (carte != NULL && get_est_cachee(carte) == 0 &&
                    (get_id(carte) == Catherine_Dubois || get_id(carte) == AnneLaure_Ligozat || get_id(carte) == Guillaume_Burel ||
                     get_id(carte) == Christophe_Mouilleron || get_id(carte) == Thomas_Lim || get_id(carte) == Julien_Forest || get_id(carte) == Dimitri_Watel))
                {
                    pts_gagnes += 1;
                }
            }
        }
        set_pts_DDRS_manche(f, score + pts_gagnes); // ajout du bonus à la faction ayant posé cette carte
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
    if (j != 129) // si on a trouvé une carte non nulle sur la ligne où est posée cette carte en partant de la gauche
    {
        Carte c1 = p->plateau_jeu[coord.i][j];
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
        }
        free(p->plateau_jeu[coord.i][j]);
        p->plateau_jeu[coord.i][j] = NULL;

        // On recommence dans l'autre sens
        j = 128;
        while (j >= 0 && p->plateau_jeu[coord.i][j] == NULL)
        {
            j -= 1;
        }
        if (j != -1) // si on en a trouvé une deuxième sur la ligne non nulle en partant de la droite
        {
            c1 = p->plateau_jeu[coord.i][j];
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
            }
            free(p->plateau_jeu[coord.i][j]);
            p->plateau_jeu[coord.i][j] = NULL;
        }
    }
    int i = 0;
    while (i <= 128 && p->plateau_jeu[i][coord.j] == NULL)
    {
        i += 1;
    }
    if (i != 129) // si on a trouvé une carte non nulle sur la colonne où est posée cette carte en partant du bas
    {
        Carte c2 = p->plateau_jeu[i][coord.j];
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
        }
        free(p->plateau_jeu[i][coord.j]);
        p->plateau_jeu[i][coord.j] = NULL;

        // On recommence dans l'autre sens
        i = 128;
        while (i >= 0 && p->plateau_jeu[i][coord.j] == NULL)
        {
            i -= 1;
        }
        if (i != -1) // si on en a trouvé une deuxième sur la colonne non nulle en partant du haut
        {
            c2 = p->plateau_jeu[i][coord.j];
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
                free(p->plateau_jeu[i][coord.j]);
                p->plateau_jeu[i][coord.j] = NULL;
            }
        }
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_AnneLaure_Ligozat(Plateau p, Faction f, int score, Coord coord)
{
    int i, j;
    int pts_gagnes = 0;
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            // Test sur l'identité de la carte et si elle est bien retournée sur le plateau
            if (carte != NULL && get_est_cachee(carte) == 0 && (get_id(carte) == EcologIIE || get_id(carte) == Ecocup || get_id(carte) == Isolation_batiment || get_id(carte) == Parcours_sobriete_numerique))
            {
                pts_gagnes += 3;
            }
        }
    }
    set_pts_DDRS_manche(f, score + pts_gagnes); // ajout du bonus pour la faction qui a posé cette carte
    Coord bas_droite = p->coord_carte_bas_droite_cachee;
    free(p->plateau_jeu[bas_droite.i][bas_droite.j]);
    p->plateau_jeu[bas_droite.i][bas_droite.j] = NULL; // suppression dernière carte non retournée
    p->cartes_non_retournees_manche -= 1;
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Guillaume_Burel(Plateau p, Faction f, int score, Faction f_adverse, int score_adverse, Coord coord)
{
    if (score_adverse > score)
    {
        set_pts_DDRS_manche(f, score + 3);                 // ajout du bonus pour la faction qui a posé cette carte
        set_pts_DDRS_manche(f_adverse, score_adverse - 3); // ajout du malus pour la faction adverse de celle qui a posé cette carte
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Christophe_Mouilleron(Plateau p, Coord coord)
{
    int i, j;
    int heures_sup_retournees = 0; // test si la carte Heures Supplémentaires est retournée sur le plateau
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
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
        for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
        {
            for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
            {
                Carte carte = p->plateau_jeu[i][j];
                // Suppression des cartes retournées sauf deux types : CM et HS
                if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) != Christophe_Mouilleron && get_id(carte) != Heures_supplementaires)
                {
                    free(p->plateau_jeu[i][j]);
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
    int JF_retourne = 0; // test si JF est retourné ou non sur le plateau
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Julien_Forest)
            {
                JF_retourne = 1;
            }
        }
    }
    int nb_FISE = 0; // calcul du nombre de cartes FISE retournées sur le plateau
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
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
        set_pts_DDRS_manche(f, score + 3 * nb_FISE); // ajout du bonus pour la faction qui a posé cette carte
    }
    else
    {
        set_pts_DDRS_manche(f_adverse, score_adverse - nb_FISE); // ajout du malus pour la faction adverse de celle qui a posé cette carte
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Julien_Forest(Plateau p, Faction f, int score, Coord coord)
{
    int i, j;
    int cafe_retourne = 0; // test si une carte Café est retournée sur le plateau ou non
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == Cafe)
            {
                cafe_retourne = 1;
            }
        }
    }
    int nb_FISE = 0; // calcul du nombre de cartes FISE retournées sur le plateau
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
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
        set_pts_DDRS_manche(f, score + 6 * nb_FISE); // ajout du bonus pour la faction qui a posé cette carte
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Dimitri_Watel(Plateau p, Faction f, int score, Coord coord)
{
    int i, j;
    int the_retourne = 0; // test si une carte Thé est retournée sur le plateau
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            if (carte != NULL && get_est_cachee(carte) == 0 && get_id(carte) == The)
            {
                the_retourne = 1;
            }
        }
    }
    int nb_FISA_FC = 0; // calcul du nombre de cartes FISA/FC retournées sur le plateau
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
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
        set_pts_DDRS_manche(f, score + 3 * nb_FISA_FC); // ajout du bonus pour la faction qui a posé cette carte
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Djibril_Aurelien_Dembele_Cabot(Plateau p, Faction f, int score, Coord coord)
{
    int j;
    int nb_retournees_ligne = 0;
    // Calcul du nombre de cartes retournées sur la ligne de cette carte
    for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
    {
        Carte carte = p->plateau_jeu[coord.i][j];
        if (carte != NULL && get_est_cachee(carte) == 0)
        {
            nb_retournees_ligne += 1;
        }
    }
    if (nb_retournees_ligne >= 3)
    {
        set_pts_DDRS_manche(f, score + 5); // ajout du bonus pour la faction qui a posé cette carte
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Eric_Lejeune(Plateau p, Coord coord)
{
    // On commence par déterminer le nombre de cartes à prendre au hasard : min(5, nombre de cartes retournées du plateau)
    int a_choisir = p->cartes_retournees_manche < 5 ? p->cartes_retournees_manche : 5;
    int *t = malloc(a_choisir * sizeof(int)); // allocation mémoire pour sauver les numéros des cartes tirées au sort
    int n = rand();
    int retour = (int)n / p->cartes_retournees_manche;
    t[0] = n + 1 - retour * p->cartes_retournees_manche; // nombre aléatoire entre 1 et le nombre de cartes retournées inclus
    int k, r;
    // On tire au sort les numéros des a_choisir - 1 cartes restantes
    for (k = 1; k < a_choisir; k += 1)
    {
        int est_deja_tombe = 1;
        while (est_deja_tombe == 1)
        {
            n = rand();
            retour = (int)n / p->cartes_retournees_manche;
            r = n + 1 - retour * p->cartes_retournees_manche; // nombre aléatoire entre 1 et le nombre de cartes retournées inclus
            est_deja_tombe = 0;
            // On vérifie si on a déjà ce nombre dans notre tableau de numéros
            int j;
            for (j = 0; j < k; j += 1)
            {
                if (r == t[j])
                {
                    est_deja_tombe = 1;
                }
            }
        }
        t[k] = r;
    }
    Carte *supp = malloc(a_choisir * sizeof(Carte)); // allocation mémoire pour sauver les cartes tirées au sort
    int *indice_i = malloc(a_choisir * sizeof(int)); // allocation mémoire pour sauver les indices horizontaux des cartes à supprimer
    int *indice_j = malloc(a_choisir * sizeof(int)); // allocation mémoire pour sauver les indices verticaux des cartes à supprimer
    int remplissage = 0;                             // indice pour pouvoir remplir les tableaux ci-dessus
    int compte_cartes_retournees = 0;                // compteur des cartes retournées parcourues
    int i, j;
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte carte = p->plateau_jeu[i][j];
            // On teste si elle est retournée et on regarde si elle nous intéresse
            if (carte != NULL && get_est_cachee(carte) == 0)
            {
                compte_cartes_retournees += 1;
                int k;
                for (k = 0; k < a_choisir; k += 1)
                {
                    if (t[k] == compte_cartes_retournees) // elle fait partie de notre tirage, on l'enregistre
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
    // On teste si une de ces cartes est une de ces sept personnalités
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
        // On mélange les cartes
        int *l = calloc(a_choisir, sizeof(int)); // ce tableau sert à savoir si l'indice généré a déjà été généré (t[i]=1 si i déjà sorti, 0 sinon)
        Carte *melange = malloc(a_choisir * sizeof(Carte));
        int *indice_i_melange = malloc(a_choisir * sizeof(int)); // allocation mémoire pour sauver les indices horizontaux des cartes mélangées
        int *indice_j_melange = malloc(a_choisir * sizeof(int)); // allocation mémoire pour sauver les indices verticaux des cartes mélangées
        int c = 0;                                               // sert à compter le nombre de cartes rentrées dans melange
        int n = rand() % 5;                                      // génère un nombre entier aléatoire entre 0 et 4
        while (c != a_choisir)
        {
            while (n >= a_choisir || l[n] == 1)
            {                   // tant que l'indice a déjà été traité
                n = rand() % 5; // génère un nombre entier aléatoire entre 0 et a_choisir-1
            }
            melange[c] = supp[n]; // on remplit nos tableaux grâce à supp, indice_i et indice_j
            indice_i_melange[c] = indice_i[n];
            indice_j_melange[c] = indice_j[n];
            l[n] = 1; // on indique que n a été traité
            c += 1;   // on indique qu'une carte a été ajoutée à melange, on donne l'indice pour la prochaine
        }
        // On les repose face cachée à gauche de la carte en haut à gauche du plateau
        for (i = 0; i < a_choisir; i += 1)
        {
            Coord coord = p->coord_carte_haut_gauche;
            id_carte id = get_id(melange[i]);
            Faction f = get_proprietaire(melange[i]);
            Carte carte_a_poser = nouvelle_carte(id, f);
            free(p->plateau_jeu[indice_i_melange[i]][indice_j_melange[i]]);
            p->plateau_jeu[indice_i_melange[i]][indice_j_melange[i]] = NULL;
            poser_carte(carte_a_poser, p, coord.i, coord.j - 1);
        }
        p->cartes_retournees_manche -= a_choisir;
        // On libère la mémoire allouée
        free(l);
        free(melange);
        free(indice_i_melange);
        free(indice_j_melange);
    }
    // Sinon, on supprime les cartes du plateau
    else
    {
        for (i = 0; i < a_choisir; i += 1)
        {
            free(p->plateau_jeu[indice_i[i]][indice_j[i]]);
            p->plateau_jeu[indice_i[i]][indice_j[i]] = NULL;
        }
        p->cartes_retournees_manche -= a_choisir;
    }
    // Libération de la mémoire allouée
    free(indice_i);
    free(indice_j);
    free(supp);
    free(t);
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Lucienne_Pacave(Plateau p, Faction f, int score, Coord coord)
{
    int k;
    // On parcourt la ligne et la colonne de cette carte à la recherche d'une carte FISA retournée
    for (k = 0; k < 129; k += 1)
    {
        Carte carte1 = p->plateau_jeu[k][coord.j];
        Carte carte2 = p->plateau_jeu[coord.i][k];
        if ((carte1 != NULL && get_est_cachee(carte1) == 0 && get_id(carte1) == FISA) || (carte2 != NULL && get_est_cachee(carte2) == 0 && get_id(carte2) == FISA))
        {
            set_pts_DDRS_manche(f, score + 5); // ajout du bonus correspondant à la faction qui a posé la carte
            actualiser_constantes_cas_general(p, coord);
            return;
        }
    }
    // On n'en a pas trouvé... on ne fait rien
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Katrin_Salhab(Plateau p, Faction f, int score, Coord coord)
{
    // On teste si les cartes du personnel administratif sont retournées ou non sur le plateau
    int DADC = 0; // Djibril-Aurélien Dembele-Cabot
    int EL = 0;   // Eric Lejeune
    int LP = 0;   // Lucienne Pacavé
    int i, j;
    for (i = p->coord_carte_haut_gauche.i; i <= p->coord_carte_bas_droite.i; i += 1)
    {
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
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
        set_pts_DDRS_manche(f, score + 10); // ajout du bonus correspondant à la faction qui a posé cette carte
    }
    else
    {
        // On parcourt la ligne de cette carte et on retourne les cartes face cachée sans appliquer leurs effets
        // On tient à jour nos constantes
        for (j = get_colonne_gauche(p); j <= get_colonne_droite(p); j += 1)
        {
            Carte c = p->plateau_jeu[coord.i][j];
            if (c != NULL && get_est_cachee(c) == 1)
            {
                set_est_cachee(p->plateau_jeu[coord.i][j], 0);
                p->cartes_retournees_manche += 1;
                p->cartes_non_retournees_manche -= 1;
            }
        }
    }
    actualiser_constantes_cas_general(p, coord);
}

void retourne_Laurent_Prevel(Plateau p, Coord coord)
{
    actualiser_constantes_cas_general(p, coord); // On ne fait rien, on traite son effet dans nouvelle_manche
}

void switch_carte(Plateau p, id_carte id, Coord coord, Faction f, Faction f_adverse, int score, int score_adverse)
{
    // Cette fonction sert d'aiguillage pour activer l'effet de la carte posée par la faction f
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
        retourne_EcologIIE(p, f, score, coord);
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
        retourne_Ecocup(p, coord);
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
        retourne_Parcours_sobriete_numerique(p);
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
        retourne_Massinissa_Merabet(p, f, score, f_adverse, score_adverse, coord);
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

int retourner_carte(Plateau p)
{
    if (p->cartes_non_retournees_manche == 0) // dans ce cas, on n'a rien à faire, c'est fini
    {
        return (-1);
    }
    // Sinon, on identifie la carte à retourner, on la retourne
    Coord coord = p->coord_carte_haut_gauche_cachee;
    Carte c = p->plateau_jeu[coord.i][coord.j];
    id_carte id = get_id(c);
    set_est_cachee(c, 0); // on la retourne

    // On actualise nos constantes de plateau
    p->cartes_non_retournees_manche -= 1;
    p->cartes_retournees_manche += 1;

    // On identifie la fonction propriétaire de la carte et la fonction adverse à celle-ci
    Faction f = get_proprietaire(c);
    Faction f_adverse = f == p->factions.left ? p->factions.right : p->factions.left;
    int score = get_pts_DDRS_manche(f);
    int score_adverse = get_pts_DDRS_manche(f_adverse);

    // On active l'effet de la carte
    switch_carte(p, id, coord, f, f_adverse, score, score_adverse);

    // Actualisation des cartes en haut à gauche et en bas à droite + colonnes les plus à gauche et à droite
    int i, j;
    int trouve = 0, trouve_cachee = 0;
    int gauche = 128, droite = 0;
    // Actualisation cartes en haut à gauche + colonnes les plus à gauche et à droite
    for (i = 0; i < 129; i += 1)
    {
        for (j = 0; j < 129; j += 1)
        {
            if (p->plateau_jeu[i][j] != NULL)
            {
                if (trouve == 0)
                {
                    p->coord_carte_haut_gauche.i = i;
                    p->coord_carte_haut_gauche.j = j;
                    trouve = 1;
                }
                if (trouve_cachee == 0 && get_est_cachee(p->plateau_jeu[i][j]) == 1)
                {
                    p->coord_carte_haut_gauche_cachee.i = i;
                    p->coord_carte_haut_gauche_cachee.j = j;
                    trouve_cachee = 1;
                }
                if (j < gauche)
                {
                    gauche = j;
                }
                else if (j > droite)
                {
                    droite = j;
                }
            }
        }
    }
    if (gauche == 128 && droite == 0) // aucune carte trouvée
    {
        gauche = 0;
        droite = 0;
    }
    p->colonne_gauche = gauche;
    p->colonne_droite = droite;
    trouve = 0;
    trouve_cachee = 0;
    // Actualisation des cartes en bas à droite
    for (i = 128; i >= 0; i -= 1)
    {
        for (j = 128; j >= 0; j -= 1)
        {
            if (p->plateau_jeu[i][j] != NULL)
            {
                if (trouve == 0)
                {
                    p->coord_carte_bas_droite.i = i;
                    p->coord_carte_bas_droite.j = j;
                    trouve = 1;
                }
                if (trouve_cachee == 0 && get_est_cachee(p->plateau_jeu[i][j]) == 1)
                {
                    p->coord_carte_bas_droite_cachee.i = i;
                    p->coord_carte_bas_droite_cachee.j = j;
                    trouve_cachee = 1;
                }
            }
        }
    }
    return (id);
}