/*
Cours : INFO F 202
Projet : Candy Crush
Auteurs : NIETO NAVARRETE Matias, QUERINJEAN Arnaud
Date de remise : 13 janvier 2021
*/
#ifndef __CANDY_H
#define __CANDY_H

#include "plateau.h"

/**
 * Affiche un bonbon dans la box
 * trouver sur https://github.com/BDMR21/candy_crush
 */

class Candy : public Fl_PNG_Image{

 public:
  Candy (const char *filename);

};


#endif
