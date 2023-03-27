#include <iostream>     // pour cout
#include <iomanip>      // pour setfill, setw
#include <sstream>      // pour ostringstream
#include <fstream>      // pour ofstream
#include <string>
#include <vector>
#include <array>
#include <stdexcept>   //exception
#include <cmath>       // sin, cos, sqrt, ...
#include <ctime>       // time
#include <cstdlib>     // rand srand
#include "coord.hpp"

using namespace std;



ostream& operator<<(ostream& out, Coord c){
    out << '('<<c.lig<<','<<c.col<<')';
    return out;
}

bool operator==(Coord c, Coord d){
    return c.lig == d.lig and c.col == d.col;
}

bool operator!=(Coord c, Coord d){
    return not (c == d);
}

ostream& operator<<(ostream& out, EnsCoord e){
    out << '{';
    for(size_t i = 0; i < e.tab.size(); i++){
        if ( i == e.tab.size()-1){
            out << e.tab[i]<<'}'<<endl;
        }
        else{
            out << e.tab[i]<<",";
        }
        
    }
    return out;
}

Coord::Coord(int l, int c): lig{l}, col{c} {
    if ( lig > TAILLEGRILLE or col > TAILLEGRILLE){
        throw string("ERREUR : coordonée en dehors de la grille !");
    }
}


//EnsCoord::EnsCoord(vector<Coord>t):tab{t}{
//}

int EnsCoord::position(Coord c){
    for (size_t i = 0; i < tab.size(); i++){
        if (tab[i] == c){
            return i;
        }
    }
    return -1;
}

bool EnsCoord::contient(Coord c){
    if( position(c) == -1){
        return false;
    }
    return true;
}

void EnsCoord::ajoute(Coord c){
    if (contient(c) == false){
        tab.push_back(c);
    }
}

void EnsCoord::supprime(Coord c){
    if (contient(c)){    
        vector<Coord>tab_sub = {};
        for(size_t i = 0; i < tab.size(); i++){
            if( tab[i] != c){
                tab_sub.push_back(tab[i]);
            }
        }
        tab = tab_sub;

    }else{
        throw string("ERREUR : Coord pas dans EnsCoord!");
    }
}

bool EnsCoord::estVide(){
    if(tab.size() == 0){
        return true;
    }
    return false;
}

int EnsCoord::taille(){
    return tab.size();
}

Coord EnsCoord::ieme(int n){
    return tab[n];
}


int Coord::get_lig()const{return lig;}

int Coord::get_col()const{return col;}

EnsCoord voisines(Coord c){
    EnsCoord res({}); 
    int imin, imax, jmin, jmax;
    imin = max(c.lig-1, 0);
    imax = min(c.lig+2, TAILLEGRILLE);
    jmin = max(c.col-1, 0);
    jmax = min(c.col+2, TAILLEGRILLE);
    for(int i = imin ; i <imax; i++){  
        for(int j = jmin; j<jmax; j++){       
            Coord ij = {i,j}; 
            if (ij != c ){
                res.ajoute(ij);
            }  
        }        
    }
    return res;
}

Coord EnsCoord::choixHasard(){
    return tab[rand() % tab.size()];
}
     

