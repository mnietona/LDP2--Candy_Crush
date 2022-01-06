#include "cell.h"
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
  mutex animation;
  lock_guard lock(animation);
  fruit = 0;
  image = &liste_bombon.find (fruit)->second[0];
  candy = new Candy (image);
  plateau->image (candy);

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
