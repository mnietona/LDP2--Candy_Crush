#include <vector>
#include <iostream>
#include <map>
#include <memory>
#include "Plateau.hpp"
#include "Candy.hpp"

using namespace std;
/**
 * 
 * 
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
                               {3, "image/vert.png",},{4, "image/jaune.png",},{5, "image/orange.png",},
                               {6, "image/mauve.png",},{7,"image/mur.png",}};


 public:
  // Constructor
  Cell(Point center, int w, int h, int fruit);

  // Methodes
  void test();
  void cree_bombon();  // fonction repreise sur github
  void deplace(Point d); // redessine le bombom a x et y 
  void toucher(int fruit,bool s); // animation lors du survelement de la souris sur bombon
  void mouseMove(Point mouseLoc); // la souris se deplace 
  void mouseClick(Point mouseLoc); // la souris clique 
  int get_color(); // renvoi la couleur du bombon
  void set_color(int new_fruit); // donne une nouvelle couleur 
  void set_center(Point new_center);  // donne un nouveau x et y au bombon
  bool est_selectionner() const; // renvoi la valeur de select
  void deselectionner();  // met selecter a faux 
  Point get_center() const; // renvoi le x et y du bombon
  
 
};