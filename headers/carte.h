/**
 * @file carte.h
 * @author Nour ELBESSI
 * @brief  Interface Carte : interface en charge
 * des informations des cartes jeu.
 * @date 2022-03-07
 */

#ifndef CARTE_H
#define CARTE_H

/**
 * @brief type abstrait pour la faction qu'on définira dans carte.c
 *
 */
typedef struct StructureCarte *Carte;

#include "faction.h"

/**
 * @brief Prototype de creation_carte qui permet d'initialiser une carte.
 *
 * @return Carte
 */

Carte creation_carte();

/**
 * @brief
 * Déclaration des constantes et variables globales relative aux cartes : énumération des nom de cartes
 *
 */

typedef enum nom_carte
{
    FISE,
    FISA,
    FC,
    EcologIIE,
    lIIEns,
    Soiree_sans_alcool,
    Alcool,
    Cafe,
    The,
    Ecocup,
    Reprographie,
    Isolation_batiment,
    Parcours_sobriete_numerique,
    Heures_supplementaires,
    Kahina_Bouchama,
    Kevin_Goilard,
    Massinissa_Merabet,
    Vitera_Y,
    Jonas_Senizergues,
    Fetia_Bannour,
    Catherine_Dubois,
    AnneLaure_Ligozat,
    Guillaume_Burel,
    Christophe_Mouilleron,
    Thomas_Lim,
    Julien_Forest,
    Dimitri_Watel,
    Djibril_Aurelien_Dembele_Cabot,
    Eric_Lejeune,
    Lucienne_Pacave,
    Katrin_Salhab,
    Laurent_Prevel
} id_carte;

/**************************************************
 * Création des prototypes des getters et setters
 ***************************************************/

/**
 * @brief Prototype de get_id qui permet de récupérer l'id de la carte
 *
 * @param c
 * @return id_carte
 */

id_carte get_id(Carte c);

/**
 * @brief Prototype de set_id qui permet d'initialiser l'id de la carte.
 *
 * @param c
 * @param id
 */

void set_id(Carte c, id_carte id);

/**
 * @brief Prototype de get_proprietaire qui permet de récupérer la faction qui possède cette carte
 *
 * @param c
 * @return Faction
 */

Faction get_proprietaire(Carte c);

/**
 * @brief Prototype de set_proprietaire qui permet d'initialiser la fonction qui possède la carte.
 *
 * @param c
 * @param f
 */

void set_proprietaire(Carte c, Faction f);

/**
 * @brief Prototype de get_nom qui permet de récupérer le nom de la carte
 *
 * @param c
 * @return char*
 */

char *get_nom(Carte c);

/**
 * @brief Prototype de set_nom qui permet d'initialiser le nom de la carte.
 *
 * @param c
 * @param nom_carte
 */
void set_nom(Carte c, char *nom_carte);

/**
 * @brief Prototype de get_description qui permet de récupérer la description de la carte
 *
 * @param c
 * @return char*
 */
char *get_description(Carte c);

/**
 * @brief Prototype de set_description qui permet d'initialiser la description de la carte.
 *
 * @param c
 * @param description_carte
 */
void set_description(Carte c, char *description_carte);

/**
 * @brief Prototype de get_nb_occ qui permet de récupérer le nombre d'occurences d'une carte
 *
 * @param c
 * @return int
 */
int get_nb_occ(Carte c);

/**
 * @brief Prototype de set_nb_occ qui permet d'initialiser le nombre d'occurences d'une carte
 *
 * @param c
 * @param x
 * @return int
 */
void set_nb_occ(Carte c, int x);

/**
 * @brief Prototype de get_est_cachee qui permet de récupérer un entier qui indique si la face est cachée ou pas
 *
 * @param c
 * @return int
 */
int get_est_cachee(Carte c);

/**
 * @brief Prototype de set_est_cachee qui permet de changer la valeur associé à la face d'une carte: 0 Face non cachée et 1 face cachée
 *
 * @param c
 * @param x
 */
void set_est_cachee(Carte c, int x);

/**
 * @brief Prototype de get_nb_occ qui permet de récupérer nb_occ[i]
 *
 * @param i
 * @return int
 */
int get_nb_occ_vg(int i);

/**
 * @brief Prototype de get_nom_carte qui permet de récupérer nom_carte[i]
 *
 * @param i
 * @return char *
 */
char *get_nom_carte_vg(int i);

/**
 * @brief Prototype de get_description qui permet de récupérer description[i]
 *
 * @param i
 * @return char *
 */
char *get_description_vg(int i);

#endif