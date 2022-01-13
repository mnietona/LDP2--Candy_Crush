#include "score.h"

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

