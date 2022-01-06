/*
Cours : INFO F 202
Projet : Candy Crush
Auteurs : NIETO NAVARRETE Matias, QUERINJEAN Arnaud
Date de remise : 13 janvier 2021
*/
#include "canvas.h"

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
// check si 3 bonbons sont alligner ou plus horizontalement
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

// check si 3 bonbons sont alligner ou plus verticalement
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
   // permet de lire le score après chaque mouvement pour voir si objectif atteint
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

    case 'd': // permet de choisir un niveau difficile
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
    case 'f': // permet de choisir un niveau facile
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
// permet de choisir le fichier en fonction du parametre int niveau
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
// permet de mettre en place le plateau
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

}

