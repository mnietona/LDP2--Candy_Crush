#ifndef __SCORE_H
#define __SCORE_H

#include "cell.h"


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


#endif
