/*
Cours : INFO F 202
Projet : Candy Crush
Auteurs : NIETO NAVARRETE Matias, QUERINJEAN Arnaud
Date de remise : 13 janvier 2021
*/
#include "plateau.h"
// viens de github https://github.com/BDMR21/candy_crush
Plateau::Plateau (Fl_Boxtype b, int x, int y, int w, int h, const char *l) :
    Fl_Box (b, x, y, w, h, l){}

Point Plateau::get_position () const
{
  return {x(), y()};
} 

bool Plateau::contains (Point p) const
{
  return p.x >= x() &&
         p.x < x()+ w() &&
         p.y >= y() &&
         p.y < y() + h();
}