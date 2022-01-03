#ifndef __TEXTRECTANGLE_H
#define __TEXTRECTANGLE_H

#include "rectangle.h"

/**
 * Class repris du Labo 10
 * Pemret de cree un rectangle avec une du texte a l'interieur
 */
class TextRectangle : public Rectangle, public Text{
  public:
  TextRectangle(Point center, int w, int h, string s, Fl_Color frameColor = FL_BLACK, Fl_Color fillColor = FL_WHITE) : 
  Rectangle{center, w, h,frameColor, fillColor,}, Text{s, center} {}
  void draw();
 
};

void TextRectangle::draw() {
  Rectangle::draw();
  Text::draw();
}


#endif