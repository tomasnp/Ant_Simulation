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


using namespace std;

const int TAILLEGRILLE = 40;

class Coord{
    
    public:
    int lig;
    int col;
    
    Coord(int lig, int col);
    int get_lig()const;
    int get_col()const;
    private:
    
    
};

class EnsCoord{
    public:
    vector<Coord>tab;
    //EnsCoord(vector<Coord>t);
    bool contient(Coord c);
    void ajoute(Coord c);
    void supprime(Coord c);
    bool estVide();
    int taille();
    Coord ieme(int n);
    Coord choixHasard();
    
    //private:
    int position(Coord c);
    
};

ostream& operator<<(ostream& out, Coord c);

bool operator==(Coord c, Coord d);

bool operator!=(Coord c, Coord d);

ostream& operator<<(ostream& out, EnsCoord e);

EnsCoord voisines(Coord c);


