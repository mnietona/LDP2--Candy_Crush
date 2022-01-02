/*
Cours : INFO F 202
Projet : Candy Crush
Auteurs : NIETO NAVARRETE Matias, QUERINJEAN Arnaud
Date de remise : 13 janvier 2021
*/

#include <FL/fl_ask.H>
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

Point Plateau::get_position () const
{
  return {x(), y()};
}

bool Plateau::contains (Point p) const
{
  return p.x >= x() &&
         p.x < x()+ w() &&
         p.y >= y() &&
         p.y < y() + h();
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
 * Class repris du Labo 3
 * Elle permet d'ecrire du texte sur l'ecran
 * 
 */
class Text {
  Point center;
  string s;
  int fontSize;
  Fl_Color color;
 public:
  //Constructor
  Text(string s, Point center, int fontSize = 50, Fl_Color color = FL_BLACK):
    s{s}, center{center}, fontSize{fontSize}, color{color} {}
 
  //Draw
  void draw();
 
  //Setters and getters
  string getString() {
    return s;
  }
  void setString(const string &newString) {
    s = newString;
  }
  int getFontSize() {
    return fontSize;
  }
  void setFontSize(int newFontSize) {
    fontSize = newFontSize;
  }
  Point getCenter() {
    return center;
  }
  void setCenter(Point newCenter) {
    center = newCenter;
  }
};
 
void Text::draw() {
  fl_color(color);
  fl_font(FL_HELVETICA, fontSize);
  int width, height;
  fl_measure(s.c_str(), width, height, false);
  fl_draw(s.c_str(), center.x-width/2, center.y-fl_descent()+height/2);
}
 

/**
 * Class repris du Labo 2 
 * Permet de cree un rectangle sur l'ecran
 */
class Rectangle {
  Point center;
  int w, h;
  Fl_Color fillColor, frameColor;
 public:
  Rectangle(Point center, int w, int h,
            Fl_Color frameColor = FL_BLACK,
            Fl_Color fillColor = FL_WHITE);
  void draw();
};
Rectangle::Rectangle(Point center, int w, int h,
                     Fl_Color frameColor,
                     Fl_Color fillColor):
  center{center}, w{w}, h{h}, fillColor{fillColor}, frameColor{frameColor} {}
 
void Rectangle::draw() {
  fl_draw_box(FL_FLAT_BOX, center.x-w/2, center.y-h/2, w, h, fillColor);
  fl_draw_box(FL_BORDER_FRAME, center.x-w/2, center.y-h/2, w, h, frameColor);
}


/**
 * Class repris du Labo 10
 * Pemret de cree un rectangle avec une du texte a l'interieur
 */
class TextRectangle : public Rectangle, public Text{
  public:
  TextRectangle(Point center, int w, int h, string s, Fl_Color frameColor = FL_BLACK, Fl_Color fillColor = FL_WHITE) : 
  Rectangle{center, w, h,frameColor, fillColor,}, Text{s, center} {}
  void draw();
 
};
 
void TextRectangle::draw() {
  Rectangle::draw();
  Text::draw();
}


/**
 * 
 *  Dessine un bonbon sur l'ecran 
 */
class Cell {

    Plateau *plateau;
    Candy *candy;
    Point center;
    int fruit;
    int w, h;
    bool selectionner = false;
    char *image;
    map<int,string> liste_bombon = {{0, "image/explosion.png",},{1, "image/bleu.png",},{2, "image/rouge.png",},
            {3, "image/vert.png",},{4, "image/jaune.png",},{5, "image/orange.png",},{6, "image/mauve.png",},{7,"image/mur.png",},
            {8,"image/r_bleu.png",},{9,"image/r_rouge.png",},{10,"image/r_vert.png",},{11,"image/r_jaune.png",},{12,"image/r_orange.png",},
            {13,"image/r_mauve.png"},{14,"image/e_bleu.png",},{15,"image/e_rouge.png",},{16,"image/e_vert.png",},{17,"image/e_jaune.png",},
            {18,"image/e_orange.png",},{19,"image/e_mauve.png"},{20,"image/couleur.png",},{27," ",}};

 public:
  // Constructor
  Cell(Point center, int w, int h, int fruit);

  // Methodes
  void cree_bombon();  // fonction repreise sur github
  void toucher(int fruit,bool s); // animation lors du survelement de la souris sur bombon
  void explosion();
  void deplace(Point d); // redessine le bombom a x et y 
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
            {3, "image/vert_s.png",},{4, "image/jaune_s.png",},{5, "image/orange_s.png",},{6, "image/mauve_s.png",},{7,"image/mur.png",},
            {8,"image/r_bleu.png",},{9,"image/r_rouge.png",},{10,"image/r_vert.png",},{11,"image/r_jaune.png",},{12,"image/r_orange.png",},
            {13,"image/r_mauve.png"},{14,"image/e_bleu.png",},{15,"image/e_rouge.png",},{16,"image/e_vert.png",},{17,"image/e_jaune.png",},
            {18,"image/e_orange.png",},{19,"image/e_mauve.png"},{20,"image/couleur.png",},{27," ",}};
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

void Cell::explosion()
{
  mutex lock;
  lock.lock();
  fruit = 0;
  image = &liste_bombon.find (fruit)->second[0];
  candy = new Candy (image);
  plateau->image (candy);
  lock.unlock();
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
 *  Cree un score 
 * 
 */
class Scores{
    int scores = 0;
    public:
    Scores(){
    }
    void score(); // augmente le score de 10
    int get_score(); // renvoi le score
    int lecture_fichier_score(); // lit le meilleur score 
    void ecrire_fichier_score(); // ecrit le meilleur score dans le fichier 
    void reset_score(); // remet le meilleur score a 0
    void moins_score(); // diminue le score de 10
    void score_egale_0(); // remet le score a 0
};

void Scores::score(){
    scores += 10;
}

int Scores::get_score(){
    return scores;
}

void Scores::ecrire_fichier_score(){
    string const nomFichier("fichier/meilleur_score.txt");
    ofstream monFlux(nomFichier.c_str());
    monFlux << scores << endl;
}

int Scores::lecture_fichier_score(){
    ifstream fichier("fichier/meilleur_score.txt");
    int jsp;
    fichier >> jsp;
    return jsp;
}

void Scores::reset_score(){
    string const nomFichier("fichier/meilleur_score.txt");
    ofstream monFlux(nomFichier.c_str());
    monFlux << 0 << endl;
}

void Scores::moins_score(){
    scores-=10;
}

void Scores::score_egale_0(){
    scores = 0;
}

/**
 *  Permet d'effacer et de cree les bonbon speciaux
 * 
 */
class Effacer_bonbon: public Scores{
    
    public:
    vector<Cell > horizontal;
    vector<Cell > vertical;
    vector< vector<Cell> > cells;
    Effacer_bonbon(){
    }
    bool a_coter(int x0, int y0, int x1, int y1); // verifie que 2 bonbon sont l'un a coter de l'autre 
    bool a_coter_diagonal(int x0, int y0, int x1, int y1); // verifie que 2 bonbon sont l'un a coter de l'autre  en diagonal
    void super_bonbon(int x1, int y1, int x0, int y0); // si un super bonbon est selectionner fait son pouvoir ( 5 alligner )
    void pouvoir_rayer(int sauve); // pouvoir du bonbon rayer ( 4 alligner )
    void pouvoir_emballer(int x, int y); // pouvoir du bonbon emballer ( L ou T )
    void condition_super_bonbon(int i, int j, int x, int y, int sauve); // permet de garder les couleur du bonbon qui doivent etre effacer 
    void efface(); // efface les allognement 
    int couleur_special(vector<Cell > position, int couleur_new_bonbon ); // cree bonbon special pour les allignements
    void couleur_bonbon_emballer();  // cree bonbon emballer 
    void efface_vertical_horizontal(vector<Cell > position,int couleur_new_bonbon, string direction); // efface tt les allignements
};

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

            for (int i = 0; i < 9; i++){
              for (int j = 0; j < 9; j++){
                if (cells[i][j].get_color() == 0){
                  cells[i][j].explosion();
                }
              }
            }

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

void Canvas::lire_fichier(const char* fichier_input){
    couleur.clear();
    ifstream fichier(fichier_input);
    vector<int> couleur_fichier;
    couleur_fichier.clear();
    int fruit = 0;
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

void Canvas::cree_plateau(){ 
  for (int x = 0; x < 9; x++)
  {
    cells.emplace_back();
    for (int y = 0; y < 9; y++){
        int fruit = 27; //couleur[x][y];
        cells[x].push_back ({{x * 80 , y * 80}, 80, 80, fruit});
      }
  } 
}

bool Canvas::debut_check_horizontal(){
    bool horizontal = false;
    for (int j= 0; j < 9; j++){
       for (int i = 1; i < 8; i++){
           if (couleur[i][j] == 7){
               continue; }
           else if( couleur[i][j] == couleur[i-1][j] && couleur[i][j] == couleur[i+1][j]){
               horizontal = true;
               while(couleur[i][j] == couleur[i-1][j]){
                   int fruit = rand() %(7-1) + 1;
                   couleur[i][j] = fruit;
                }
           }
        }
   }
   return horizontal;
}

bool Canvas::debut_check_vertical(){
   bool vertical = false;
   for (int i= 0; i < 9; i++){
       for (int j = 1; j < 8; j++){
           if (couleur[i][j] == 7){
               continue; }
           else if( couleur[i][j] == couleur[i][j-1] && couleur[i][j] == couleur[i][j+1]){
               vertical = true;
               while(couleur[i][j] == couleur[i][j-1]){
                   int fruit = rand() %(7-1) + 1;
                   couleur[i][j] = fruit;
                }
            }
       }
   }
   return vertical;
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
        Mouvement::deplacement(&c);
    }

   if (Scores::get_score() >= 6000 && !continuer){
      switch (fl_ask("Vous avez atteint l'objectif, Félicitation !\n\nVoulez vous passez au niveau suivant?")){
        case 0:
            continuer = true;
            break;
        case 1:
            Scores::score_egale_0();
            cases.clear();
            if (niveau != 6){
                select_level(niveau+1);
                niveau +=1;
            }else{
                fl_message("Vous avez reussi le dernier niveau");
            }
            break;
        }
    }


}

void Canvas::keyPressed(int keyCode) {
  switch (keyCode) {
    case 'a': // vérifie si aucun mouvement
       if (!Mouvement::verifie_mouvement_possible_officiel()){
          fl_message("Plus de mouvement possible, Les bonbons vont être remplacé");
          Mouvement::reset_plateau();
       }else if (Mouvement::verifie_mouvement_possible_officiel()){
           fl_message("Il y a toujours un mouvement possible");
       }
       break;

    case 'd':
        switch ( fl_choice("Quel niveau voulez vous ?", "Impossible", "Hard", "Difficile") ) {
            case 0: 
                cases.clear();
                Scores::score_egale_0();
                select_level(6);
                niveau = 6;
                break;           
            case 1:
                cases.clear();
                Scores::score_egale_0();
                select_level(5);
                niveau = 5;
                break;  
            case 2:
                cases.clear();
                Scores::score_egale_0();
                select_level(4);
                niveau = 4;
                break; 
            }
        break;
    case 'f':
        switch ( fl_choice("Quel niveau voulez vous ?", "Normal", "Facile","Débutant") ) {
            case 0: 
                cases.clear();
                Scores::score_egale_0();
                select_level(3);
                niveau = 3;
                break;
            case 1:
                cases.clear();
                Scores::score_egale_0();
                select_level(2);
                niveau = 2;
                break;   
            case 2:
                cases.clear();
                Scores::score_egale_0();
                select_level(1);
                niveau = 1;
                break;         
            }
        break;
    case 'r': // reset meilleur score
       Scores::reset_score();
       break;
    case ' ': // ouvre le jeu
       if (niveau == 0){
         select_level(1);
       }
       jouer = true; 
       break;
    case 'q':
        exit(0);
  }
}

bool Canvas::get_jouer(){
    return jouer;
}

void Canvas::select_level(int niveau){
   
    switch(niveau){
        case 1:
            couleur.clear();
            for (int i = 0; i < 9; i++){
            couleur.emplace_back ();
            for (int j = 0; j < 9; j++){
                int fruit = rand() %(7-1) +1;
                couleur[i].push_back(fruit); }
            }
            // boucle tant que 3 allignement
            do{
            debut_check_horizontal();
            debut_check_vertical();
            }while( debut_check_horizontal() && debut_check_vertical() );
            break;
        case 2:
            lire_fichier("fichier/niveau_2.txt");
            break;
        case 3:
            lire_fichier("fichier/niveau_3.txt");
            break;
        case 4:
            lire_fichier("fichier/niveau_4.txt");
            break;
        case 5:
            lire_fichier("fichier/niveau_5.txt");
            break;
        case 6:
            lire_fichier("fichier/niveau_6.txt");
            break;
           
    }

    for (int i =0; i < 9; i++){
        for (int j=0; j < 9; j++){
            cases.push_back(&cells[i][j]);
        }
    }
    int x=0;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j< 9; j++){
            int fruit = couleur[i][j];
            cells[i][j].set_color(fruit);
            cases[x]->set_color(fruit);
            x++;
        }
    }
    Mouvement::print();
}

/**
 * Cree la fenetre  
 *
 * Pas toucher 
 */
class MainWindow : public Fl_Window{
  Canvas canvas;
 public:
  MainWindow() : Fl_Window(200, 100, windowWidth, windowHeight, "Candy crush") {
    //Fl::background(32,32,32);
    Fl::add_timeout(1.0/refreshPerSecond, Timer_CB, this);
    resizable(this);
  }

  void affiche_case_text_jeu(); // affiche les option, score, objetif et meilleur score
  void ecran_acceuil(); //affiche un écran d'acceuil

  void draw() override {
       
      ecran_acceuil();

      if (canvas.get_jouer()){ // si espace toucher 
        Fl_Window::draw();
        affiche_case_text_jeu();
        }
  }

  int handle(int event) override {
    switch (event) {
      case FL_MOVE:
        canvas.mouseMove(Point{Fl::event_x(), Fl::event_y()});
        return 1;
      //case FL_PUSH:
        //canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
        //return 1;
      case FL_KEYDOWN:
        canvas.keyPressed(Fl::event_key());
        return 1;
      case FL_DRAG: // Permet le deplacer de bonbon par glissement 
        canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
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

void MainWindow::affiche_case_text_jeu(){
    
    int n1 = canvas.Scores::get_score();
    Text("Score", {900, 45}, 20).draw();
    string scorees = to_string(n1);
    TextRectangle score({900,100}, 240, 80, scorees );
    score.draw();

    Text("Objectif", {900, 195}, 20).draw();
    string obj = "6 000";
    TextRectangle objectif({900,250}, 240, 80, obj );
    objectif.draw();


    Text("Meilleur score", {900, 345}, 20).draw();
    int n2 = canvas.Scores::lecture_fichier_score();

    if (n2 < n1){
        n2 = n1;
        canvas.Scores::ecrire_fichier_score();
    }
    string meilleur_score = to_string(n2);
    TextRectangle meuilleur_score({900,400}, 240, 80, meilleur_score );
    meuilleur_score.draw();

    Text("Options : ", {820, 500}, 20).draw();
    Text("A -> Plus de mouvements ?", {900, 530}, 20).draw();
    Text("F -> Niveau facile", {900, 560}, 20).draw();
    Text("D -> Niveau Difficile", {900, 590}, 20).draw();
    

  }

void MainWindow::ecran_acceuil(){

    TextRectangle ok({0,0},windowWidth*2 , windowHeight*2 , "", FL_BLACK, fl_rgb_color(214, 214, 214));
    ok.draw();

    Text("Candy Crush", {windowWidth/2 , 100}, 70).draw();
    Text("Par Arnaud Querinjean et Matias Nieto", {windowWidth/2 ,200}, 25).draw();
    Text("Appuyer ESPACE pour jouer ", {windowWidth/2,620}, 22).draw();
    Text("Meuilleur score", {windowWidth/2,310}, 20).draw();

    int n2 = canvas.Scores::lecture_fichier_score();
    string meilleur_score = to_string(n2);
    TextRectangle meuilleur_score({windowWidth/2, windowHeight/2+10}, 240, 100, meilleur_score );
    meuilleur_score.draw();
    
    Text("Appuyer R pour réinitialiser", {windowWidth/2, 430}, 20).draw();
    Text("Appuyer F pour niveau facile ou D pour niveau dure ", {windowWidth/2,650}, 15).draw();
  }
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
