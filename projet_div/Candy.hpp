#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Button.H>


/**
 * Affiche un bonbon dans la box
 * 
 */

class Candy : public Fl_PNG_Image{

 public:
  Candy (const char *filename);

};