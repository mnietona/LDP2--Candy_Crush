
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Box.H>
#include <iostream>
#include <time.h>
#include <vector>
#include <cstdio>
#include <FL/Fl_Double_Window.H>
#include <string>
#include <math.h>
#include <chrono>
#include <random>

using namespace std;

const int windowWidth=1080;
const int windowHeight=700;
const double refreshPerSecond=60;

class Plateau{
    int min= 1;
    int max = 6;
    int nombre;
    string bonbon;
public:
    char* candy_color();
    void dessin();
};

char* Plateau::candy_color(){
    nombre = rand() %(max-min) + min;;
    if (nombre == 1) {
        bonbon = "Candy_images/bleu.png";};
    if (nombre == 2) {
        bonbon = "Candy_images/jaune.png";};
    if (nombre == 3) {
        bonbon = "Candy_images/mauve.png";};
    if (nombre == 4) {
        bonbon = "Candy_images/orange.png";};
    if (nombre == 5) {
        bonbon = "Candy_images/rouge.png";};
    if (nombre == 6) {
        bonbon = "Candy_images/vert.png";};
    char *a=new char[bonbon.size()+1]; 
    a[bonbon.size()]=0;
    memcpy(a,bonbon.c_str(),bonbon.size());

    return a;
}

void Plateau::dessin(){
    for (int i = 0; i < 9 ; i++){
        for (int j = 0; j < 9 ; j++){
        Fl_PNG_Image* candy = new Fl_PNG_Image(candy_color());
        Fl_Box *box = new Fl_Box(70*i,70*j,candy->w(),candy->h());
        box->image(candy);
        }
    }
}

struct Point {float x;float y;};
Point mousePos;

void mouseMove(int x, int y){
    mousePos.x=x;
    mousePos.y=y;
}
    
void keyPressed(int keyCode){
    exit(0);
}

/* ------ DO NOT EDIT BELOW HERE (FOR NOW) ------ */
class MainWindow : public Fl_Window {
    public:
    MainWindow() : Fl_Window(000, 000, windowWidth, windowHeight, "Candy Crush Saga") {
        Plateau p;
        p.dessin();
        Fl::add_timeout(1.0/refreshPerSecond, Timer_CB, this);
        resizable(this);
        
    }
    
    void draw() override {
        Fl_Window::draw();
        //::draw(); //Global draw function
    }


    int handle(int event) override {
        switch (event) {
            case FL_MOVE:
                mouseMove(Fl::event_x(),Fl::event_y());
                return 1;
            case FL_KEYDOWN:
                keyPressed(Fl::event_key());
        }
        return 0;
    }
    static void Timer_CB(void *userdata) {
        MainWindow *o = (MainWindow*) userdata;
        o->redraw();
        Fl::repeat_timeout(1.0/refreshPerSecond, Timer_CB, userdata);
    }
};

int main(int argc, char *argv[]) {
    MainWindow window; 
    window.show(argc, argv);
    return Fl::run();


}