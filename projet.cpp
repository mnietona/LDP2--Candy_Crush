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
    
    map<int,string> liste_bombon = {{1, "image/bleu.png",},{2, "image/rouge.png",},
                               {3, "image/vert.png",},{4, "image/jaune.png",},
                               {5, "image/orange.png",},{6, "image/mauve.png",}};


 public:
  // Constructor
  Cell(Point center, int w, int h, int fruit);

  // Methodes 
  void cree_bombon();  // fonction repreise sur github
  void deplace(Point d);
  void toucher(int fruit,bool s);
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  int get_color();
  void set_color(int new_fruit); // donne une nouvelle couleur 
  void set_center(Point new_center);  // donne un nouveau x et y au bombon
  bool est_selectionner() const; // renvoi la valeur de select
  void deselectionner();  // met selecter a faux 
  Point get_center() const; // renvoi le x et y du bombon
  void setNeighbors (const vector<Cell *> &newNeighbors); // donne un nouveau voisin
  
 
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
      map<int ,string> liste_t_bombon = {{1, "image/bleu_s.png",},{2, "image/rouge_s.png",},
                                        {3, "image/vert_s.png",},{4, "image/jaune_s.png",},
                                        {5, "image/orange_s.png",},{6, "image/mauve_s.png",}};
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

void Cell::setNeighbors (const vector<Cell *> &newNeighbors){
  neighbors = newNeighbors;
}





/**
 * 
 * 
 */
class Canvas {
  vector< vector<Cell> > cells;
  vector<vector<int> > couleur;
  vector<Cell *> liste;
  
 public:
  Canvas ()
  {
    cree_plateau();
  }

  void cree_voisin(); // Cree 4 voisins d'une cellules
  void cree_plateau(); // initilaise le plateau
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
  bool debut_check_horizontal();
  bool debut_check_vertical();
  void print();
  //void donne_couleur();

  bool a_coter(int x0, int y0, int x1, int y1);
  void change_2_bombon(int x0, int y0, int x1, int y1);
  void efface();
  void deplacement(Cell *c);
  bool alligner(Cell c);
  };


/*
void donne_couleur(){
    
    for (int i = 0; i < 9; i++){
        couleur.emplace_back ();
        for (int j = 0; j < 9; j++){
            int fruit = rand() %(6-1) + 1;
            couleur[i].push_back(fruit);
        }
    }
}
*/

void Canvas::print(){

  cout << "\n" << endl;
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
            cout << "["<< cells[j][i].get_color() << "]; ";
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

void Canvas::cree_voisin(){
    
    // Viens du labo3 solution 
  for (int x = 0; x < 9; x++)
    for (int y = 0; y < 9; y++)
    {
      vector<Cell *> neighbors;
      for (auto &shift: vector<Point> ({{-1, 0}, {0, 1}, {1, 0}, {0, -1},}))
      {
          int neighborx = x + shift.x;
          int neighbory = y + shift.y;
          
          if (neighborx >= 0 && neighbory >= 0 &&
              neighborx < static_cast<int>(cells.size ()) &&
              neighbory < static_cast<int >(cells[neighborx].size ()))
            {
                neighbors.push_back (&cells[neighborx][neighbory]);
            }
          cells[x][y].setNeighbors (neighbors);
        }
    }


}

void Canvas::cree_plateau(){ 

    for (int i = 0; i < 9; i++){
        couleur.emplace_back ();
        for (int j = 0; j < 9; j++){
            int fruit = rand() %(6-1) + 1;
            couleur[i].push_back(fruit);
        }
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

void Canvas:: efface(){

    // TODO pour delete case
}

bool Canvas::alligner(Cell c){

    // TODO verifie si case alligner 
  
}


void Canvas::change_2_bombon(int x0, int y0, int x1, int y1){
    
    Cell sauve = cells[x0][y0];
    cells[x0][y0] = cells[x1][y1];
    cells[x1][y1] = sauve;
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
        cout << x0 << y0 << " " << x1 << y1 << endl;
        
        if (a_coter(x0, y0, x1, y1)){

            change_2_bombon(x0, y0, x1, y1); // change bombom sur le terminal 
            
            // change bombon sur FLTK
            Point save_center{liste[0]->get_center().x, liste[0]->get_center().y};
            liste[0]->deplace(liste[1]->get_center());
            liste[0]->set_center(liste[1]->get_center());
            liste[1]->deplace(save_center);
            liste[1]->set_center(save_center);
                

            print();

            liste.clear();
        
        }
        else{
            cout <<"pas frere"<< endl;
            liste.clear();
            liste.push_back(c);
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
        cree_plateau();
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