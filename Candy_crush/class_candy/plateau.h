#ifndef __PLATEAU_H
#define __PLATEAU_H

#include "common.h"

/**
 * Affiche des Box sur l'ecran
 * 
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
