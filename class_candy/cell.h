#ifndef __CELL_H
#define __CELL_H

#include "textrectangle.h"

/**
 * 
 *  Dessine un bonbon sur l'ecran 
 */
class Cell {

    Plateau *plateau;
    Candy *candy;
    Point center;
    int fruit;
    int w, h;
    bool selectionner = false;
    char *image;
    map<int,string> liste_bombon = {{0, "image/explosion.png",},{1, "image/bleu.png",},{2, "image/rouge.png",},
            {3, "image/vert.png",},{4, "image/jaune.png",},{5, "image/orange.png",},{6, "image/mauve.png",},{7,"image/mur.png",},
            {8,"image/r_bleu.png",},{9,"image/r_rouge.png",},{10,"image/r_vert.png",},{11,"image/r_jaune.png",},{12,"image/r_orange.png",},
            {13,"image/r_mauve.png"},{14,"image/e_bleu.png",},{15,"image/e_rouge.png",},{16,"image/e_vert.png",},{17,"image/e_jaune.png",},
            {18,"image/e_orange.png",},{19,"image/e_mauve.png"},{20,"image/couleur.png",},{27," ",}};

 public:
  // Constructor
  Cell(Point center, int w, int h, int fruit);

  // Methodes
  void cree_bombon();  // fonction repreise sur github
  void toucher(int fruit,bool s); // animation lors du survelement de la souris sur bombon
  void explosion();
  void deplace(Point d); // redessine le bombom a x et y 
  void mouseMove(Point mouseLoc); // la souris se deplace 
  void mouseClick(Point mouseLoc); // la souris clique 
  int get_color(); // renvoi la couleur du bombon
  void set_color(int new_fruit); // donne une nouvelle couleur 
  void set_center(Point new_center);  // donne un nouveau x et y au bombon
  bool est_selectionner() const; // renvoi la valeur de select
  void deselectionner();  // met selecter a faux 
  Point get_center() const; // renvoi le x et y du bombon
  
};




#endif
