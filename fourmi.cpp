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
#include "fourmi.hpp"
using namespace std;

Fourmi::Fourmi(Coord c, EnsCoord e): coor{c} {
    ind = e.position(c);
    sucre = false;
    team = 0;
}


Coord Fourmi::coord(){
    return coor;
}

int Fourmi::num(){
    return ind;
}

bool Fourmi::porteSucre(){
    return sucre;
}

void Fourmi::prendSucre(){
    sucre = true;
}

void Fourmi::poseSucre(){
    sucre = false;
}

void Fourmi::deplace(Coord c1,Coord c2){
    coor = c2;
}

Colonie::Colonie(EnsCoord E,EnsCoord n, int x,char col){
    index = x-1;
    for(size_t i = 0; i < E.tab.size(); i++){
        Fourmi f(E.tab[i],E);
        f.coul = col;
        f.team = x-1;
        colo.push_back(f);
    }
    ni = n;
    color = col;
    
}

