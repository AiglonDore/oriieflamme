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
    Coord carte_haut_gauche;
    Coord carte_bas_droite;
    int numero_manche;
    int cartes_retournees_manche;
    int cartes_non_retournees_manche;
};

void init_pioche(Faction f) {
    int i;
    Pioche pioche;
    pioche = get_pioche(f);
    for (i=0;i<32;i+=1) {
        int j = nb_occ[i];
        while (j!=0) {
            Carte c;
            set_id(c, (id_carte) i);
            set_nom_faction(c, nom_carte[i]);
            set_proprietaire(c, f);
            set_description(c, description[i]);
            set_nb_occ(c, nb_occ[i]);
            set_est_cachee(c, 1);
            ajout_pioche(pioche, c);
            j-=1;
        }
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
    set_carte_anl_retournee(faction1, 0);
    set_carte_anl_retournee(faction2, 0);
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
    Carte main[8] = { NULL };
    set_main(p->factions.left, main);
    set_main(p->factions.right, main);
    // On initialise le plateau de jeu
    int i, j;
    for (i=0; i<129; i+=1) {
        for (j=0; j<129; j+=1) {
            p->plateau_jeu[i][j] = NULL;
        }
    }
    // On initialise les paramètres du plateau (on a choisi -1 arbitraitement)
    p->cartes_retournees_manche=0;
    p->cartes_non_retournees_manche=0;
    p->numero_manche+=1;
    p->derniere_carte_posee.i = -1;
    p->derniere_carte_posee.j = -1;
    p->derniere_carte_retournee.i = -1;
    p->derniere_carte_retournee.j = -1;
    p->avant_derniere_carte_retournee.i = -1;
    p->avant_derniere_carte_retournee.j = -1;
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

void poser_carte(Carte c, Plateau p, int i, int j) { // on suppose que i et j sont légales
    Coord derniere_carte = p->derniere_carte_posee;
    p->cartes_non_retournees_manche+=1;
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

Carte retourner_carte(Plateau p) {
    // On identifie la carte à retourner, on la retourne
    if (p->cartes_non_retournees_manche==0) {
        return NULL;
    }
    Coord coord = p->carte_haut_gauche;
    Carte c = p->plateau_jeu[coord.i][coord.j];
    id_carte id = get_id(c);
    set_est_cachee(c, 0);
    // On identifie la fonction propriétaire de la carte et la fonction adverse à celle-ci
    Faction f = get_proprietaire(c);
    Faction f_adverse = f==p->factions.left ? p->factions.right : p->factions.left;
    int score = get_pts_DDRS_manche(f);
    int score_adverse = get_pts_DDRS_manche(f_adverse);
    // On actualise le nombre de cartes retournées
    p->cartes_retournees_manche+=1;
    switch(id) {
        case FISE : {
            set_pts_DDRS_manche(f, score+1);
            break;
        }
        case FISA : {
            if (p->cartes_retournees_manche%2==0) {
                set_pts_DDRS_manche(f, score+2);
            }
            break;
        }
        case FC : {
            int i, j;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_id(carte)==FC && get_est_cachee(carte)==0) {
                        set_pts_DDRS_manche(f, score+4);
                        break;
                    }
                }
            }
            break;
        }
        case EcologIIE : {
            int pts_gagnes = 0;
            int i, j;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && (get_id(carte)==FISE || get_id(carte)==FISA || get_id(carte)==FC)) {
                        pts_gagnes+=1;
                    }
                }
            }
            set_pts_DDRS_manche(f, score+pts_gagnes);
            break;
        }
        case lIIEns : {
            // On enlève les cartes FISE/FISA/FC retournées du plateau, on les stocke dans a_retirer
            Carte a_retirer[16]; // il y a 16 cartes sur le plateau
            int nb_a_retirer = 0;
            int i,j;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && (get_id(carte)==FISE || get_id(carte)==FISA || get_id(carte)==FC)) {
                        p->plateau_jeu[i][j] = NULL;
                        a_retirer[nb_a_retirer] = carte;
                        nb_a_retirer+=1;
                    }
                }
            }
            // On mélange ce tableau en génénrant un entier aléatoire entre 0 et nb_a_retirer-1
            if (nb_a_retirer==0) {
                break;
            }
            int t[nb_a_retirer]; // ce tableau sert à savoir si l'indice généré a déjà été généré (t[i]=1 si i déjà sorti, 0 sinon)
            Carte melange[nb_a_retirer];
            int c = 0; // sert à compter le nombre de cartes rentrées dans melange
            int n = rand()%nb_a_retirer; // génère un nombre entier aléatoire entre 0 et nb_a_retirer-1
            while (c!=nb_a_retirer) {
                while (t[n]==1) { // tant que l'indice a déjà été traité
                    n = rand()%nb_a_retirer; // génère un nombre entier aléatoire entre 0 et nb_a_retirer-1
                }
                melange[c] = a_retirer[n]; // on remplit melange grâce à a_retirer
                t[n] = 1; // on indique que n a été traité
                c+=1; // on indique qu'une carte a été ajoutée à melange, on donne l'indice pour la prochaine
            }
            // On les repose face cachée à gauche de la carte en haut à gauche du plateau
            for (i=0;i<a_retirer;i+=1) {
                Coord coord = p->carte_haut_gauche;
                int t = coord.i-1;
                while (p->plateau_jeu[t][coord.j]!=NULL) {
                    t-=1;
                }
                poser_carte(melange[i], p, t, coord.j);
            }
            break;
        }
        case Soiree_sans_alcool : {
            int i,j;
            int alcool_retourne = 0;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && get_id(carte)==Alcool) {
                        alcool_retourne = 1;
                    }
                }
            }
            if (alcool_retourne == 1) {
                for (i=0;i<129;i+=1) {
                    for (j=0;j<129;j+=1) {
                        Carte carte = p->plateau_jeu[i][j];
                        if (carte!=NULL && get_est_cachee(carte)==0 && (get_id(carte)==FISE || get_id(carte)==FISA || get_id(carte)==FC)) {
                            p->plateau_jeu[i][j] = NULL;
                        }
                    } 
                }
                int premiere_ligne = p->carte_haut_gauche.i;
                int derniere_ligne = p->carte_bas_droite.i;
                for (j=0;j<129;j+=1) {
                    p->plateau_jeu[premiere_ligne][j] = NULL;
                    p->plateau_jeu[derniere_ligne][j] = NULL;
                }
            }
            else {
                set_pts_DDRS_manche(f, score+5);
            }
            break;
        }
        case Alcool : {
            p->plateau_jeu[coord.i-1][coord.j] = NULL;
            p->plateau_jeu[coord.i+1][coord.j] = NULL;
            p->plateau_jeu[coord.i][coord.j-1] = NULL;
            p->plateau_jeu[coord.i][coord.j+1] = NULL;
            break;
        }
        case Cafe : {
            int i,j;
            int ecocup_retourne = 0;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && (get_id(carte)==Alcool || get_id(carte)==The)) {
                        p->plateau_jeu[i][j] = NULL;
                    }
                    else if (carte!=NULL && get_est_cachee(carte)==0 && get_id(carte)==Ecocup) {
                        ecocup_retourne = 1;
                    }
                }
            }
            if (ecocup_retourne==0) {
                set_pts_DDRS_manche(f, score-1);
            }
            else {
                set_pts_DDRS_manche(f, score+1);
            }
            break;
        }
        case The : {
            int i,j;
            int ecocup_retourne = 0;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && (get_id(carte)==Alcool || get_id(carte)==Cafe)) {
                        p->plateau_jeu[i][j] = NULL;
                    }
                    else if (carte!=NULL && get_est_cachee(carte)==0 && get_id(carte)==Ecocup) {
                        ecocup_retourne = 1;
                    }
                }
            }
            if (ecocup_retourne==0) {
                set_pts_DDRS_manche(f, score-1);
            }
            else {
                set_pts_DDRS_manche(f, score+1);
            }
            break;
        }
        case Reprographie : {
            int cartes_retournees[32] = {0};
            int i, j;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (get_est_cachee(carte)==0) {
                        id_carte id = get_id(carte);
                        cartes_retournees[(int) id]+=1;
                    }
                }
            }
            int nb_paires=0;
            for (i=0;i<32;i+=1) {
                int n = cartes_retournees[i];
                nb_paires += (n*(n-1))/2;
            }
            set_pts_DDRS_manche(f_adverse, score-nb_paires);
            break;
        }
        case Isolation_batiment : {
            int i,j;
            int pts_gagnes_f = 0;
            int pts_gagnes_f_adverse = 0;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==1 && get_proprietaire(c)==f) {
                        pts_gagnes_f += 1;
                    }
                    else if (carte!=NULL && get_est_cachee(carte)==1 && get_proprietaire(c)==f_adverse) {
                        pts_gagnes_f_adverse += 1;
                    }
                }
            }
            set_pts_DDRS_manche(f, score+pts_gagnes_f);
            set_pts_DDRS_manche(f_adverse, score_adverse+pts_gagnes_f_adverse);
            break;
        }
        case Parcous_sobriete_numerique : {
            int i;
            for (i=0;i<129;i+=1) {
                int j=0;
                while (j<=128 && (p->plateau_jeu[i][j]==NULL || get_est_cachee(p->plateau_jeu[i][j]==0))) {
                    j+=1;
                }
                set_est_cachee(p->plateau_jeu[i][j], 0);
                j=128;
                while (j>=0 && (p->plateau_jeu[i][j]==NULL || get_est_cachee(p->plateau_jeu[i][j]==0))) {
                    j-=1;
                }
                set_est_cachee(p->plateau_jeu[i][j], 0);
            }
            break;
        }
        case Heures_supplementaires : {
            int i, j;
            int malus = 0;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && get_id(c)==Heures_supplementaires) {
                        malus -= 3;
                    }
                }
            }
            set_pts_DDRS_manche(f_adverse, score_adverse+malus);
            break;
        }
        case Kahina_Bouchama : {
            int numero_carte_supprimer = rand()%p->cartes_non_retournees_manche+1;
            int cartes_vues = 0;
            int i = 0, j = 0;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==1) {
                        cartes_vues+=1;
                    }
                    if (numero_carte_supprimer==cartes_vues) {
                        p->plateau_jeu[i][j] = NULL;
                        break;
                    }
                }
            }
            break;
        }
        case Kevin_Goilard : {
            int ligne_suppression = rand()%129;
            int cartes_supprimees = 0;
            int j;
            for (j=0;j<128;j+=1) {
                Carte carte = p->plateau_jeu[ligne_suppression][j];
                if (carte!=NULL) {
                    p->plateau_jeu[ligne_suppression][j] = NULL;
                    cartes_supprimees += 1;
                }
            }
            set_pts_DDRS_manche(f, score+2*cartes_supprimees);
            break;
        }
        case Massinissa_Merabet : {
            Coord derniere_carte_retournee = p->derniere_carte_retournee;
            Carte carte = p->plateau_jeu[derniere_carte_retournee.i][derniere_carte_retournee.j];
            if (get_id(carte)==Massinissa_Merabet) {
                Coord avant_derniere_carte_retournee = p->avant_derniere_carte_retournee;
                carte = p->plateau_jeu[avant_derniere_carte_retournee.i][avant_derniere_carte_retournee.j];
            }
            set_proprietaire(carte, f);
            id_carte id = get_id(carte);
            /**
             * @TODO
             * 
             */
            break;
        }
        case Vitera_Y : {
            if (score<score_adverse) {
                set_pts_DDRS_manche(f, score+3);
                break;
            }
            else if (score>score_adverse) {
                set_pts_DDRS_manche(f_adverse, score_adverse+3);
                break;
            }
            else {
                break;
            }
        }
        case Jonas_Senizergues : {
            int i, j;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && get_id(carte)==Heures_supplementaires) {
                        p->plateau_jeu[i][j] = NULL;
                    }
                }
            }
            break;
        }
        case Fetia_Bannour : {
            int i, j;
            int heures_sup_retournees = 0;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && get_id(carte)==Heures_supplementaires) {
                        int k;
                        for (k=0;k<129;k+=1) {
                            p->plateau_jeu[i][k] = NULL;
                            p->plateau_jeu[k][j] = NULL;
                        }
                        heures_sup_retournees = 1;
                    }
                }
            }
            if (heures_sup_retournees==1) {
                break;
            }
            else {
                int pts_gagnes = 0;
                int i, j;
                for (i=0;i<129;i+=1) {
                    for (j=0;j<129;j+=1) {
                        Carte carte = p->plateau_jeu[i][j];
                        if (carte!=NULL && get_est_cachee(carte)==0 && 
                        (get_id(carte)==Catherine_Dubois || get_id(carte)==AnneLaure_Ligozat || get_id(carte)==Guillaume_Burel ||
                        get_id(carte)==Christophe_Mouilleron || get_id(carte)==Thomas_Lim || get_id(carte)==Julien_Forest || get_id(carte)==Dimitri_Watel)) {
                            pts_gagnes += 1;
                        }
                    }
                }
                set_pts_DDRS_manche(f, score+pts_gagnes);
            }
            break;
        }
        case Catherine_Dubois : {
            int j = 0;
            while (p->plateau_jeu[coord.i][j]==NULL) {
                j+=1;
            }
            p->plateau_jeu[coord.i][j] = NULL;
            int i = 0;
            while (p->plateau_jeu[i][coord.j]==NULL) {
                i+=1;
            }
            p->plateau_jeu[i][coord.j] = NULL;
            break;
        }
        case AnneLaure_Ligozat : {
            set_carte_anl_retournee(f, 1);
            int i, j;
            int pts_gagnes = 0;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && (get_id(carte)==EcologIIE ||
                    get_id(carte)==Ecocup || get_id(carte)==Isolation_batiment || get_id(carte)==Parcous_sobriete_numerique)) {
                        pts_gagnes += 3;
                    }
                }
            }
            set_pts_DDRS_manche(f, score+pts_gagnes);
            // A refaire
            Coord bas_droite = p->carte_bas_droite;
            p->plateau_jeu[bas_droite.i][bas_droite.j] = NULL;
        }
        case Guillaume_Burel : {
            if (score_adverse > score) {
                set_pts_DDRS_manche(f, score+3);
                set_pts_DDRS_manche(f_adverse, score_adverse-3);
            }
            break;
        }
        case Christophe_Mouilleron : {
            int i, j;
            int heures_sup_retournees = 0;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && get_id(carte)==Heures_supplementaires) {
                        heures_sup_retournees = 1;
                    }
                }
            }
            if (heures_sup_retournees==1) {
                for (i=0;i<129;i+=1) {
                    for (j=0;j<129;j+=1) {
                        Carte carte = p->plateau_jeu[i][j];
                        if (carte!=NULL && get_est_cachee(carte)==0 && get_id(carte)!=Christophe_Mouilleron && get_id(carte)!=Heures_supplementaires) {
                            p->plateau_jeu[i][j] = NULL;
                        }
                    }
                }
            }
            break;
        }
        case Thomas_Lim : {
            int i, j;
            int JF_retourne = 0;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && get_id(carte)==Julien_Forest) {
                        JF_retourne = 1;
                    }
                }
            }
            int nb_FISE;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && get_id(carte)==FISE) { 
                        nb_FISE += 1;
                    }
                }
            }
            if (JF_retourne==0) {
                set_pts_DDRS_manche(f, score+3*nb_FISE);
            }
            else {
                set_pts_DDRS_manche(f_adverse, score_adverse-nb_FISE);
            }
            break;
        }
        case Julien_Forest : {
            int i, j;
            int cafe_retourne = 0;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && get_id(carte)==Cafe) {
                        cafe_retourne = 1;
                    }
                }
            }
            int nb_FISE;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && get_id(carte)==FISE) { 
                        nb_FISE += 1;
                    }
                }
            }
            if (cafe_retourne==1) {
                set_pts_DDRS_manche(f, score+6*nb_FISE);
            }
            break;
        }
        case Dimitri_Watel : {
            int i, j;
            int the_retourne = 0;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && get_id(carte)==The) {
                        the_retourne = 1;
                    }
                }
            }
            int nb_FISA_FC;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0 && (get_id(carte)==FISA || get_id(carte)==FC)) { 
                        nb_FISA_FC += 1;
                    }
                }
            }
            if (the_retourne==1) {
                set_pts_DDRS_manche(f, score+3*nb_FISA_FC);
            }
            break;
        }
        case Djibril_Aurelien_Dembele_Cabot : {
            int j;
            int nb_retournees_ligne = 0;
            for (j=0; j<129; j+=1) {
                Carte carte = p->plateau_jeu[coord.i][j];
                if (get_est_cachee(carte)==0) {
                    nb_retournees_ligne += 1;
                }
            }
            if (nb_retournees_ligne >= 3) {
                set_pts_DDRS_manche(f, score+5);
            }
            break;
        }
        case Eric_Lejeune : {
            int a_choisir = p->cartes_retournees_manche < 5 ? p->cartes_retournees_manche : 5;
            if (a_choisir == 0) {
                break;
            }
            int t[a_choisir];
            t[0] = rand()%a_choisir+1;
            int k;
            for (k=1;k<a_choisir;k+=1) {
                int est_deja_tombe = 1;
                int n;
                while (est_deja_tombe == 1) {
                    n = rand()%a_choisir+1;
                    est_deja_tombe = 0;
                    int j;
                    for (j=0;j<k;j+=1) {
                        if (n==t[j]) {
                            est_deja_tombe = 1;
                        }
                    }
                }
                t[k] = n;
            }
            Carte supp[a_choisir];
            int indice_i[a_choisir];
            int indice_j[a_choisir];
            int remplissage = 0;
            int compte_cartes_retournees = 0;
            int i,j;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (get_est_cachee(carte)==0) {
                        compte_cartes_retournees += 1;
                        int k;
                        for (k=0;k<a_choisir;k+=1) {
                            if (t[k]==compte_cartes_retournees) {
                                supp[remplissage] = carte;
                                indice_i[remplissage] = i;
                                indice_j[remplissage] = j;
                                remplissage += 1;
                            }
                        }
                    }
                }
            }
            int est_ok = 0;
            for (i=0;i<a_choisir;i+=1) {
                if (get_id(supp[i])==Catherine_Dubois || get_id(supp[i])==AnneLaure_Ligozat || get_id(supp[i])==Guillaume_Burel ||
                    get_id(supp[i])==Christophe_Mouilleron || get_id(supp[i])==Thomas_Lim || get_id(supp[i])==Julien_Forest || get_id(supp[i])==Dimitri_Watel) {
                        est_ok = 1;    
                }
            }
            if (est_ok == 1) {
                int t2[a_choisir]; // ce tableau sert à savoir si l'indice généré a déjà été généré (t[i]=1 si i déjà sorti, 0 sinon)
                Carte melange[a_choisir];
                int c = 0; // sert à compter le nombre de cartes rentrées dans melange
                int n = rand()%a_choisir; // génère un nombre entier aléatoire entre 0 et a_choisir-1
                while (c!=a_choisir) {
                    while (t2[n]==1) { // tant que l'indice a déjà été traité
                        n = rand()%a_choisir; // génère un nombre entier aléatoire entre 0 et a_choisir-1
                    }
                    melange[c] = supp[n]; // on remplit melange grâce à c
                    t2[n] = 1; // on indique que n a été traité
                    c+=1; // on indique qu'une carte a été ajoutée à melange, on donne l'indice pour la prochaine
                }
                // On les repose face cachée à gauche de la carte en haut à gauche du plateau
                for (i=0;i<a_choisir;i+=1) {
                    Coord coord = p->carte_haut_gauche;
                    int t = coord.i-1;
                    while (p->plateau_jeu[t][coord.j]!=NULL) {
                        t-=1;
                    }
                    poser_carte(melange[i], p, t, coord.j);
                }
            }
            else {
                for (i=0;i<a_choisir;i+=1) {
                    p->plateau_jeu[indice_i[0]][indice_j[0]] = NULL;
                }
            }
            break;
        }
        case Lucienne_Pacave : {
            int k;
            for (k=0;k<129;k+=1) {
                Carte carte1 = p->plateau_jeu[k][coord.j];
                Carte carte2 = p->plateau_jeu[coord.i][k];
                if (get_id(carte1)==FISA || get_id(carte2)==FISA) {
                    set_pts_DDRS_manche(f, score+5);
                    break;
                }
            }
            break;
        }
        case Katrin_Salhab : {
            int DADC = 0;
            int EL = 0;
            int LP = 0;
            int i, j;
            for (i=0;i<129;i+=1) {
                for (j=0;j<129;j+=1) {
                    Carte carte = p->plateau_jeu[i][j];
                    if (carte!=NULL && get_est_cachee(carte)==0) { 
                        if (get_id(carte)==Djibril_Aurelien_Dembele_Cabot) {
                            DADC = 1;
                        }
                        if (get_id(carte)==Eric_Lejeune) {
                            EL = 1;
                        }
                        if (get_id(carte)==Lucienne_Pacave) {
                            LP = 1;
                        }
                    }
                }
            }
            if (DADC==1 && EL==1 && LP==1) {
                set_pts_DDRS_manche(f, score+10);
            }
            else {
                for (j=0;j<129;j+=1) {
                    set_est_cachee(p->plateau_jeu[coord.i][j], 0);
                }
            }
            break;
        }
        case Laurent_Prevel : {
            if (p->cartes_non_retournees_manche==0) {
                set_pts_DDRS_manche(f, 1000000);
            }
            break;
        }
        default : break;
    }
    // Traitement des effets
    // Mise à jour des constantes du plateau : carte haut gauche, bas droite
    return c;
}