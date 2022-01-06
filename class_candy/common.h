/*
Cours : INFO F 202
Projet : Candy Crush
Auteurs : NIETO NAVARRETE Matias, QUERINJEAN Arnaud
Date de remise : 13 janvier 2021
*/
#ifndef __COMMON_H
#define __COMMON_H

#include <FL/fl_ask.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Button.H>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <vector>
#include <unistd.h>
#include <map>
#include <memory>
#include <iostream>
#include <string.h>
#include <mutex>
#include <algorithm>
#include <fstream>
#include <stdio.h>								
#include <stdlib.h>	

using namespace std;
const int windowWidth = 1080;
const int windowHeight = 720;
const double refreshPerSecond = 60;


struct Point {
  int x, y;
};

#endif
