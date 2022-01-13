#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include "canvas.h"

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
  void ecran_acceuil_linux();
  void affiche_case_text_jeu_linux();
  
  void draw() override {
       
      ecran_acceuil_linux();

      if (canvas.get_jouer()){ // si espace toucher 
        Fl_Window::draw();
        affiche_case_text_jeu_linux();
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


#endif