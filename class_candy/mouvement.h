#ifndef __MOUVEMENT_H
#define __MOUVEMENT_H

#include "effacer_bonbon.h"



/**
 * fait les mouvement si possible 
 * 
 */
class Mouvement: public Effacer_bonbon{
    vector<Cell *> liste;
    public:
    Mouvement(){
    }
    void print(); // print dans le terminal notre jeux 
    void change_2_bombon(int x0, int y0, int x1, int y1); // change 2 bonbon de position 
    void echange_bonbon(vector<Cell *> &liste); // change 2 bonbon de position dasn fltk 
    void deplacement(Cell *c); // dmouvement des bonbon selectionner 
    bool alligner_horizontal(Cell horizontal);  // verifie allignement horizontal
    bool alligner_vertical(Cell vertical);  // verifie allignement vertical
    bool alligner(Cell c); // renvoie vrai si allignement
    void animation(); // cree animation des alligenment
    void tomber_fruits(); // fait tomber les bonbon quand allignement 
    bool verifie_pas_0(); // verfie qu'il n'y a plus de cell sans bonbon
    bool verif_mur(int x0,int y0,int x1,int y1); // verifie que un bonbon est un mur 
    void efface_alligner_aleatoire(); // verifie qu'il y a des alignement et les suprimes
    bool verifie_mouvement_possible_officiel(); // verifie qu'il y a toujours des mouvement possible
    void reset_plateau(); // change les bonbon normaux de couleur
    bool mouvement_verif(int a, int b, int c, int d);
};


#endif


