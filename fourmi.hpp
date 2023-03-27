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



class Fourmi{
    
    public:
    bool sucre;
    Coord coor;
    int ind;
    char coul;
    int team;
    
   
    Fourmi(Coord c,EnsCoord e);
    
    Coord coord();
    int num();
    bool porteSucre();
    void prendSucre();
    void poseSucre();
    void deplace(Coord c1, Coord c2);
    private:
};


class Colonie{
    public:
    vector<Fourmi>colo;
    EnsCoord ni;
    char color;
    int index;
    Colonie(EnsCoord E,EnsCoord n,int i,char col);
    
};
    
        
        
        
        
        
        
        