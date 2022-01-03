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

};

void Mouvement::print(){

  cout << "\n" << endl;
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
            cout<<"[" << cells[j][i].get_color() << "]; "; // on met j i opur avoir les meme position que fltk
        }
        cout<<"\n" << endl;
  }
  cout << endl;
  
}

void Mouvement::change_2_bombon(int x0, int y0, int x1, int y1){
    
    Cell sauve = cells[x0][y0];
    cells[x0][y0] = cells[x1][y1];
    cells[x1][y1] = sauve;
}

void Mouvement::echange_bonbon(vector<Cell *> &liste){
   
    Point save_center{liste[0]->get_center().x, liste[0]->get_center().y};
            
    liste[0]->deplace(liste[1]->get_center());
    liste[0]->set_center(liste[1]->get_center());
            
    liste[1]->deplace(save_center);
    liste[1]->set_center(save_center);
}

void Mouvement::deplacement(Cell *c){

    if (c->est_selectionner()){
        liste.push_back(c);
        c->deselectionner();
    }
   
    if (liste.size() == 2){
       
        int x0 = liste[0]->get_center().x/80;
        int y0 = liste[0]->get_center().y/80;
        int x1 = liste[1]->get_center().x/80;
        int y1 = liste[1]->get_center().y/80;
        
        if (Effacer_bonbon::a_coter(x0, y0, x1, y1) && !verif_mur(x0, y0, x1, y1)){

            change_2_bombon(x0, y0, x1, y1); 
            echange_bonbon(liste); 
            
            bool res = false;
            bool res_1 = false;
            
            if (cells[x0][y0].get_color() == 20 || cells[x1][y1].get_color() == 20 ){
              Effacer_bonbon::super_bonbon(x1,y1,x0,y0);
              res = true;
              res_1 = true;
            }else{
                res = alligner(cells[x0][y0]);
                Effacer_bonbon::efface();
                res_1 = alligner(cells[x1][y1]);
                Effacer_bonbon::efface();
            } 

            animation();
            
            while(!verifie_pas_0()){
                tomber_fruits();
                efface_alligner_aleatoire();
            }

            if (!res && !res_1){
                change_2_bombon(x1, y1, x0, y0);
                echange_bonbon(liste);
            }

            liste.clear();

        }else{
            liste.clear();
            liste.push_back(c);
        }    
    } 
}

bool Mouvement::alligner_horizontal(Cell c){

    int x = c.get_center().x/80;
    int y = c.get_center().y/80;
    int toute_couleur = c.get_color();
    if (toute_couleur > 7){
      if (toute_couleur > 13){
        toute_couleur = toute_couleur-13;
      }else{
        toute_couleur = toute_couleur-7; }
    }

    horizontal.push_back(c);
    // horizontal droite
    x++;
    while (x < 9 && (cells[x][y].get_color() == toute_couleur || toute_couleur == cells[x][y].get_color()-7 || toute_couleur == cells[x][y].get_color()-13 )){
        if (c.get_color() == 7){
            break;
        }else{
            horizontal.push_back(cells[x][y]);
            x++; }
    }

    // horizontal gauche
    x = c.get_center().x/80;
    x--;
    while (x >= 0 && (cells[x][y].get_color() == toute_couleur || toute_couleur == cells[x][y].get_color()-7 || toute_couleur == cells[x][y].get_color()-13 )){
        if (c.get_color() == 7){
            break;
        }else{
            horizontal.push_back(cells[x][y]);
            x--; }
    }

    return horizontal.size() >= 3;
}

bool Mouvement::alligner_vertical(Cell c){

    int x = c.get_center().x/80;
    int y = c.get_center().y/80;
    int toute_couleur = c.get_color();
    if (toute_couleur > 7){
      if (toute_couleur > 13){
        toute_couleur = toute_couleur-13;
      }else{
        toute_couleur = toute_couleur-7; }
    }

    vertical.push_back(c);
    // vertical bas
    y++;
    while (y < 9 && (cells[x][y].get_color() == toute_couleur || toute_couleur == cells[x][y].get_color()-7 || toute_couleur == cells[x][y].get_color()-13 )){
        if (c.get_color() == 7){
            break;
        }else{
            vertical.push_back(cells[x][y]);
            y++; }
    }

    // vertical haut
    y = c.get_center().y/80;
    y--;
    while (y >= 0 && (cells[x][y].get_color() == toute_couleur || toute_couleur == cells[x][y].get_color()-7 || toute_couleur == cells[x][y].get_color()-13) ){
        if (c.get_color() == 7){
            break;
        }else{
            vertical.push_back(cells[x][y]);
            y--; }
    }

    return vertical.size() >= 3;   
}

bool Mouvement::alligner(Cell c){
    
    bool res_h = alligner_horizontal(c);
    bool res_v = alligner_vertical(c);

    return res_v || res_h;

}

void Mouvement::animation(){
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      if (cells[i][j].get_color() == 0){
        cells[i][j].explosion();
      }
    }
  }
}

void Mouvement::tomber_fruits(){
    
    for (int i = 0; i < 9 ; i++){
      for (int j = 0; j< 9; j++){
          
        if (cells[i][j].get_color() == 0){
          if (j==0){
              int fruit = rand() %(7-1) +1;
              cells[i][j].set_color(fruit);
          }else{
            if (cells[i][j-1].get_color()==7){ // vérifie si c'est un mur et donne au bonbon la couleur diganol mur 
              cells[i][j].set_color(cells[i-1][j-1].get_color());
              cells[i-1][j-1].set_color(cells[i][j-2].get_color());
              cells[i][j-2].set_color(0);
            }else{ // donne au bonbon la couleur de celui du dessus 
              cells[i][j].set_color(cells[i][j-1].get_color());
              cells[i][j-1].set_color(0); }
          }
        }
      }
    }   
}

bool Mouvement::verifie_pas_0(){
    bool res = true;
    
    for (int i = 0; i < 9 ; i++)
      for (int j = 0; j< 9; j++)
          if ( cells[i][j].get_color() == 0)
              res = false;

    return res;
}

bool Mouvement::verif_mur(int x0,int y0,int x1,int y1){
  bool res=false;
  if (cells[x0][y0].get_color()==7 || cells[x1][y1].get_color()==7)
    res=true;
  return res;
}

void Mouvement::efface_alligner_aleatoire(){
    for (int i = 0; i < 9 ; i++){
        for (int j = 0; j< 9; j++){
            alligner(cells[i][j]);
            Effacer_bonbon::efface();
        } 
    }
}

bool Mouvement::verifie_mouvement_possible_officiel(){
  for (int i = 1; i < 8; i++){
      for (int j = 1; j< 8; j++){
        liste.clear();
        horizontal.clear();
        vertical.clear();
        liste.push_back(&cells[i][j]);
        liste.push_back(&cells[i+1][j]);
        change_2_bombon( i, j,i+1 ,j);
        echange_bonbon(liste);
        if(alligner(cells[i][j])){
          change_2_bombon( i+1, j,i ,j);
          echange_bonbon(liste);
          liste.clear();
          horizontal.clear();
          vertical.clear();
          return true;
        }
        change_2_bombon( i+1, j,i ,j);
        echange_bonbon(liste);
        liste.clear();
        /////////////////////////////////////////////////////////////
        horizontal.clear();
        vertical.clear();
        liste.push_back(&cells[i][j]);
        liste.push_back(&cells[i-1][j]);
        change_2_bombon( i, j, i-1 ,j);
        echange_bonbon(liste);
        if (alligner(cells[i][j])){
          change_2_bombon( i-1, j,i ,j);
        echange_bonbon(liste);
        liste.clear();
        horizontal.clear();
          vertical.clear();
          return true;
        }
        change_2_bombon( i-1, j,i ,j);
        echange_bonbon(liste);
        liste.clear();
        /////////////////////////////////////////////////////////////
        liste.push_back(&cells[i][j]);
        liste.push_back(&cells[i][j-1]);
        horizontal.clear();
        vertical.clear();
        change_2_bombon( i, j,i ,j-1);
        echange_bonbon(liste);
        if (alligner(cells[i][j])){
          change_2_bombon( i, j-1,i ,j);
          echange_bonbon(liste);
          liste.clear();
          horizontal.clear();
          vertical.clear();
          return true;
        }
        change_2_bombon( i, j-1,i ,j);
        echange_bonbon(liste);
        liste.clear();
        /////////////////////////////////////////////////////////////
        liste.push_back(&cells[i][j]);
        liste.push_back(&cells[i][j+1]);
        horizontal.clear();
        vertical.clear();
        change_2_bombon( i, j,i ,j+1);
        echange_bonbon(liste);
        if (alligner(cells[i][j])){
          change_2_bombon( i, j+1,i ,j);
          echange_bonbon(liste);
          liste.clear();
          horizontal.clear();
          vertical.clear();
          return true;
        }
        change_2_bombon( i, j+1,i ,j);
        echange_bonbon(liste);
        /////////////////////////////////////////////////////////////
        liste.clear();
        horizontal.clear();
        vertical.clear();
     }
    
   }
   return false;
}

void Mouvement::reset_plateau(){
  for (int i= 0; i < 9; i++){
       for (int j = 1; j < 9; j++){
           if (cells[i][j].get_color() < 7){
               int fruit = rand() %(6-1) + 1;
               cells[i][j].set_color(fruit);
           }
       }
  }
  do{
    tomber_fruits();
    efface_alligner_aleatoire();
    }while(!verifie_pas_0());
}

#endif


