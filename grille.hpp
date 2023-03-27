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

class Place{
    public:
    Coord pl;
    int ant;
    bool sugar;
    bool nid;
    float pherosucre;
    vector<float> pheronid;
    float r,g,b;

    
    Place(Coord c);
    
    Coord coord();
    
    float pheroSucre();
    float pheroNid(int col);
    int numeroFourmi();
    bool contientSucre();
    bool contientNid();
    bool estSurUnePiste();
    void poseSucre();
    void enleveSucre();
    void poseNid(int col);
    void poseFourmi(Fourmi f);
    void enleveFourmi();
    void posePheroNid(float n, int col);
    void posePheroSucre();
    void diminuePheroSucre();
    
};



class Grille{
    public:
    vector<Place>rail;
    Grille();
    
    Place chargePlace(Place p);
    void rangePlace(Place p);
    void linearisePheroNid(int col);
    void diminuePheroSucre();
    
};
/////////////////////////////////////////////////

bool estVide(Place p);

bool estPlusProcheNid(Place p1, Place p2,int col);
bool estPlusLoinNid(Place p1, Place p2, int col);


void deplaceFourmi(Fourmi &f1,Place &p1,Place &p2);

void placeNid(Grille &g, vector<Coord> v, int col) ;

void placeSucre(Grille &g, vector<Coord> v);
     
void placeFourmi(Grille &g, vector<Fourmi> v);
int cardinal(EnsCoord e);
Coord iemeElement(EnsCoord e, int n);

Coord voisinVideAleatoire(Grille g, Place p);

//int deux = 0; int trois = 0; int quatre = 0; int cinq = 0; int six = 0; int sept = 0;
bool condition2(Fourmi f, Place p1, Place p2);
void action2(Fourmi &f, Place &p1, Place &p2);

bool condition3(Fourmi f, Place p1, Place p2);
void action3(Fourmi &f, Place &p1, Place &p2);
bool condition4(Fourmi f, Place p1, Place p2);
void action4(Fourmi &f, Place &p1, Place &p2);
bool condition5(Fourmi f, Place p1, Place p2);
void action5(Fourmi &f, Place &p1, Place &p2);

bool condition6(Fourmi f, Place p1, Place p2);
void action6(Fourmi &f, Place &p1, Place &p2);
bool condition7(Fourmi f, Place p1, Place p2);
void action7(Fourmi &f, Place &p1, Place &p2);
bool condition_n(int x, Fourmi &f, Place &p1, Place &p2);

void action_n(int x, Fourmi &f, Place &p1, Place &p2);
        
            
     

    
///////////////////////////////////////////////////////////////


void creerPlacesGrille(EnsCoord &all,Grille &g);



void initialiserEmplacements(vector<Colonie> &lesColonies,EnsCoord &leSucre,EnsCoord &all,Grille &g);

void mettreAJourUneFourmi(Grille &g, Fourmi &f);

void mettreAJourEnsColonie(Grille &g, vector<Colonie> &lesColonies);

void majPheroSucre(Grille &g);


void dessinerGrille(Grille &g);