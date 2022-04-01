/**
 * @file carte.c
 * @author Nour Elbessi & Valentin Gardel
 * @brief Implantation de l'interface en charge des informations des cartes du jeu
 * @version 0.1
 * @date 2022-03-22
 *
 * @copyright Copyright (c) 2022
 *
 */

/**
 * @brief type concret pour la faction
 *
 */

struct StructureCarte
{
    char *nom;
    char *description;
    int nb_occ;
};
