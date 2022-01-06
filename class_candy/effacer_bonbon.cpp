#include "effacer_bonbon.h"

bool Effacer_bonbon:: a_coter(int x0, int y0, int x1, int y1){

    bool coter = false;

    if (x0 - 1 >=0 && x0 - 1 ==  x1 && y0 == y1 ){
        coter = true;
    }
    else if (x0 + 1 < 9 && x0 + 1 == x1 && y0 == y1 ){
        coter = true;
    }
    else if (y0 - 1 >=0 && x0 == x1 && y0 - 1 == y1 ){
        coter = true;
    }
    else if (y0 + 1 < 9 && x0 == x1 && y0 + 1 == y1 ){
        coter = true;
    }

    return coter;
}

bool Effacer_bonbon:: a_coter_diagonal(int x0, int y0, int x1, int y1){

    bool coter = false;

    if (x0 - 1 >= 0 && y0 - 1 >= 0 && x0 - 1 ==  x1 && y0 - 1 == y1 ){
        coter = true;
    }
    else if (x0 + 1 < 9 && y0 + 1 < 9 && x0 + 1 == x1 && y0 + 1 == y1 ){
        coter = true;
    }
    else if (x0 + 1 < 9 && y0 - 1 >=0 && x0 + 1 == x1 && y0 - 1 == y1 ){
        coter = true;
    }
    else if (x0 - 1 >= 0 && y0 + 1 < 9 && x0 - 1 == x1 && y0 + 1 == y1 ){
        coter = true;
    }

    return coter;
}

void Effacer_bonbon::super_bonbon(int x1, int y1, int x0, int y0){
  bool rayer = false;
  bool emballer = false;
  bool reset = cells[x1][y1].get_color() == 20 && cells[x0][y0].get_color() == 20;
  int sauve = 0;

  for (int i = 0; i< 9; i++){
    for (int j = 0; j < 9; j++){
      if(reset){  // Si 2 bonbon de super bonbon selectionner alors reset plateau 
        if (cells[i][j].get_color() != 7)
          cells[i][j].set_color(0); 
          Scores::score();}
      else if ( (cells[x1][y1].get_color() != 20 && cells[i][j].get_color() ==  cells[x1][y1].get_color()) || (cells[x0][y0].get_color() != 20 && cells[i][j].get_color() ==  cells[x0][y0].get_color()) ){  // si super bonbon avec un bonbon normal
        if ((i != x1 && j != y1) || (i != x0 && j != y0) ){
          cells[i][j].set_color(0); 
          Scores::score();} // met tt les bonbons de la couleur a 0 
      }else if (cells[x0][y0].get_color() != 20 && cells[i][j].get_color()+7 ==  cells[x0][y0].get_color()){ // Si un super bonbon et un bonbon rayer
        sauve = cells[x0][y0].get_color();
        condition_super_bonbon(i, j, x0, y0, sauve); // met bonbon a la couleur du rayer 
        rayer = true;
      }else if (cells[x1][y1].get_color() != 20 && cells[i][j].get_color()+7 ==  cells[x0][y0].get_color()){ // Si un super bonbon et un bonbon rayer
        sauve = cells[x1][y1].get_color();
        condition_super_bonbon(i, j, x1, y1, sauve);  // met bonbon a la couleur du rayer 
        rayer = true;
      }else if (cells[x0][y0].get_color() != 20 && cells[i][j].get_color()+13 ==  cells[x0][y0].get_color()){ // Si un super bonbon et un bonbon emballer 
        sauve = cells[x0][y0].get_color();
        condition_super_bonbon(i, j, x0, y0, sauve); // met bonbon a la couleur du remballer
        emballer = true;
      }else if (cells[x1][y1].get_color() != 20 && cells[i][j].get_color()+13 ==  cells[x0][y0].get_color()){ // Si un super bonbon et un bonbon emballer 
        sauve = cells[x1][y1].get_color();
        condition_super_bonbon(i, j, x1, y1, sauve); // met bonbon a la couleur du remballer
        emballer = true; }
    }
  }
  if (rayer)
    pouvoir_rayer(sauve); // efface tt les bonbon rayer correctement 

  if (emballer){
    for (int x = 0; x < 9; x++){
       for (int y = 0; y < 9; y++){
           if (cells[x][y].get_color() == sauve){
               pouvoir_emballer(x,y); // efface tt les bonbon emballer correctement
           }
       }
    }
  }

  cells[x0][y0].set_color(0);
  cells[x1][y1].set_color(0);
}

void Effacer_bonbon::pouvoir_rayer(int sauve){
    for (int i = 0; i < 9; i++){
       for (int j = 0; j < 9; j++){
            if (cells[i][j].get_color() == sauve){
                if (j % 2 == 1){
                    for (int x = 0; x < 9; x++){ // vertical 
                    if (cells[x][j].get_color() != 7){
                        cells[x][j].set_color(0);} 
                    Scores::score();  }
                }else{
                    for (int y = 0; y < 9; y++){ // horizontal 
                    if (cells[i][y].get_color() != 7){
                        cells[i][y].set_color(0);} 
                    Scores::score();  }
                }
            }
        }
    }
}

void Effacer_bonbon::pouvoir_emballer(int x, int y){
    
    cells[x][y].set_color(0);
    Scores::score();
    if (a_coter( x, y, x+1, y) && cells[x+1][y].get_color() != 7 ){
        cells[x+1][y].set_color(0);
        Scores::score();}
    if ( a_coter(x, y, x, y+1) && cells[x][y+1].get_color() != 7 ){
        cells[x][y+1].set_color(0);
        Scores::score();}
    if ( a_coter(x, y, x-1, y) && cells[x-1][y].get_color() != 7 ){
        cells[x-1][y].set_color(0);
        Scores::score();}
    if (a_coter(x, y, x, y-1) && cells[x][y-1].get_color() != 7 ){
        cells[x][y-1].set_color(0);
        Scores::score();}
    if (a_coter_diagonal(x, y, x+1, y+1) && cells[x+1][y+1].get_color() != 7 ){
        cells[x+1][y+1].set_color(0);
        Scores::score();}
    if ( a_coter_diagonal(x, y, x-1, y-1) && cells[x-1][y-1].get_color() != 7 ){
        cells[x-1][y-1].set_color(0);
        Scores::score();}
    if ( a_coter_diagonal(x, y, x+1, y-1) && cells[x+1][y-1].get_color() != 7){
        cells[x+1][y-1].set_color(0);
        Scores::score();}
    if ( a_coter_diagonal(x, y, x-1, y+1) && cells[x-1][y+1].get_color() != 7){
        cells[x-1][y+1].set_color(0);
        Scores::score();}

}

void Effacer_bonbon::condition_super_bonbon(int i, int j, int x, int y, int sauve){
    if (i != x && j != y){
        cells[i][j].set_color(sauve);
    }  
}

int Effacer_bonbon::couleur_special(vector<Cell > position, int couleur_new_bonbon ){
    int couleur_ancien = 0;

    if (position.size() == 4){
        couleur_ancien = position[0].get_color();
        if (couleur_ancien > 7){
            couleur_new_bonbon = couleur_ancien;
        }else{
            couleur_new_bonbon =  couleur_ancien+7;
        }
    }

    else if (position.size() == 5){
        couleur_new_bonbon = 20;
    }
      
    if (couleur_new_bonbon == 7){
        couleur_new_bonbon = 0;
    }
    return couleur_new_bonbon;
}

void Effacer_bonbon::couleur_bonbon_emballer(){
    
    int ancien = vertical[0].get_color();
    int new_bonbon =  ancien+13;
    if (ancien > 7){
        new_bonbon = ancien;
    }
    

    for (unsigned long int i = 0; i < horizontal.size(); i++){
        int x = horizontal[i].get_center().x/80;
        int y = horizontal[i].get_center().y/80;
        if (cells[x][y].get_color() != 7){
            cells[x][y].set_color(0);
            Scores::score();  // augmente le score pour chaque supression 
        }else if (cells[x][y].get_color() > 13 && cells[x][y].get_color() < 20){ // bonbon emballer 
            pouvoir_emballer(x, y);
        }
    }
    for (unsigned long int i = 0; i < vertical.size(); i++){
            int x = vertical[i].get_center().x/80;
            int y = vertical[i].get_center().y/80;
            if (cells[x][y].get_color() != 7){
                cells[x][y].set_color(0);
                Scores::score();  // augmente le score pour chaque supression 
            }else if (cells[x][y].get_color() > 13 && cells[x][y].get_color() < 20){ // bonbon emballer 
                pouvoir_emballer(x, y);
            }
    }
    Scores::moins_score(); // car il reprend 2 fois le meme ducoup on suprime une fois le score
    cells[ horizontal[0].get_center().x/80 ][ horizontal[0].get_center().y/80 ].set_color(new_bonbon);
  }

void Effacer_bonbon::efface(){
  int couleur_new_bonbon = 0;

  // cree bonbon embaler et efface les ligne qu'il l'ont cree
  if ( (vertical.size() == 3 || vertical.size() == 4) && (horizontal.size() == 3 || horizontal.size() == 4) && horizontal[0].get_color() == vertical[0].get_color() ){
    couleur_bonbon_emballer(); }
  
  else{

    couleur_new_bonbon = couleur_special(vertical, couleur_new_bonbon );

    if (vertical.size() >= 3 && vertical[0].get_color() != 0){
        efface_vertical_horizontal(vertical,couleur_new_bonbon,"vertical"); }
      
    couleur_new_bonbon = couleur_special(horizontal, couleur_new_bonbon );

    if (horizontal.size() >= 3 && horizontal[0].get_color() != 0){
        efface_vertical_horizontal(horizontal,couleur_new_bonbon,"horizontal"); }
  } 
   
  horizontal.clear();
  vertical.clear();

}

void Effacer_bonbon::efface_vertical_horizontal(vector<Cell > position,int couleur_new_bonbon, string direction){
    int stop = false;
    bool rayer_ok = false;
    for (unsigned long int i = 0; i < position.size(); i++){ // permet de voir si bonbon rayer dans liste comme ca il garde couleur si allignement vaux 4 ou 5 
        if( position[i].get_color() > 7 && position[i].get_color() < 14 ){
            rayer_ok = true; }
    }
    for (unsigned long int i = 0; i < position.size(); i++){
        int x = position[i].get_center().x/80;
        int y = position[i].get_center().y/80;

        if(rayer_ok){ // Si bonbon rayer dans allignement fait son piuvoir  
            for (int j = 0; j < 9; j++){
                if (direction == "vertical"){
                    if (cells[x][j].get_color() != 7){
                        cells[x][j].set_color(0); }
                }else if (direction == "horizontal"){
                    if (cells[j][y].get_color() != 7){
                        cells[j][y].set_color(0);  }
                }
                stop = true;
                Scores::score();  // augmente le score pour chaque supression 
            }
            cells[x][y].set_color(couleur_new_bonbon);
            couleur_new_bonbon = 0;
            rayer_ok = false;
        }
        else if (cells[x][y].get_color() > 13 && cells[x][y].get_color() < 20){ // bonbon emballer 
            pouvoir_emballer(x, y);
            couleur_new_bonbon = 0;
        }
                
        else if (!stop){
            cells[x][y].set_color(couleur_new_bonbon);
            couleur_new_bonbon = 0;
            Scores::score();  // augmente le score pour chaque supression 
        }
    }
}
