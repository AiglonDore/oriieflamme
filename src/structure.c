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

#include "../headers/carte.h"
#include "../headers/faction.h"
#include "../headers/structure.h"

/**
 * @brief type concret de pile pour la pioche d'une faction
 *
 */

struct s_pioche
{
  Carte t[32];
  int top;
};

Pioche creation_pioche_vide()
{
  Pioche p;
  p->top = -1;
  return p;
}

int pioche_est_vide(Pioche p)
{
  return (p->top < 0 ? 1 : 0);
}

void ajout_pioche(Pioche p, Carte c)
{
  p->top += 1;
  p->t[p->top] = c;
}

Carte enleve_pioche(Pioche p)
{
  Carte c;
  c = p->t[p->top];
  p->top -= 1;
  return c;
}
