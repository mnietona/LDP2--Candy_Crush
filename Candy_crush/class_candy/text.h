#ifndef __TEXT_H
#define __TEXT_H

#include "candy.h"

/**
 * Class repris du Labo 3
 * Elle permet d'ecrire du texte sur l'ecran
 * 
 */
class Text {
  Point center;
  string s;
  int fontSize;
  Fl_Color color;
 public:
  //Constructor
  Text(string s, Point center, int fontSize = 50, Fl_Color color = FL_BLACK):
    s{s}, center{center}, fontSize{fontSize}, color{color} {}
 
  //Draw
  void draw();
 
  //Setters and getters
  string getString() {
    return s;
  }
  void setString(const string &newString) {
    s = newString;
  }
  int getFontSize() {
    return fontSize;
  }
  void setFontSize(int newFontSize) {
    fontSize = newFontSize;
  }
  Point getCenter() {
    return center;
  }
  void setCenter(Point newCenter) {
    center = newCenter;
  }
};


#endif
