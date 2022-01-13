#include "mainwindow.h"

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
    Text("F -> Niveau facile", {855, 560}, 20).draw();
    Text("D -> Niveau Difficile", {865, 590}, 20).draw();
    

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

void MainWindow::affiche_case_text_jeu_linux(){
    
    int n1 = canvas.Scores::get_score();
    Text("Score", {900, 45}, 20).draw();
    string scorees = to_string(n1);
    TextRectangle score({900,100}, 240, 80, scorees );
    score.draw();

    Text("Objectif", {900, 200}, 20).draw();
    string obj = "6 000";
    TextRectangle objectif({900,275}, 240, 90, obj );
    objectif.draw();

    Text("Meilleur score", {880, 330}, 20).draw();
    int n2 = canvas.Scores::lecture_fichier_score();

    if (n2 < n1){
        n2 = n1;
        canvas.Scores::ecrire_fichier_score();
    }
    string meilleur_score = to_string(n2);
    TextRectangle meuilleur_score({900,400}, 240, 80, meilleur_score );
    meuilleur_score.draw();

    Text("Options : ", {820, 500}, 20).draw();
    Text("A -> Plus de mouvements ?", {880, 500}, 20).draw();
    Text("F -> Niveau facile", {852, 560}, 20).draw();
    Text("D -> Niveau Difficile", {851, 590}, 20).draw();
    

  }

void MainWindow::ecran_acceuil_linux(){

    TextRectangle ok({0,0},windowWidth*2 , windowHeight*2 , "", FL_BLACK, fl_rgb_color(214, 214, 214));
    ok.draw();

    // permet de placer dans la page d'acceuil les élements de texte
    Text("Candy Crush", {windowWidth/2-100 , 100}, 70).draw();
    Text("Par Arnaud Querinjean et Matias Nieto", {windowWidth/2-150 ,150}, 25).draw();
    Text("Appuyer ESPACE pour jouer ", {windowWidth/2-100,600}, 22).draw();
    Text("Meuilleur score", {windowWidth/2-30,320}, 20).draw();

    int n2 = canvas.Scores::lecture_fichier_score();
    string meilleur_score = to_string(n2);
    TextRectangle meuilleur_score({windowWidth/2, windowHeight/2+50}, 240, 100, meilleur_score );
    meuilleur_score.draw();
    
    Text("Appuyer R pour réinitialiser", {windowWidth/2-80, 450}, 20).draw();
    Text("Appuyer F pour niveau facile ou D pour niveau dure ", {windowWidth/2-175,620}, 15).draw();
  }