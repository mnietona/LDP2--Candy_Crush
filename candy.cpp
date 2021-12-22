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


using namespace std;


const int windowWidth = 1080;
const int windowHeight = 720;
const double refreshPerSecond = 60;


struct Point {
  int x, y;
};

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



/**
 * 
 * 
 */

class Cell {

  Point center;
  int w, h;
  bool selected = false;
  vector<Cell *> neighbors;
  
  Plateau *plateau = nullptr;
  Candy *candy = nullptr;
  std::string color;
  char *file_image = {};

  


 public:
  // Constructor
  Cell(Point center, int w, int h, std::string color);

  // Methodes 
  void initialize(); 

  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void toucher(string color,bool s); // recois une couleur et change la couleur sur l'ecran 
  string get_color(); // renvoi coulor du bombon
  void set_color(string new_color); // donne une nouvelle couleur 
  void set_center(Point new_center);  // donne un nouveau x et y au bombon
  void reposition(Point p); // met image de la cellule a la position x y demander
  bool is_selected() const; // renvoi la valeur de select
  void unselect();  // met selecter a faux 
  Point get_center() const; // renvoi le x et y du bombon

  bool is_neighbor(Cell * cell) const; // renvoi vrai si c'est son voisin
  void setNeighbors (const vector<Cell *> &newNeighbors); // donne un nouveau voisin
  vector<Cell *> get_Neighbors(); // renvoi le voisin 
  void myNeighbors(Cell * c);  // PAS TROP COMPRIS 
  
  // Destructeur
  ~Cell(){};

};

Cell::Cell(Point center, int w, int h, std::string color):
  center{center}, w{w}, h{h}, color{color}
    {
      initialize();
    }

void Cell::initialize ()
{
  std::map<std::string , std::string> candy_d = {{"jsp", "image/bob.png"},
                                                 {"bleu", "image/bleu.png",},
                                                 {"rouge", "image/rouge.png",},
                                                 {"vert", "image/vert.png",},
                                                 {"jaune", "image/jaune.png",},
                                                 {"orange", "image/orange.png",},
                                                 {"mauve", "image/mauve.png",}};
  
  file_image = &candy_d.find (color)->second[0];
  
  candy = new Candy(file_image);
  plateau= new Plateau(FL_NO_BOX, center.x, center.y, w, h+10, " ");

  plateau->color(fl_rgb_color(214, 214, 214));
  plateau->image(candy);

}

void Cell::toucher(string color,bool s) {
  
  if (s){
  std::map<std::string , std::string> candy_d = {{"bleu", "image/bleu_s.png",},
                                                 {"rouge", "image/rouge_s.png",},
                                                 {"vert", "image/vert_s.png",},
                                                 {"jaune", "image/jaune_s.png",},
                                                 {"orange", "image/orange_s.png",},
                                                 {"mauve", "image/mauve_s.png",}};
   

   file_image = &candy_d.find (color)->second[0];
   candy = new Candy(file_image);
   plateau->image(candy);

   }else{std::map<std::string , std::string> candy_d = {{"bleu", "image/bleu.png",},
                                                 {"rouge", "image/rouge.png",},
                                                 {"vert", "image/vert.png",},
                                                 {"jaune", "image/jaune.png",},
                                                 {"orange", "image/orange.png",},
                                                 {"mauve", "image/mauve.png",}};
   

   file_image = &candy_d.find (color)->second[0];
   candy = new Candy(file_image);
   plateau->image(candy);}


}

void Cell::mouseMove(Point mouseLoc) {
  if (plateau->contains(mouseLoc)) {
      toucher(get_color(),true);
      //plateau->color(FL_RED);
      
      
    } else {
      toucher(get_color(),false);
      //plateau->color(fl_rgb_color(214, 214, 214));
    }
}

void Cell::mouseClick(Point mouseLoc) {
    if ((plateau->contains (mouseLoc)))
      selected = true;
      
}

string Cell::get_color(){
  return color;
}

void Cell ::set_color(string new_color){
  color = new_color;
}

void Cell ::set_center(Point new_center){
  center.x = new_center.x;
  center.y = new_center.y;
}

void Cell::reposition (Point p)
{
  int x = p.x;
  int y = p.y;
  plateau->position(x,y);
  plateau->redraw();
}

bool Cell::is_selected () const
{
  return selected;
}

void Cell::unselect ()
{
  selected = false;
}

Point Cell::get_center() const
{
  return center;
}

////################

bool Cell::is_neighbor (Cell * cell) const
{
  return find (neighbors.begin(), neighbors.end(), cell) != neighbors.end();
}

void Cell::setNeighbors (const vector<Cell *> &newNeighbors)
{
  neighbors = newNeighbors;
}

vector<Cell *> Cell::get_Neighbors ()
{
  return neighbors;
}

void Cell::myNeighbors (Cell *c)
{
  for (auto &neighbor : neighbors)
    {
      auto n_tochange = neighbor->get_Neighbors();
      std::replace(n_tochange.begin(), n_tochange.end(), c, this);
      neighbor->setNeighbors (n_tochange);
    }

}
//###############

/**
 * 
 * 
 */
class Canvas {
  vector< vector<Cell> > cells;
  vector<Cell *> selected; // Liste des selectionner 
  vector<Cell> horizontally_aligned; // liste des allignement horizonatal
  vector<Cell> vertically_aligned;  // liste des allignement vertical
  vector<vector<string> > colors_grid; // Liste de liste de string de couleur
  vector<Cell > fruit;
  int score = 0;
 public:
  Canvas ()
  {
    initialize ();
  }

  void cells_color(); 
  void initialize ();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
  void check_image(int x, int y);
  
  void swap(Cell * c);
  bool check_alligner(Cell c);
  void delete_alligner();
  void move_fruits();
  void cree_voisin();

};



void Canvas::cree_voisin(){

  for (int x = 0; x < 9; x++)
    for (int y = 0; y < 9; y++)
    {
      vector<Cell *> neighbors;
      for (auto &shift: vector<Point> ({
                                           {-1, 0}, // The 4 neighbors relative to the cell
                                           {0, 1},
                                           {1, 0},
                                           {0, -1},
                                       }))
        {
          int neighborx = x + shift.x;
          int neighbory = y + shift.y;
          if (neighborx >= 0 && // Check if the indicies are in range
              neighbory >= 0 &&
              neighborx < static_cast<int>(cells.size ()) &&
              neighbory < static_cast<int >(cells[neighborx].size ()))
            neighbors.push_back (&cells[neighborx][neighbory]);
          cells[x][y].setNeighbors (neighbors);
        }
    }


}

void Canvas::check_image(int x, int y){
  
  string color = colors_grid[x][y];
  int col = 0;
  int row = 0;
  std::vector <string> color_vect {"bleu", "rouge", "orange", "jaune", "vert", "mauve"};
  std::string new_color = color;

  // horizontal vers la droite
  int i = x+1;
  while (i < 9 && color == colors_grid[i][y])
  {
    col++;
    i++;
  }
  // horizontal vers la gauche
  i = x;
  while (i >= 0 && color == colors_grid[i][y])
  {
    col++;
    i--;
  }
  // vertical vers le haut
  int j = y+1;
  while (j < 9 && color == colors_grid[x][j])
  {
    row++;
    j++;
  }
  // vertical vers le bas
  j = y;
  while (j >= 0 && color == colors_grid[x][j])
  {
    if (color == colors_grid[x][j])
    {
      row++;
      j--;
    }
  }
  
  if (col > 2 || row > 2)
  {
    while (color == new_color)
    {
      new_color = color_vect[rand() % color_vect.size()];
    } 
  }
  if (new_color != color)
  {
    colors_grid[x][y] = new_color;
  }
  
}

void Canvas::cells_color(){
  
  for (int i = 0; i < 9; i++){
    colors_grid.emplace_back ();
    for (int j = 0; j < 9; j++){
      std::vector <string> color_vect {"bleu", "rouge", "orange", "jaune", "vert", "mauve"};
      std::string color = color_vect[rand() % color_vect.size()];
      colors_grid[i].push_back(color);
    }
  }

   for (int i = 0; i < 9 ; i++){
      for (int j = 0; j< 9; j++){
        bool res = check_alligner(cells[i][j]);
        delete_alligner();
      }
    }
    
    
  
}

void Canvas::initialize ()
{
  cells_color();
  
  for (int x = 0; x < 9; x++)
  {
    cells.emplace_back ();
    for (int y = 0; y < 9; y++)
      {
        std::string color = colors_grid[x][y];
        
        cells[x].push_back ({{x * 80 , y * 80}, 80, 80, color});
      }
  }

  cree_voisin();

  //##########################################  CA PRINT SUR TERMINAL 
  cout << "\n" << endl;
  for (auto item : cells) {
        for (auto i : item) {
            cout << "["<< i.get_color() << "]; ";
        }
        cout<<"\n" << endl;
  }
  cout << endl;
  //##########################################  CA PRINT SUR TERMINAL
  
    
}



bool Canvas::check_alligner(Cell c){

  horizontally_aligned.push_back(c);
  vertically_aligned.push_back(c);
  int i = c.get_center().x/80;
  int j = c.get_center().y/80;
  string color_c = c.get_color();

  // vertical vers le bas
  j++;
  while (j < 9 && cells[i][j].get_color() == c.get_color())
  {
    vertically_aligned.push_back(cells[i][j]);
    j++;
  }
  j = c.get_center().y/80;

  // vertical vers le haut
  j--;
  while (j >= 0 && cells[i][j].get_color() == c.get_color())
  {
    vertically_aligned.push_back(cells[i][j]);
    j--;
  }

  j = c.get_center().y/80;
  // horizontal vers la droite
  i++;
  while (i < 9 && cells[i][j].get_color() == c.get_color())
  {
    horizontally_aligned.push_back(cells[i][j]);
    i++;
  }
  i = c.get_center().x/80;

  // horizontal vers la gauche
  i--;
  while (i >= 0 && cells[i][j].get_color() == c.get_color())
  {
    horizontally_aligned.push_back(cells[i][j]);
    i--;
  }

  return horizontally_aligned.size() >= 3 || vertically_aligned.size() >= 3;
  
}

void Canvas::delete_alligner(){

  if (horizontally_aligned.size() >= 3){ 
    
       score += 1;
   
    for (int x = 0; x < horizontally_aligned.size(); x++){
      int x_ = horizontally_aligned[x].get_center().x/80;
      int y_ = horizontally_aligned[x].get_center().y/80;
      cells[x_][y_].set_color("vide");
      //cells[x_][y_].reposition({1000, 1000});
    }
  }

  if (vertically_aligned.size() >= 3){ 
    score +=1;
    for (int x = 0; x < vertically_aligned.size(); x++){
      int x_ = vertically_aligned[x].get_center().x/80;
      int y_ = vertically_aligned[x].get_center().y/80;
      cells[x_][y_].set_color("vide");
      //cells[x_][y_].reposition({1000, 1000});
    }    
  }
  horizontally_aligned.clear();
  vertically_aligned.clear(); 

}

void Canvas::move_fruits(){

  std::vector <string> color_vect {"bleu", "rouge", "orange", "jaune", "vert", "mauve"};
  
    for (int i = 0; i < 9 ; i++){
      for (int j = 0; j< 9; j++){

        if (cells[i][j].get_color() == "vide"){
          if (j==0){
            std::string color = color_vect[rand() % color_vect.size()];
            cells[i][j].set_color(color);
          }else{
            cells[i][j].set_color(cells[i][j-1].get_color());
            cells[i][j-1].set_color("vide");
          }
        }
      }
    }  

    cree_voisin();

    for (int i = 0; i < 9 ; i++){
      for (int j = 0; j< 9; j++){
        bool res = check_alligner(cells[i][j]);
        delete_alligner();
      }
    }
    
  
}

void Canvas::swap(Cell * c){
   
     if (c->is_selected()){
      cout << "---------------------------------" << endl;
      cout << "debut" << endl;
      cout << c->get_center().x << "  " << c->get_center().y << "  x=" << c->get_center().x/80 << "y=" << c->get_center().y/80 << endl;
      cout << c->get_color() << endl;
      cout << "---------------------------------" << endl;
       selected.push_back (c);
       c->unselect();
    }

    if ((selected.size() == 2) && (selected[0]->is_neighbor(selected[1]))){
              
        Point save_center{selected[0]->get_center().x, selected[0]->get_center().y};

        selected[0]->reposition(selected[1]->get_center());
        selected[0]->set_center(selected[1]->get_center());

        selected[1]->reposition(save_center);
        selected[1]->set_center(save_center);

        int i1 = selected[1]->get_center().x/80;
        int j1 = selected[1]->get_center().y/80;
        
        int i0 = selected[0]->get_center().x/80;
        int j0 = selected[0]->get_center().y/80;

        Cell sauv = cells[i1][j1];
        cells[i1][j1] = cells[i0][j0];
        cells[i0][j0] = sauv;

        bool res_1 = check_alligner(cells[i0][j0]);
        delete_alligner();
       
        bool res_2 = check_alligner(cells[i1][j1]);
        delete_alligner();

        for (int i = 0; i < 100 ;i++){
          move_fruits();
        }

        cout << "score : " << score << endl;
        

        if (!res_1 && !res_2){

          cout << "DEPLACEMENT SERT A RIEN" << endl;

          Cell sauv = cells[i0][j0];
          cells[i0][j0] = cells[i1][j1];
          cells[i1][j1] = sauv;

          Point save_center_{selected[1]->get_center().x, selected[1]->get_center().y};

          selected[1]->reposition(selected[0]->get_center());
          selected[1]->set_center(selected[0]->get_center());

          selected[0]->reposition(save_center_);
          selected[0]->set_center(save_center_);

        }

        //##########################################  CA PRINT SUR TERMINAL 
        cout<<"\n" << endl;
        for (auto item : cells) {
          for (auto i : item) {
            cout << "["<< i.get_color() << "]; ";
          }
          cout<<"\n" << endl;
        }
        cout << endl;
        //##########################################  CA PRINT SUR TERMINAL

      
      selected.clear();

    }
    else if ((selected.size() == 2) && (!selected[0]->is_neighbor (selected[1]))){
      cout << "PAAAS VOISIN" << endl;

      selected.clear();
      selected.push_back (c);
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
        swap(&c);
    }

}


void Canvas::keyPressed(int keyCode) {
  switch (keyCode) {
    case 'a': 
        initialize();
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