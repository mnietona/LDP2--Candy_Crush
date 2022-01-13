#ifndef __CANVAS_H
#define __CANVAS_H

#include "mouvement.h"

/**
 * La class permet de cree le plateau de jeux au complet
 * 
 */
class Canvas: public Mouvement { 
  vector<vector<int> > couleur;
  vector< Cell *> cases;
  bool jouer = false;
  bool continuer = false; 
  int niveau = 0;
  public:
  
  Canvas ()
  {
      cree_plateau();
  }

  void lire_fichier(const char* fichier_input); // prend un fichier pour construire plateau
  void cree_plateau(); // initilaise le plateau
  bool debut_check_horizontal(); // verifie si allignement au lancement du jeu
  bool debut_check_vertical();  // verifie si allignement au lancement du jeu
  void mouseMove(Point mouseLoc); // vois qu'elle bonbon on touche
  void mouseClick(Point mouseLoc); // permet les mouvement
  void keyPressed(int keyCode); // touche pour lancer le jeux et options 
  bool get_jouer(); // renvoi la valeur de jouer
  void select_level(int niveau); // cree le niveau demander
};


#endif
