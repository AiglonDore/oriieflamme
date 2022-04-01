/**
 * @file structure.c
 * @author Valentin Gardel (valentin.gardel@ensiie.fr)
 * @brief Implémentation de l'interface pour gérer le plateau de jeu et le déroulement de la partie
 * @version 0.1
 * @date 2022-04-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _STRUCTURE_H
#define _STRUCTURE_H
#include "../headers/carte.h"
#include "../headers/faction.h"
#include "../headers/structure.h"

/**
 * @brief type concret de pile pour la pioche d'une faction
 * 
 */

typedef struct s_pioche {
  Carte t[32];
  int top;
};

/**
 * @brief type concret pour la pioche d'une faction
 * 
 */

typedef struct s_pioche *Pioche;

/**
 * @brief Savoir si une faction a itilisé l'option de remélanger sa main et boîte à idée et de repiocher des cartes.
 * @param f une faction
 * @return 0 si la main n'a pas été remélangé 
 * @return 1 si la main a été remélangé
 */

Pioche creation_pioche_vide() {
  Pioche p;
  p->top = -1;
  return p;
}

/**
 * @brief indique si la pioche est vide ou non
 * @param p une pioche valide
 * @return 0 si la pioche n'est pas vide
 * @return 1 si la pioche est vide
 */

int pioche_est_vide(Pioche p) {
    return (p->top<0?1:0);
}

/**
 * @brief ajoute la carte à la pioche au sommet de celle-ci
 * @param p une pioche valide
 * @param c une carte valide
 */

void ajout_pioche(Pioche p, Carte c) {
  p->top+=1;
  p->t[p->top]=c;
}

/**
 * @brief enlève la carte au sommet de la pioche (on suppose la pioche non vide)
 * @param p une pioche valide
 * @return la carte qui a été retirée
 */

Carte enleve_pioche(Pioche p) {
  Carte c;
  c=p->t[p->top];
  p->top-=1;
  return c;
}

#endif // STRUCTURE_H
