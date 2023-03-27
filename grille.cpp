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
#include "grille.hpp"
using namespace std;

Place::Place(Coord c): pl{c}{
    ant = -1;
    sugar = false;
    nid = false;
    pherosucre = 0;
    for(size_t i = 0; i < 3; i++){
        pheronid.push_back(0);
    }
    r = 0;g = 0;b = 0;   
}

Coord Place::coord(){
    return pl;
}    

float Place::pheroSucre(){
    return pherosucre;
}

float Place::pheroNid(int col){
    return pheronid[col];            
}

int Place::numeroFourmi(){
    return ant;
}

bool Place::contientSucre(){
    return sugar;
}

bool Place::contientNid(){
    return nid;
}

bool Place::estSurUnePiste(){
    if( pheroSucre() > 0){
        return true;
    }
    return false;
}

void Place::poseSucre(){
    sugar = true;
    r = 255;g = 255;b = 255;
}

void Place::enleveSucre(){
    sugar = false;
    r = 0;g = 0;b = 0;
}

void Place::poseNid(int col){
    nid = true;
    r = 255;g = 127;b = 0;
}

void Place::poseFourmi(Fourmi f){
    ant = f.ind;
    if(f.coul == 'g'){
        r = 0;g = 255;b = 0;
    }
    if(f.coul == 'b'){
        r = 0;g = 0;b = 255;
    }
    if(f.coul == 'r'){
        r = 255;g = 0;b = 0;
    }
}

void Place::enleveFourmi(){
    ant = -1;
    r = 0;g = 0;b = 0;
}

void Place::posePheroNid(float n, int col){
    pheronid[col] = n;
    //r = pheronid*255;g = 255;b = 255;
}

void Place::posePheroSucre(){
    pherosucre = 255;
    //r = pherosucre;g = pherosucre;b = pherosucre;
}

void Place::diminuePheroSucre(){
    pherosucre -= 15;
    //r -= 15;g -= 15;b -= 15;
}


Grille::Grille(){
    rail = {};
}
    
Place Grille::chargePlace(Place p){
    for(size_t i = 0; i < rail.size(); i++){
        if (rail[i].pl == p.pl){
            return rail[i];
        }
    }
    throw invalid_argument("Pas de Place");
}

void Grille::rangePlace(Place p){
    for(size_t i = 0; i < rail.size(); i++){
        if (rail[i].pl == p.pl){
            rail[i]= p;
        }    
    }
}

void Grille::linearisePheroNid(int col){
    bool stable = false;
    while(not stable){
        stable = true;
        for(size_t i = 0; i< rail.size(); i++){
            Place p = chargePlace(rail[i]);
            if(p.pheroNid(col)<1){
                
                EnsCoord coordVois = voisines(rail[i].pl);
                float maxPhero = 0;
                for(size_t j = 0; j < coordVois.tab.size(); j++){
                    Place voisin = chargePlace(coordVois.tab[j]); 
                    maxPhero = max(maxPhero, voisin.pheroNid(col));
                }
                maxPhero = maxPhero - (float(1.0))/(float(TAILLEGRILLE)); 
                if(maxPhero > p.pheroNid(col)){
                   p.posePheroNid(maxPhero,col);
                   rangePlace(p);
                   stable = false;
                }
            }
        }
    }
}





/////////////////////////////////////////////////////////////////

bool estVide(Place p){
    if(p.ant == -1 and p.sugar == false and p.nid == false){
        return true;
    }
    return false;
}

bool estPlusProcheNid(Place p1, Place p2,int col){
    return p1.pheroNid(col) >= p2.pheroNid(col);
}

bool estPlusLoinNid(Place p1, Place p2, int col){
    return p1.pheroNid(col) <= p2.pheroNid(col);
}


void deplaceFourmi(Fourmi &f1,Place &p1,Place &p2){
    if((voisines(p1.pl).contient(p2.pl)) and estVide(p2)){
        p1.enleveFourmi();
        p1.posePheroSucre();
        p2.poseFourmi(f1);
        f1.deplace(p1.pl,p2.pl);
    }
}

void placeNid(Grille &g, vector<Coord> v,int col) {
    for (Coord c : v) {
        Place p = g.chargePlace(c);    // copie de la place
        p.poseNid(col);
        p.posePheroNid(1,col);
        g.rangePlace(p);               // range la copie dans la grille
    }
}

void placeSucre(Grille &g, vector<Coord> v) {
    for (Coord c : v) {
        Place p = g.chargePlace(c);
        p.poseSucre();
        p.posePheroSucre();
        g.rangePlace(p);               
    }
}
     
void placeFourmi(Grille &g, vector<Fourmi> v) {
    for (Fourmi f : v) {
        Place p = g.chargePlace(f.coor);    
        p.poseFourmi(f);
        g.rangePlace(p);               
    }
} 

int cardinal(EnsCoord e){
    return e.tab.size();
}

Coord iemeElement(EnsCoord e, int n){
    return e.tab[n];
}

Coord voisinVideAleatoire(Grille g, Place p){
    /* retourne les coordonnées dans la grille g d’un voisin vide de p choisi aléatoirement */
    EnsCoord res = voisines(p.pl);
    vector<Place>vois={};
    for (size_t i = 0; i < g.rail.size(); i++){
        for(size_t j = 0; j < res.tab.size(); j++){
            if(res.tab[j] == g.rail[i].pl and estVide(g.rail[i])){
                vois.push_back(g.rail[i]);
            }
        }
    }
    return vois[rand()%vois.size()].pl;  
}


bool condition2(Fourmi f, Place p1, Place p2){
    return (f.porteSucre()==false and p2.contientSucre());
}

void action2(Fourmi &f, Place &p1, Place &p2){
    f.prendSucre();
    p1.posePheroSucre();
    //deux++;
}

bool condition3(Fourmi f, Place p1, Place p2){
    return (f.porteSucre() and p2.contientNid());
}
void action3(Fourmi &f, Place &p1, Place &p2){
    f.poseSucre();
    //trois++;
}
bool condition4(Fourmi f, Place p1, Place p2){
    return (f.porteSucre() and estVide(p2) and estPlusProcheNid(p2, p1,f.team));
} 
void action4(Fourmi &f, Place &p1, Place &p2){
    deplaceFourmi(f,p1,p2);
    p2.posePheroSucre();
    //quatre++;
}
bool condition5(Fourmi f, Place p1, Place p2){
    return (not(f.porteSucre()) and p1.estSurUnePiste() and estVide(p2)and estPlusLoinNid(p2, p1,f.team) and p2.estSurUnePiste());
}
void action5(Fourmi &f, Place &p1, Place &p2){
    deplaceFourmi(f,p1,p2);
    //cinq++;
}

bool condition6(Fourmi f, Place p1, Place p2){
    return (not(f.porteSucre()) and p2.estSurUnePiste() and estVide(p2));
}
void action6(Fourmi &f, Place &p1, Place &p2){
    deplaceFourmi(f,p1,p2);
    //six++;
}
bool condition7(Fourmi f, Place p1, Place p2){
    return (not(f.porteSucre()) and estVide(p2));
} 
void action7(Fourmi &f, Place &p1, Place &p2){
    deplaceFourmi(f,p1,p2);
    //sept++;
}

bool condition_n(int x, Fourmi &f, Place &p1, Place &p2){
    switch(x){
        case 1: case 2: return condition2(f,p1,p2);
        case 3: return condition3(f,p1,p2);
        case 4: return condition4(f,p1,p2);
        case 5: return condition5(f,p1,p2);
        case 6: return condition6(f,p1,p2);
        case 7: return condition7(f,p1,p2);
        default: return false;
    }
}

void action_n(int x, Fourmi &f, Place &p1, Place &p2){
    switch(x){
        case 1: case 2:  action2(f,p1,p2);
        case 3:  action3(f,p1,p2);
        case 4:  action4(f,p1,p2);
        case 5:  action5(f,p1,p2);
        case 6:  action6(f,p1,p2);
        case 7:  action7(f,p1,p2);
        default: return;
    }
}
        
            
     

    
///////////////////////////////////////////////////////////////


void creerPlacesGrille(EnsCoord &all,Grille &g){
    for (int j = TAILLEGRILLE; j >= 0; j--){
        for (int i = 0; i <= TAILLEGRILLE; i++){
            Coord c(i,j);
            all.ajoute(c);
            Place p(c);
            g.rail.push_back(p);
        }
    }
}




void initialiserEmplacements(vector<Colonie> &lesColonies,EnsCoord &leSucre,EnsCoord &all,Grille &g){
    for( size_t i = 0; i < lesColonies.size(); i++){
        for (size_t j = 0; j < lesColonies[i].colo.size(); j++){
            
            placeFourmi(g,lesColonies[i].colo);
        }
        placeNid(g,lesColonies[i].ni.tab,lesColonies[i].index);
        g.linearisePheroNid(lesColonies[i].index);
        
    }
    placeSucre(g,leSucre.tab);
    
    
    
}

void mettreAJourUneFourmi(Grille &g, Fourmi &f){
/* déplace une fourmi en appliquant les règles de comportement des fourmis */
    Place pf = g.chargePlace(f.coor);
    EnsCoord voisCoord = voisines(pf.pl);

    Place vois = g.chargePlace(voisines(f.coor).choixHasard());
    
    for(int i = 2; i < 8; i++){
        for(size_t j = 0; j < voisCoord.tab.size(); j++){
            if(condition2(f,pf,vois)){
                action2(f,pf,vois);
                g.rangePlace(pf);
                g.rangePlace(vois);
                return;
            }
            if(condition_n(i,f,pf,vois)){
                action_n(i,f,pf,vois);
                g.rangePlace(pf);
                g.rangePlace(vois);
                return;
            }
        }
    }
    
}

void mettreAJourEnsColonie(Grille &g, vector<Colonie> &lesColonies){
    for(size_t i = 0; i < lesColonies.size(); i++){
        for(size_t j = 0; j < lesColonies[i].colo.size(); j++){
            mettreAJourUneFourmi(g, lesColonies[i].colo[j]);
        }
    }
}

void majPheroSucre(Grille &g){
    for(size_t i = 0; i < g.rail.size(); i++){
        if (g.rail[i].estSurUnePiste()){ 
            g.rail[i].diminuePheroSucre();
        }
    }
}







// variable globale permettant de creer des noms de fichiers differents
int compteurFichier = 0;
// action dessinant un damier
void dessinerGrille(Grille &g){
    int red,green,blue;
    ostringstream filename;
    // creation d'un nouveau nom de fichier de la forme img347.ppm
    filename << "proj" << setfill('0') << setw(3) << compteurFichier << ".ppm";
    compteurFichier++;
    cout << "Ecriture dans le fichier : " << filename.str() << endl;
    
    // ouverture du fichier
    ofstream fic(filename.str(), ios::out | ios::trunc);
    // ecriture de l'entete
    fic << "P3" << endl
    << TAILLEGRILLE << " " << TAILLEGRILLE << " " << endl
    << 255 << " " << endl<<endl;
    // ecriture des pixels
    for (size_t i = 0; i < g.rail.size();i++){
        // calcul de la couleur
        if(i%(TAILLEGRILLE+1)==0){fic << endl<< endl;}
        else{
        red = g.rail[i].r ; 
        green = g.rail[i].g; 
        blue = g.rail[i].b;
        fic << red << " " << green << " " << blue << "  ";
        }
    }
        // fin de ligne dans l'image
    fic.close();
}
        
        