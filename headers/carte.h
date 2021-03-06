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

/**
 * @brief Prototype de creation_carte qui crée une carte face cachée
 * @param id l'identifiant de la carte
 * @param f la faction propriétaire de la carte
 * @return Carte
 */
Carte nouvelle_carte(id_carte id, Faction f);

/**************************************************
 * Création des prototypes des getters et setters
 ***************************************************/

/**
 * @brief Prototype de get_id qui permet de récupérer l'id de la carte
 *
 * @param c Carte
 * @return Identifiant de la carte
 */

id_carte get_id(Carte c);

/**
 * @brief Prototype de set_id qui permet d'initialiser l'id de la carte.
 *
 * @param c Carte
 * @param id Identifiant de la carte
 */

void set_id(Carte c, id_carte id);

/**
 * @brief Prototype de get_proprietaire qui permet de récupérer la faction qui possède cette carte
 *
 * @param c Carte
 * @return Faction propriétaire de la carte
 */

Faction get_proprietaire(Carte c);

/**
 * @brief Prototype de set_proprietaire qui permet d'initialiser la fonction qui possède la carte.
 *
 * @param c Carte
 * @param f Faction propriétaire de la carte
 */

void set_proprietaire(Carte c, Faction f);

/**
 * @brief Prototype de get_nom qui permet de récupérer le nom de la carte
 *
 * @param c Carte
 * @return Nom de la carte
 */

char *get_nom(Carte c);

/**
 * @brief Prototype de set_nom qui permet d'initialiser le nom de la carte.
 *
 * @param c Carte
 * @param nom_carte Nom de la carte
 */
void set_nom(Carte c, char *nom_carte);

/**
 * @brief Prototype de get_description qui permet de récupérer la description de la carte
 *
 * @param c Carte
 * @return Description de la carte
 */
char *get_description(Carte c);

/**
 * @brief Prototype de set_description qui permet d'initialiser la description de la carte.
 *
 * @param c Carte
 * @param description_carte Description de la carte
 */
void set_description(Carte c, char *description_carte);

/**
 * @brief Prototype de get_nb_occ qui permet de récupérer le nombre d'occurences d'une carte
 *
 * @param c Carte
 * @return Nombre d'occurences de la carte dans la pioche de chaque faction
 */
int get_nb_occ(Carte c);

/**
 * @brief Prototype de set_nb_occ qui permet d'initialiser le nombre d'occurences d'une carte
 *
 * @param c Carte
 * @param x Nombre d'occurences de la carte dans la pioche de chaque faction
 */
void set_nb_occ(Carte c, int x);

/**
 * @brief Prototype de get_est_cachee qui permet de récupérer un entier qui indique si la face est cachée ou pas
 *
 * @param c Carte
 * @return 1 si la carte est face cachée, 0 sinon
 */
int get_est_cachee(Carte c);

/**
 * @brief Prototype de set_est_cachee qui permet de changer la valeur associé à la face d'une carte: 0 Face non cachée et 1 face cachée
 *
 * @param c Carte
 * @param x 1 si la carte est face cachée, 0 sinon
 */
void set_est_cachee(Carte c, int x);

/**
 * @brief Prototype de get_nb_occ qui permet de récupérer nb_occ[i]
 *
 * @param i Identifiant de la carte dont il faut récupérer le nombre d'occurences
 * @return Nombre d'occurences de la carte
 */
int get_nb_occ_vg(int i);

/**
 * @brief Prototype de get_nom_carte qui permet de récupérer nom_carte[i]
 *
 * @param i Identifiant de la carte dont il faut récupérer le nom
 * @return Nom de la carte
 */
char *get_nom_carte_vg(int i);

/**
 * @brief Prototype de get_description qui permet de récupérer description[i]
 *
 * @param i Identifiant de la carte dont il faut récupérer la description
 * @return Description de la carte
 */
char *get_description_vg(int i);

#endif