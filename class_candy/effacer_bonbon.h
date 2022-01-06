/*
Cours : INFO F 202
Projet : Candy Crush
Auteurs : NIETO NAVARRETE Matias, QUERINJEAN Arnaud
Date de remise : 13 janvier 2021
*/
#ifndef __EFFACER_BONBON_H
#define __EFFACER_BONBON_H

#include "score.h"


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


#endif
