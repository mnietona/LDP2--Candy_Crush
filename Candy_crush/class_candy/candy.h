#ifndef __CANDY_H
#define __CANDY_H

#include "plateau.h"

/**
 * Affiche un bonbon dans la box
 * 
 */

class Candy : public Fl_PNG_Image{

 public:
  Candy (const char *filename);

};


#endif
