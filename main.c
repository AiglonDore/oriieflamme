/**
 * @file main.c
 * @author Thomas Roiseux (thomas.roiseux@ensiie.fr)
 * @brief Fichier principal qui contrôle le programme
 * @version 0.1
 * @date 2022-03-07
 */

#include <stdlib.h>

#include "interface.h"
#include "carte.h"
#include "faction.h"
#include "plateau.h"

/**
 * @brief Fonction qui contrôle la phase 1
 * 
 * @param p Plateau de jeu.
 */
void phase1(Plateau p)
{
    Factions_en_jeu factions = factions_plateau(p);//Type concret donc free inutile
    melanger(factions.left);
    melanger(factions.right);
    
}

/**
 * @brief Fonction qui contrôle la phase 2
 * 
 * @param p Plateau de jeu.
 */
void phase2(Plateau p)
{

}

/**
 * @brief Fonction principale qui controle le programme.
 * 
 * @param argc Nombre d'arguments passés à l'exécutable.
 * @param argv Liste de ces arguments
 * @return int Code de retour
 */
int main(int argc, char *argv[])
{
    Plateau jeu = init_plateau();       //Initialise le plateau, les factions...

    libere_plateau(jeu);
    jeu = NULL;
    return 0;
}