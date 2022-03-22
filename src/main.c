/**
 * @file main.c
 * @author Thomas Roiseux (thomas.roiseux@ensiie.fr)
 * @brief Fichier principal qui contrôle le programme
 * @version 0.1
 * @date 2022-03-07
 */

#include <stdlib.h>

#include "../hearders/interface.h"
#include "../hearders/carte.h"
#include "../hearders/faction.h"
#include "../hearders/plateau.h"

/**
 * @brief Fonction qui contrôle la phase 1
 * 
 * @param p Plateau de jeu.
 */
void phase1(Plateau p)
{
    Factions_en_jeu factions = factions_plateau(p);//Type concret donc free inutile
    melanger_pioche(factions.left);
    melanger_pioche(factions.right);
    piocher(factions.left);
    piocher(factions.right);
    //Joueur 1
    affiche_main(factions.left);
    if (!a_remelange(factions.left) && utiliser_option(factions.left))
    {
        melanger(factions.left);
    }
    //Joueur 2
    affiche_main(factions.right);
    if (!a_remelange(factions.right) && utiliser_option(factions.right))
    {
        melanger(factions.right);
    }
    for (int i = 8; i > 0; i--)
    {
        affiche_main(factions.left);
        Carte a_poser = a_poser_face_cachee_sur_plateau(factions.left);
        IntCouple position = demande_position(p);
        poser_carte(a_poser,p,position.left,position.right);
        affiche_main(factions.right);
        a_poser = a_poser_face_cachee_sur_plateau(factions.right);
        position = demande_position(p);
        poser_carte(a_poser,p,position.left,position.right);
    }
}

/**
 * @brief Fonction qui contrôle la phase 2
 * 
 * @param p Plateau de jeu.
 */
void phase2(Plateau p)
{
    Carte carte_retournee = NULL;
    while ((carte_retournee = retourner_carte(p)) != NULL)//Condition sur la valeur de l'affectation: si retourner_carte renvoie NULL, cela signifie qu'il n'y a plus de cartes à retourner.
    {
        affiche_effets(carte_retournee);
        affiche_plateau(p);
    }
}

/**
 * @brief Fonction principale qui controle le programme.
 * @return int Code de retour
 */
int main()
{
    Plateau jeu = init_plateau();       //Initialise le plateau, les factions...
    while (nouvelle_manche(jeu))
    {
        phase1(jeu);
        phase2(jeu);
    }
    affiche_vainqueur(jeu);
    libere_plateau(jeu);
    jeu = NULL;
    return 0;
}