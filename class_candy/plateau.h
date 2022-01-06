/*
Cours : INFO F 202
Projet : Candy Crush
Auteurs : NIETO NAVARRETE Matias, QUERINJEAN Arnaud
Date de remise : 13 janvier 2021
*/
#ifndef __PLATEAU_H
#define __PLATEAU_H
#include "common.h"

/**
 * Affiche des Box sur l'ecran
 * viens de github https://github.com/BDMR21/candy_crush
 */

class Plateau: public Fl_Box {

 public:
  // constructeur 
  Plateau (Fl_Boxtype b, int x, int y, int w, int h, const char *l);
  // renvoi les coordonnees
  Point get_position() const;
  // true si curseur est dedans
  bool contains (Point p) const;
};

#endif
