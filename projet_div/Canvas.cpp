#include "Canvas.hpp"

void Canvas::lire_fichier(const char* fichier_input){
    std::istringstream fichier(fichier_input);
    vector<int> couleur_fichier;
    couleur_fichier.clear();
    int fruit;
    int i = 0;
    while( fruit != 100) {
        fichier >> fruit;
        couleur_fichier.push_back(fruit);
    
    }

    int x = 0;
    for (int i = 0; i < 9; i++){
        couleur.emplace_back ();
        for (int j = 0; j < 9; j++){
            couleur[i].push_back(couleur_fichier[x]);
            x++;
        }

    }

}

void Canvas::print(){

  cout << "\n" << endl;
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
            cout<<"[" << cells[j][i].get_color() << "]; ";
        }
        cout<<"\n" << endl;
  }
  cout << endl;
  
}

bool Canvas::debut_check_horizontal(){
    bool horizontal = false;
    for (int j= 0; j < 9; j++){
       for (int i = 1; i < 8; i++){
           if( couleur[i][j] == couleur[i-1][j] && couleur[i][j] == couleur[i+1][j]){
               horizontal = true;
               while(couleur[i][j] == couleur[i-1][j]){
                   int fruit = rand() %(6-1) + 1;
                   couleur[i][j] = fruit;
                }
                cout << " horizontal" << endl;
           }
        }
   }
   return horizontal;
}

bool Canvas::debut_check_vertical(){
    bool vertical = false;
    //Vertical
   for (int i= 0; i < 9; i++){
       for (int j = 1; j < 8; j++){
           if( couleur[i][j] == couleur[i][j-1] && couleur[i][j] == couleur[i][j+1]){
               vertical = true;
               while(couleur[i][j] == couleur[i][j-1]){
                   int fruit = rand() %(6-1) + 1;
                   couleur[i][j] = fruit;
                }
                cout << " vertical" << endl;
            }
           
       }
   }
   return vertical;
}

void Canvas::cree_plateau(int niveau){ 
  couleur.clear();
  cells.clear();
  switch(niveau){
    case 1:
      for (int i = 0; i < 9; i++){
        couleur.emplace_back ();
        for (int j = 0; j < 9; j++){
            int fruit = rand() %(6-1) + 1;
            couleur[i].push_back(fruit);
        }
      }
      break;
    case 2:
       lire_fichier("mur.txt");
       break;
    case 3:
    lire_fichier("test.txt");
    break;
}
    
  // boucle tant que 3 allignement
  do{
      debut_check_horizontal();
      debut_check_vertical();

  }while( debut_check_horizontal() && debut_check_vertical() );


  // cree le plateau de cells
  for (int x = 0; x < 9; x++)
  {
    cells.emplace_back ();
    for (int y = 0; y < 9; y++){
        int fruit = couleur[x][y];
        cells[x].push_back ({{x * 80 , y * 80}, 80, 80, fruit});
      }
  }

  //cree_voisin(); // initialise le voisin de chaque cells 

  print();
    
}

bool Canvas:: a_coter(int x0, int y0, int x1, int y1){

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

void Canvas::efface(){
    // VIOR SI ON PEUX CHANGER 
    if (vertical.size() >= 3){
        for (int i = 0; i < vertical.size(); i++){
            int x = vertical[i].get_center().x/80;
            int y = vertical[i].get_center().y/80;
            cells[x][y].set_color(0);
            cells[x][y].deplace({x * 80,y*80});
        }
    }

    if (horizontal.size() >= 3){
        for (int i = 0; i < horizontal.size(); i++){
            int x = horizontal[i].get_center().x/80;
            int y = horizontal[i].get_center().y/80;
            cells[x][y].set_color(0);
            cells[x][y].deplace({x*80,y*80});
        }
    }

    horizontal.clear();
    vertical.clear();

}

bool Canvas::alligner_horizontal(Cell c){

    int x = c.get_center().x/80;
    int y = c.get_center().y/80;

    // #### HORIZONTAL 
    horizontal.push_back(c);
    // horizontal droite
    x++;
    while (x < 9 && cells[x][y].get_color() == c.get_color()){
        horizontal.push_back(cells[x][y]);
        x++;
    }

    // horizontal gauche
    x = c.get_center().x/80;
    x--;
    while (x >= 0 && cells[x][y].get_color() == c.get_color()){
        horizontal.push_back(cells[x][y]);
        x--;
    }

    return horizontal.size() >= 3;
}

bool Canvas::alligner_vertical(Cell c){

    int x = c.get_center().x/80;
    int y = c.get_center().y/80;

    // #### VERTICAL 
    vertical.push_back(c);
    // vertical bas
    y++;
    while (y < 9 && cells[x][y].get_color() == c.get_color()){
        vertical.push_back(cells[x][y]);
        y++;
    }

    // vertical haut
    y = c.get_center().y/80;
    y--;
    while (y >= 0 && cells[x][y].get_color() == c.get_color()){
        vertical.push_back(cells[x][y]);
        y--;
    }

    return vertical.size() >= 3;   
}

bool Canvas::alligner(Cell c){
    
    bool res_h = alligner_horizontal(c);
    bool res_v = alligner_vertical(c);

    return res_v || res_h;

}

bool Canvas::verif_mur(int x0,int y0,int x1,int y1){
  bool res=false;
  if (cells[x0][y0].get_color()==7 || cells[x1][y1].get_color()==7){
    res=true;
  }return res;
}

void Canvas::change_2_bombon(int x0, int y0, int x1, int y1){
    
    Cell sauve = cells[x0][y0];
    cells[x0][y0] = cells[x1][y1];
    cells[x1][y1] = sauve;
}

void Canvas::echange_bonbon(vector<Cell *> &liste){
   
    Point save_center{liste[0]->get_center().x, liste[0]->get_center().y};
            
    liste[0]->deplace(liste[1]->get_center());
    liste[0]->set_center(liste[1]->get_center());
            
    liste[1]->deplace(save_center);
    liste[1]->set_center(save_center);
}

void Canvas::deplacement(Cell *c){
        if (!verifie_mouvement_possible()){
          cout<<"plus de mouvement";
          test();

        }

    if (c->est_selectionner()){
       liste.push_back(c);
       c->deselectionner();
    }
   
    if (liste.size() == 2){
       
        int x0 = liste[0]->get_center().x/80;
        int y0 = liste[0]->get_center().y/80;

        int x1 = liste[1]->get_center().x/80;
        int y1 = liste[1]->get_center().y/80;
        
        if (a_coter(x0, y0, x1, y1) && !verif_mur(x0, y0, x1, y1)){

            change_2_bombon(x0, y0, x1, y1); // change bombom sur le terminal 
            
            echange_bonbon(liste); // change bombon FLTK
            
            bool res = alligner(cells[x0][y0]);
            efface();
            bool res_1 = alligner(cells[x1][y1]);
            efface();


            
           while(!verifie_pas_0()){
                tomber_fruits();
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

bool Canvas::verifie_pas_0(){
    bool res = true;
    
    for (int i = 0; i < 9 ; i++){
      for (int j = 0; j< 9; j++){
          if ( cells[i][j].get_color() == 0){
              res = false;
          } 
      }
    }
    return res;
}

void Canvas::tomber_fruits(){

    for (int i = 0; i < 9 ; i++){
      for (int j = 0; j< 9; j++){
          
        if (cells[i][j].get_color() == 0){
          if (j==0){
              int fruit = rand() %(6-1) + 1;
              cells[i][j].set_color(fruit);
          }else{
            // vérifie si c'est un mur 
            if (cells[i][j-1].get_color()==7){
              // déplace en diagonal si c'est un mur 
              cells[i][j].set_color(cells[i-1][j-1].get_color());
              cells[i-1][j-1].set_color(cells[i][j-2].get_color());
              cells[i][j-2].set_color(0);
      
            }else{
              cells[i][j].set_color(cells[i][j-1].get_color());
              cells[i][j-1].set_color(0);
            }
          }
        }
      }
    }  

   for (int i = 0; i < 9 ; i++){
      for (int j = 0; j< 9; j++){
        bool res = alligner(cells[i][j]);
        efface();
      } 
    }
}

void Canvas::mouseMove(Point mouseLoc) {
  for (auto &v: cells)
    for (auto &c: v){
      c.mouseMove(mouseLoc);
    }
}

void Canvas::mouseClick(Point mouseLoc) {
  for (auto &v: cells)
    for (auto &c: v){
        c.mouseClick (mouseLoc);
        deplacement(&c);
    }

}

void Canvas::keyPressed(int keyCode) {
  switch (keyCode) {
    case 'a': 
        cree_plateau(1);
        break;
    case 'q':
        exit(0);
  }
}


bool Canvas::verifie_mouvement_possible_diagonal(){
  // vérifie si il y a un mouvement possible sur les diagonales.
  bool move_possible=false;
  for (int i = 1; i < 8; i++){
      for (int j = 1; j< 8; j++){
        if(cells[i][j].get_color() == cells[i+1][j+1].get_color() && cells[i][j].get_color() == cells[i-1][j+1].get_color()  ){
          move_possible=true;
       }
        else if(cells[i][j].get_color() == cells[i+1][j+1].get_color() && cells[i][j].get_color() == cells[i+1][j-1].get_color()  ){
           move_possible=true;
         }
        else if(cells[i][j].get_color() == cells[i-1][j-1].get_color() && cells[i][j].get_color() == cells[i-1][j+1].get_color()  ){
           move_possible=true;
          }
        else  if(cells[i][j].get_color() == cells[i+1][j-1].get_color() && cells[i][j].get_color() == cells[i-1][j-1].get_color()  ){
           move_possible=true;
          }
    } 
 } return move_possible;
}

bool Canvas::verifie_mouvement_possible_vertical(){
    bool move_possible=false;
    for (int i = 0; i < 9; i++){
      for (int j = 1; j< 8; j++){
        if (i-1 < 0){
            continue;
        }
        else if(cells[i][j].get_color() == cells[i][j-1].get_color() && cells[i][j].get_color() == cells[i-1][j+1].get_color()  ){
           move_possible=true;
        }
        else if(cells[i][j].get_color() == cells[i][j-1].get_color() && cells[i][j].get_color() == cells[i+1][j+1].get_color()  ){
           move_possible=true;
        }
        else if(cells[i][j].get_color() == cells[i][j-1].get_color() && cells[i][j].get_color() == cells[i][j+2].get_color()  ){
           move_possible=true;
        }
        else if(cells[i][j].get_color() == cells[i][j+1].get_color() && cells[i][j].get_color() == cells[i-1][j-1].get_color()  ){
           move_possible=true;
        }
        else if(cells[i][j].get_color() == cells[i][j+1].get_color() && cells[i][j].get_color() == cells[i+1][j-1].get_color()  ){
           move_possible=true;
        }
        else if(cells[i][j].get_color() == cells[i][j+1].get_color() && cells[i][j].get_color() == cells[i][j-2].get_color()  ){
           move_possible=true;
        }
      }
    } return move_possible;
}  

bool Canvas::verifie_mouvement_possible_horizontal(){
    bool move_possible=false;
    for (int i = 1; i < 7; i++){
      for (int j = 0; j< 9; j++){
        if(cells[i][j].get_color() == cells[i-1][j].get_color() && cells[i][j].get_color() == cells[i+1][j-1].get_color()  ){
           move_possible=true;
        }
        else if(cells[i][j].get_color() == cells[i-1][j].get_color() && cells[i][j].get_color() == cells[i+1][j+1].get_color()  ){
           move_possible=true;
        }
        else if(cells[i][j].get_color() == cells[i-1][j].get_color() && cells[i][j].get_color() == cells[i+2][j].get_color()  ){
           move_possible=true;
        }
        else if(cells[i][j].get_color() == cells[i+1][j].get_color() && cells[i][j].get_color() == cells[i-2][j].get_color()  ){
           move_possible=true;
        }
        else if(cells[i][j].get_color() == cells[i+1][j].get_color() && cells[i][j].get_color() == cells[i-1][j+1].get_color()  ){
           move_possible=true;
        }
        else if(cells[i][j].get_color() == cells[i+1][j].get_color() && cells[i][j].get_color() == cells[i-1][j-1].get_color()  ){
           move_possible=true;
        }

      }
    }return move_possible;
}

bool Canvas::verifie_mouvement_possible(){
    bool res = false;
    
    if (verifie_mouvement_possible_diagonal() || verifie_mouvement_possible_vertical() || verifie_mouvement_possible_horizontal() ){
        res= true;
    }
    return res;
}

void Canvas::test(){
  for (int i= 0; i < 9; i++){
       for (int j = 1; j < 9; j++){
           if (cells[i][j].get_color() != 7){
               int fruit = rand() %(6-1) + 1;
               cells[i][j].set_color(fruit);
           }
           if (alligner(cells[i][j])){
            efface();
            }
       }
  }
   while(!verifie_pas_0()){
    tomber_fruits();
    }
}


