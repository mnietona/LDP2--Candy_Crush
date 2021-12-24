/**
 * 
 * 1 = bleu
 * 2 = rouge.png
 * 3 = vert
 * 4 = jaune
 * 5 = orange
 * 6 = mauve  
 * 
 */

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

//################## REPRIS SUR GITHUB #############
/**
 * Affiche des Box sur l'ecran
 * 
 */

class Plateau: public Fl_Box {

 public:
  // constructeur 
  Plateau (Fl_Boxtype b, int x, int y, int w, int h, const char *l);
  // renvoi les coordonnees
  Point get_position() const;
  // true si curseur est dedans
  bool contains (Point p) const;
};

Plateau::Plateau (Fl_Boxtype b, int x, int y, int w, int h, const char *l) :
    Fl_Box (b, x, y, w, h, l){}

bool Plateau::contains (Point p) const
{
  return p.x >= x() &&
         p.x < x()+ w() &&
         p.y >= y() &&
         p.y < y() + h();
}

Point Plateau::get_position () const
{
  return {x(), y()};
}

/**
 * Affiche un bonbon dans la box
 * 
 */

class Candy : public Fl_PNG_Image{

 public:
  Candy (const char *filename);

};

Candy::Candy (const char *filename) : Fl_PNG_Image(filename){}
//################## REPRIS SUR GITHUB #############


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
    vector<Cell *> neighbors;
    char *image;
    
    map<int,string> liste_bombon = {{0, "image/explosion.png",},{1, "image/bleu.png",},{2, "image/rouge.png",},
                               {3, "image/vert.png",},{4, "image/jaune.png",},{5, "image/orange.png",},
                               {6, "image/mauve.png",},{7,"image/mur.png",}};


 public:
  // Constructor
  Cell(Point center, int w, int h, int fruit);

  // Methodes 
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
Cell::Cell(Point center, int w, int h, int fruit):
  center{center}, w{w}, h{h}, fruit{fruit}
    {
      cree_bombon();
    }

void Cell::cree_bombon(){

  image = &liste_bombon.find (fruit)->second[0];
  candy = new Candy(image);
  plateau= new Plateau(FL_NO_BOX, center.x, center.y, w, h+10, " ");
  plateau->color(fl_rgb_color(214, 214, 214));
  plateau->image(candy);

}

void Cell::toucher(int fruit,bool s) {
  
  if (s){
      map<int ,string> liste_t_bombon = {{0, "image/explosion.png",},{1, "image/bleu_s.png",},{2, "image/rouge_s.png",},
                                        {3, "image/vert_s.png",},{4, "image/jaune_s.png",},
                                        {5, "image/orange_s.png",},{6, "image/mauve_s.png",},{7,"image/mur.png",}};
      image = &liste_t_bombon.find (fruit)->second[0];
      candy = new Candy(image);
      plateau->image(candy);

   }
   else{
       image = &liste_bombon.find (fruit)->second[0];
       candy = new Candy(image);
       plateau->image(candy);
    }


}

void Cell::deplace(Point d){
    int x = d.x;
    int y = d.y;
    plateau->resize(x, y, w, h+10);
}

void Cell::mouseMove(Point mouseLoc) {
  if (plateau->contains(mouseLoc)) {
      toucher(get_color(),true);
      
    } else {
        toucher(get_color(),false);
      }
}

void Cell::mouseClick(Point mouseLoc) {
    if ((plateau->contains (mouseLoc)))
      selectionner = true;
}

int Cell::get_color(){
  return fruit;
}

void Cell::set_color(int new_fruit){
  fruit = new_fruit;
}

void Cell::set_center(Point new_center){
  center.x = new_center.x;
  center.y = new_center.y;
}

bool Cell::est_selectionner() const{
  return selectionner;
}

void Cell::deselectionner(){
  selectionner = false;
}

Point Cell::get_center() const{
  return center;
}




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
    cree_plateau(2);
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
  bool alligner_horizontal(Cell c); // verifie allignement horizontal et ajoute les bombon alligner dans une liste 
  bool alligner_vertical(Cell c); // verifie allignement vertical et ajute dasn une liste les bombon alligner 
  bool alligner(Cell c); // verifie allignement total
  void echange_bonbon(vector<Cell *> &liste); // change le deplacement du bombon sur l'interface 
  void tomber_fruits(); // fait tomber les fruit lor d'une surpression
  bool verifie_pas_0(); // verifie qu'il n'y a plus de case vide 
  void lire_fichier();
  };


void Canvas::lire_fichier(){
    
    ifstream fichier("mur.txt");
    vector<int> couleur_fichier;
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
       lire_fichier();
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

    if (c->est_selectionner()){
       liste.push_back(c);
       c->deselectionner();
    }

    if (liste.size() == 2){
       
        int x0 = liste[0]->get_center().x/80;
        int y0 = liste[0]->get_center().y/80;

        int x1 = liste[1]->get_center().x/80;
        int y1 = liste[1]->get_center().y/80;
        
        if (a_coter(x0, y0, x1, y1)){

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
            print();

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
              cells[i][j].set_color(cells[i][j-1].get_color());
              cells[i][j-1].set_color(0);
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
    for (auto &c: v)
      c.mouseMove(mouseLoc);
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







/**
 * Cree la fenetre  
 *
 * Pas toucher 
 */

class MainWindow : public Fl_Window {
  Canvas canvas;
 public:
  MainWindow() : Fl_Window(200, 100, windowWidth, windowHeight, "Candy crush") {
    Fl::add_timeout(1.0/refreshPerSecond, Timer_CB, this);
    resizable(this);
  }
  void draw() override {
    Fl_Window::draw();
  }
  int handle(int event) override {
    switch (event) {
      case FL_MOVE:
        canvas.mouseMove(Point{Fl::event_x(), Fl::event_y()});
        return 1;
      case FL_PUSH:
        canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
        return 1;
      case FL_KEYDOWN:
        canvas.keyPressed(Fl::event_key());
        return 1;
    }
    return 0;
  }
  static void Timer_CB(void *userdata) {
    MainWindow *o = (MainWindow*) userdata;
    o->redraw();
    Fl::repeat_timeout(1.0/refreshPerSecond, Timer_CB, userdata);
  }
};


/*--------------------------------------------------

main

Do not edit!!!!

--------------------------------------------------*/


int main(int argc, char *argv[]) {
  srand(time(0));
  MainWindow window;
  window.show(argc, argv);
  return Fl::run();
}