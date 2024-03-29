#ifndef __RECTANGLE_H
#define __RECTANGLE_H

#include "text.h"

/**
 * Class repris du Labo 2 
 * Permet de cree un rectangle sur l'ecran
 */
class Rectangle {
  Point center;
  int w, h;
  Fl_Color fillColor, frameColor;
 public:
  Rectangle(Point center, int w, int h,
            Fl_Color frameColor = FL_BLACK,
            Fl_Color fillColor = FL_WHITE);
  void draw();
};

#endif
