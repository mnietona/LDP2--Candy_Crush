/*
Cours : INFO F 202
Projet : Candy Crush
Auteurs : NIETO NAVARRETE Matias, QUERINJEAN Arnaud
Date de remise : 13 janvier 2021
*/
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


#endif
