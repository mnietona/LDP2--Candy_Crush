#include <vector>
#include <sstream>
#include "Cell.hpp"

/**
 * 
 * 
 */
class Canvas {
  vector< vector<Cell> > cells;
  vector<vector<int> > couleur;
  vector<Cell *> liste;
  vector<Cell > horizontal;
  vector<Cell > vertical;
  
 public:
  Canvas ()
  {
    cree_plateau(3);
  }


  void cree_plateau(int niveau); // initilaise le plateau
  void mouseMove(Point mouseLoc); // VIENS DU TP
  void mouseClick(Point mouseLoc); // VIENS DU TP
  void keyPressed(int keyCode); // VIENS DU TP
  bool debut_check_horizontal(); // verifie si allignement au lancement du jeu
  bool debut_check_vertical();  // verifie si allignement au lancement du jeu
  void print(); // print le jeu sur terminal
  bool a_coter(int x0, int y0, int x1, int y1); // verifie si les 2 bombon son l'un a coter de l'autre
  void change_2_bombon(int x0, int y0, int x1, int y1); // chnage  la position du bombon dasn le jeux 
  void efface(); // efface les allignement de bombon
  void deplacement(Cell *c); // deplace le bombon si possible 
  bool alligner_horizontal(Cell horizontal); // verifie allignement horizontal et ajoute les bombon alligner dans une liste 
  bool alligner_vertical(Cell vertical); // verifie allignement vertical et ajute dasn une liste les bombon alligner 
  bool alligner(Cell c); // verifie allignement total
  void echange_bonbon(vector<Cell *> &liste); // change le deplacement du bombon sur l'interface 
  void tomber_fruits(); // fait tomber les fruit lor d'une surpression
  bool verifie_pas_0(); // verifie qu'il n'y a plus de case vide 
  void lire_fichier(const char* fichier_input); // prend un fichier pour construire plateau
  bool verif_mur(int x0,int y0,int x1,int y1); // vérifie si c'est un mur
  bool verifie_mouvement_possible_diagonal(); // vérifie si il y a des mouvements possible
  bool verifie_mouvement_possible_vertical();
  bool verifie_mouvement_possible_horizontal();
  bool verifie_mouvement_possible();

  void test();
  };
