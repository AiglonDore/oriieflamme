/**
 * @file plateau.c
 * @author Nour Elbessi & Valentin Gardel
 * @brief Implantation de l'interface pour gérer le plateau de jeu et le déroulement de la partie
 * @version 0.1
 * @date 2022-03-22
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
#include "../headers/interface.h"

/**
 * @brief type concret vers lequel pointe le plateau de jeu
 *
 */

struct s_plateau
{
    Plateau_jeu plateau_jeu;
    Coord derniere_carte_posee;
    Coord carte_haut_gauche;
    Coord carte_bas_droite;
    int numero_manche;
    Factions_en_jeu factions;
};

void init_pioche(Faction f) {
    int i;
    Pioche pioche;
    pioche = get_pioche(f);
    for (i=0;i<32;i+=1) {
        Carte c;
        set_id(c, i);
        set_nom_faction(c, nom_carte[i]);
        set_description(c, description[i]);
        set_nb_occ(c, nb_occ[i]);
        set_est_cachee(c, 1);
        ajout_pioche(pioche, c);
    }
}

Plateau init_plateau() {
    Plateau p;
    // On initialise le numéro de manche
    p->numero_manche=0;
    // On initialise les factions
    Faction faction1;
    Faction faction2;
    set_nom_faction(faction1, "Faction 1");
    set_nom_faction(faction2, "Faction 2");
    char * a = nom_faction(faction1);
    char * b = nom_faction(faction2);
    set_nom_faction(faction1, a);
    set_nom_faction(faction2, b);
    set_nb_maches_gagnees(faction1, 0);
    set_nb_maches_gagnees(faction2, 0);
    p->factions.left = faction1;
    p->factions.right = faction2;
    // Le reste de l'initialisation est commun à chaque début de manche et se fera dans nouvelle_manche
}

void libere_plateau(Plateau p) {
    return;
}

int nouvelle_manche(Plateau p) {
    // On regarde si une faction a gagné
    if (get_nb_maches_gagnees(p->factions.left)==2 || get_nb_maches_gagnees(p->factions.right)==2) {
        return 0;
    }
    // On initialise les scores des factions
    set_pts_DDRS_manche(p->factions.left, 0);
    set_pts_DDRS_manche(p->factions.right, 0);
    // On réinitialise les pioches et les mains des factions
    init_pioche(p->factions.left);
    init_pioche(p->factions.right);
    Carte * main[8] = { NULL };
    set_main(p->factions.left, main);
    set_main(p->factions.right, main);
    // On initialise le plateau de jeu
    int i, j;
    for (i=0; i<129; i+=1) {
        for (j=0; j<129; j+=1) {
            p->plateau_jeu[i][j]=NULL;
        }
    }
    // On initialise les paramètres du plateau (on a choisi -1 arbitraitement)
    p->numero_manche+=1;
    p->derniere_carte_posee.i = -1;
    p->derniere_carte_posee.j = -1;
    p->carte_bas_droite.i = -1;
    p->carte_bas_droite.j = -1;
    p->carte_haut_gauche.i = -1;
    p->carte_haut_gauche.j = -1;
    return 1;
}

Factions_en_jeu factions_plateau(Plateau p) {
    int m = p->numero_manche;
    if (m==1 || m==3) { // 1ère ou 3ème manche donc on choisit aléatoirement si on échange factions.left et factions.right ou pas
        int i = rand()%2; // génère 0 ou 1 de manière aléatoire
        if (i==0) {
            return p->factions;
        }
        else {
            Faction f = p->factions.left;
            p->factions.left = p->factions.right;
            p->factions.right = f;
            return p->factions;
        }
    }
    else { // 2ème manche donc on fait jouer en premier l'autre faction cette fois-ci
        Faction f = p->factions.left;
        p->factions.left = p->factions.right;
        p->factions.right = f;
        return p->factions;
    }
}

void poser_carte(Carte c, Plateau p, int i, int j) {
    Coord derniere_carte = p->derniere_carte_posee;
    // On vérifie la légalité de i et j
    if (abs(derniere_carte.i - i)>1 && abs(derniere_carte.j - j)>1) {
        printf("Valeurs pour i ou/et j illégales");
        exit(1);
    }
    // Cas de la première carte à poser
    if (derniere_carte.i == -1 && derniere_carte.j == -1) {
        p->plateau_jeu[64][64]=c;
        p->derniere_carte_posee.i=64;
        p->derniere_carte_posee.j=64;
        p->carte_bas_droite.i=64;
        p->carte_bas_droite.j=64;
        p->carte_haut_gauche.i=64;
        p->carte_haut_gauche.j=64;
        return;
    }
    p->plateau_jeu[i][j]=c;
    p->derniere_carte_posee.i=i;
    p->derniere_carte_posee.j=j;
    // On change éventuellement les coordonnées des cartes en haut à gauche et en bas à droite
    if (j<=p->carte_bas_droite.j && i>p->carte_bas_droite.i) {
        p->carte_bas_droite.i=i;
        p->carte_bas_droite.j=j;
        return;
    }
    else if (j>=p->carte_haut_gauche.j && i<p->carte_haut_gauche.i) {
        p->carte_haut_gauche.i=i;
        p->carte_haut_gauche.j=j;
        return;
    }
}

/**
 * @brief retourne la carte la plus en haut à gauche du plateau face visible et active son effet
 * @param p plateau valide (le pointeur doit être valide)
 * @return la carte que l'on a retourné face visible
 * @return NULL s'il n'y a plus aucune carte à retourner
 *
 */

Carte retourner_carte(Plateau p) {
    Coord coord = p->carte_haut_gauche;
    Carte c = p->plateau_jeu[coord.i][coord.j];
    set_est_cachee(c, 0);
    id_carte id = get_id(c);
    // Traitement des effets
    // Mise à jour des constantes du plateau
    return c;
}