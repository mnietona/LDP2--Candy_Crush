#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <vector>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <map>
#include <memory>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Button.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <iostream>



using namespace std;


const int windowWidth = 1080;
const int windowHeight = 720;
const double refreshPerSecond = 60;


struct Point {
  int x, y;
};


/*------------------------------------------------------
Class Square et Candy :
      
    Permet d'inserer les images

------------------------------------------------------------*/
class Square: public Fl_Box {

 public:
  Square (Fl_Boxtype b, int x, int y, int w, int h, const char *l);
  Point get_position() const;

  bool contains (Point p) const;
};

Square::Square (Fl_Boxtype b, int x, int y, int w, int h, const char *l) :
    Fl_Box (b, x, y, w, h, l){}

bool Square::contains (Point p) const
{
  return p.x >= x() &&
         p.x < x()+ w() &&
         p.y >= y() &&
         p.y < y() + h();
}

Point Square::get_position () const
{
  return {x(), y()};
}

class Candy : public Fl_PNG_Image{

 public:
  Candy (const char *filename);

};

Candy::Candy (const char *filename) : Fl_PNG_Image(filename){}




/*------------------------------------------------------

Class Cell:

???????

------------------------------------------------------------*/

class Cell {

  Point center;
  int w, h;
  bool selected = false;
  int * counter;
  vector<Cell *> neighbors;

  Square *square = nullptr;
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
  string get_color();
  void set_color(string new_color);
  void set_center(Point new_center);
  void reposition(Point p);
  bool is_selected() const; // [[nodiscard]]  etait devant bool 
  void unselect();
  Point get_center() const;
  bool is_neighbor(Cell * cell) const;
  void setNeighbors (const vector<Cell *> &newNeighbors);
  vector<Cell *> get_Neighbors();
  void myNeighbors(Cell * c);
  
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
  std::map<std::string , std::string> candy_d = {{"blue", "image/bleu.png",},
                                                 {"red", "image/rouge.png",},
                                                 {"green", "image/vert.png",},
                                                 {"yellow", "image/jaune.png",},
                                                 {"orange", "image/orange.png",},
                                                 {"purple", "image/mauve.png",}};


  square= new Square(FL_FLAT_BOX, center.x, center.y, w, h+10, "");
  square->color(fl_rgb_color(214, 214, 214));
  file_image = &candy_d.find (color)->second[0];
  candy = new Candy(file_image);
  square->image(candy);

}

void Cell::mouseMove(Point mouseLoc) {
  if (square->contains(mouseLoc)) {
      square->color(FL_RED);

    } else {
      square->color(fl_rgb_color(214, 214, 214));
    }
}

void Cell::mouseClick(Point mouseLoc) {
    if ((square->contains (mouseLoc)))
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
  square->position(x,y);
  square->redraw();
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




/*--------------------------------------------------

Class Canvas:

????????

--------------------------------------------------*/


class Canvas {
  vector< vector<Cell> > cells;
  vector<Cell *> selected;
  vector<Cell> horizontally_aligned;
  vector<Cell> vertically_aligned;
  vector<vector<string> > colors_grid;

 public:
  Canvas ()
  {
    initialize ();
  }

  void check_image(int x, int y);
  void cells_color();
  void initialize ();
  bool are_aligned(Cell c);
  void delete_alignment();
  void check(Cell * c);
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
};



void Canvas::check_image(int x, int y){
  
  string color = colors_grid[x][y];
  int col = 0;
  int row = 0;
  std::vector <string> color_vect {"blue", "red", "orange", "yellow", "green", "purple"};
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
  
  for (int i = 0; i < 9; i++)
  {
    colors_grid.emplace_back ();
    for (int j = 0; j < 9; j++)
    {
      std::vector <string> color_vect {"blue", "red", "orange", "yellow", "green", "purple"};
      std::string color = color_vect[rand() % color_vect.size()];
      colors_grid[i].push_back(color);
    }}
    
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      check_image(i, j);
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
  
  // This computes the (pointers to) neighbors of each cell
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

bool Canvas::are_aligned(Cell c){

  horizontally_aligned.push_back(c);
  vertically_aligned.push_back(c);
  int i = c.get_center().x/80;
  int j = c.get_center().y/80;
  string color_c = c.get_color();
  vector<Cell> horizontal_cells = cells[i];
  bool res = false;


  // vertical vers le haut
  j++;
  while (j < 9 && cells[i][j].get_color() == c.get_color())
  {
    horizontally_aligned.push_back(cells[i][j]);
    j++;
  }
  j = c.get_center().y/80;

  // vertical vers le bas
  j--;
  while (j >= 0 && cells[i][j].get_color() == c.get_color())
  {
    horizontally_aligned.push_back(cells[i][j]);
    j--;
  }

  j = c.get_center().y/80;
  // horizontal vers la droite
  i++;
  while (i < 9 && cells[i][j].get_color() == c.get_color())
  {
    vertically_aligned.push_back(cells[i][j]);
    i++;
  }
  i = c.get_center().x/80;

  // horizontal vers la gauche
  i--;
  while (i >= 0 && cells[i][j].get_color() == c.get_color())
  {
    vertically_aligned.push_back(cells[i][j]);
    i--;
  }

  return horizontally_aligned.size() >= 3 || vertically_aligned.size() >= 3;
  
}

void Canvas::delete_alignment(){
  if (horizontally_aligned.size() >= 3)   // vertical
  {
    for (int x = 0; x < horizontally_aligned.size(); x++){
      int x_ = horizontally_aligned[x].get_center().x/80;
      int y_ = horizontally_aligned[x].get_center().y/80;
      cells[x_][y_].reposition({1000, 1000});
      cells[x_][y_].set_color("");
    }

  }


  if (vertically_aligned.size() >= 3)
  { 
    for (int x = 0; x < vertically_aligned.size(); x++){
      int x_ = vertically_aligned[x].get_center().x/80;
      int y_ = vertically_aligned[x].get_center().y/80;
      cells[x_][y_].reposition({1000, 1000});
      cells[x_][y_].set_color("");
    }
  }    
  horizontally_aligned.clear();
  vertically_aligned.clear();
}

void Canvas::check (Cell * c)
{ 
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
        string save_color = selected[0]->get_color();
        selected[0]->reposition(selected[1]->get_center());
        selected[0]->set_center(selected[1]->get_center());
        //selected[0]->set_color(selected[1]->get_color());
        selected[1]->reposition(save_center);
        selected[1]->set_center(save_center);
        //selected[1]->set_color(save_color);

        int i1 = selected[1]->get_center().x/80;
        int j1 = selected[1]->get_center().y/80;
        
        int i0 = selected[0]->get_center().x/80;
        int j0 = selected[0]->get_center().y/80;

        Cell sauv = cells[i1][j1];
        cells[i1][j1] = cells[i0][j0];
        cells[i0][j0] = sauv;
        
      
        vector<Cell *> save_neighbors0 = selected[0]->get_Neighbors();
        vector<Cell *> save_neighbors1 = selected[1]->get_Neighbors();

        save_neighbors0.push_back (selected[0]);
        save_neighbors0.erase (remove (save_neighbors0.begin(), save_neighbors0.end(), selected[1]), save_neighbors0.end());

        save_neighbors1.push_back (selected[1]);
        save_neighbors1.erase (remove (save_neighbors1.begin(), save_neighbors1.end(), selected[0]), save_neighbors1.end());

        selected[0]->setNeighbors (save_neighbors1);
        selected[1]->setNeighbors (save_neighbors0);

        selected[0]->myNeighbors (selected[1]);
        selected[1]->myNeighbors (selected[0]);
        
        bool res_1 = are_aligned(cells[i0][j0]);
        delete_alignment();
        bool res_2 = are_aligned(cells[i1][j1]);
        delete_alignment();


        if (!res_1 && !res_2){
          Cell sauv = cells[i0][j0];
          cells[i0][j0] = cells[i1][j1];
          cells[i1][j1] = sauv;

          Point save_center_{selected[1]->get_center().x, selected[1]->get_center().y};
          string save_color = selected[1]->get_color();
          selected[1]->reposition(selected[0]->get_center());
          selected[1]->set_center(selected[0]->get_center());
          //selected[1]->set_color(save_color);
          selected[0]->reposition(save_center_);
          selected[0]->set_center(save_center_);
          //selected[0]->set_color(selected[1]->get_color());
        }
      selected.clear();

    }
    else if ((selected.size() == 2) && (!selected[0]->is_neighbor (selected[1]))){
      selected.clear();
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
        check(&c);
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








/*--------------------------------------------------

MainWindow class.

Do not edit!!!!

-----


---------------------------------------------*/

class MainWindow : public Fl_Window {
  Canvas canvas;
 public:
  MainWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "WESHHHH") {
    Fl::add_timeout(1.0/refreshPerSecond, Timer_CB, this);
    resizable(this);
  }
  void draw() override {
    Fl_Window::draw();
    //canvas.draw();
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