#include <iostream>     // pour cout
#include <iomanip>      // pour setfill, setw
#include <sstream>      // pour ostringstream
#include <fstream>      // pour ofstream
#include <string>
#include "grille.hpp"


#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

using namespace std;

TEST_SUITE_BEGIN("Struct");


TEST_CASE("Coord") {
    Coord c1(1,2);
    Coord c2(2,3);
    Coord c3(1,2);
    CHECK_FALSE(c1 == c2);
    CHECK(c1 == c3);
    CHECK(c1 != c2);
    CHECK(c1 != c2);
    CHECK_THROWS_AS((Coord{TAILLEGRILLE+2,10}),string);
    CHECK(c1.get_lig() == 1);
    CHECK(c2.get_lig() == 2);
    
}

TEST_CASE("EnsCoord") {
    Coord c1(1,2);
    Coord c2(2,3);
    Coord c3(1,3);
    EnsCoord E1 {{c1,c2}};

    CHECK(E1.contient(c2));
    CHECK_FALSE(E1.estVide());
    E1.ajoute(c3);
    E1.supprime(c2);
    CHECK_THROWS_AS((E1.supprime(c2)),string);
    CHECK(E1.taille() == 2);
    CHECK(E1.ieme(0) == c1);  
    
}

TEST_CASE("Fourmi") {
    Coord c1{1,2};
    Coord c2{2,3};
    Coord c3{1,3};
    EnsCoord E1 {{c1,c2,c3}};
    Fourmi f1(c1,E1);
    Fourmi f2{c2,E1};
    Fourmi f3{c3,E1};
    f2.prendSucre();
    CHECK(f1.coord() == Coord{1,2});
    CHECK(f2.num() == 1);
    CHECK(f2.porteSucre() == true);
    //f3.deplace({0,1});
    //CHECK(f3.coord() == Coord(0,1));
}

TEST_CASE("Place") {
    Coord c0{0,0};
    Coord c1{3,5};
    Coord c2{6,1};
    Coord c3{9,8};
    EnsCoord E1 {{c0,c1,c2,c3}};
    
    Place p0(c0);
    Place p1(c1);
    Place p2(c2);
    Place p3(c3);
    
    Fourmi f1(c0,E1);
    Fourmi f2(c2,E1);
    
    f1.prendSucre();
    p0.poseFourmi(f1);
    /*
    
    CHECK(p0.coord() == {0,0});
    CHECK(p1.pheroSucre() == 255);
    CHECK(p4.numeroFourmi == p4.ant);
    CHECK(p5.estSurUnePiste());
    p2.poseFourmi(f1);
    CHECK(p2.numeroFourmi == f1.ind);
    p1.diminuePheroSucre()
    CHECK(p1.pheroSucre() == 250);
    CHECK(deplaceFourmi(f1,c1,c2));*/
}

TEST_CASE("linearisePheroNid"){
    Grille g;
    Coord c(1, 2);
    //Place p = g.chargePlace(c);
    //g.rangePlace(p);

}


TEST_CASE("constructeur"){
    Coord coord1 = {5, 4};
    
    CHECK(coord1.col == 4);
    CHECK_FALSE(coord1.col == 0);
    
    CHECK(coord1.lig == 5);
    CHECK_FALSE(coord1.lig == 3);
}



//Grands tests de la classe Coord 

TEST_CASE("classe Coord"){
    Coord c = {2, 5};
    Coord d = {5, 2};
    Coord c2 = {2, 5};
    Coord e = {0,0};
    Coord f = {2,2};
    
    CHECK(c!=d);
    CHECK(c == c2);
    CHECK_FALSE(c2 != c);
    CHECK_FALSE(e == f);
    CHECK(f != d);
    
}


//Test de la méthode postiton 
    
TEST_CASE("méthode position"){
    
    Coord co = {1, 2};
    Coord c = {0, 0};
    Coord ci = {2, 2};
    Coord cno = {4, 4};
    
    vector<Coord> vect = {co,c,ci};
     
    EnsCoord e;
    e.tab = vect;
    
    CHECK(e.position(co) == 0);
    CHECK(e.position(c) == 1);
    CHECK(e.position(cno) == -1);   
}

//Test de la méthode contient

TEST_CASE("méthode contient"){
    
    Coord co = {1, 2};
    Coord c = {0, 0};
    Coord ci = {2, 2};
    Coord cno = {4, 4};
    
    vector<Coord> vect = {co,c,ci};
     
    EnsCoord e;
    e.tab = vect;
    
    CHECK(e.contient(co) == true);
    CHECK_FALSE(e.contient(c) == false);
    CHECK(e.contient(cno) == false);
    
}

//Test de la méthode ajoute

TEST_CASE("méthode ajoute"){
    
    Coord co = {1, 2};
    Coord c = {0, 0};
    Coord ci = {2, 2};
    Coord cno = {4, 4};
    
    vector<Coord> vect = {co,c,ci};
     
    EnsCoord e;
    e.tab = vect;
    
    CHECK(e.contient(cno) == false);
    CHECK(e.tab.size() == 3);
    
    e.ajoute(cno);
    
    CHECK(e.contient(cno) == true);
    CHECK(e.tab.size() == 4);
    
}

//Test de la méthode supprime

TEST_CASE("méthode supprime"){
    
    Coord co = {1, 2};
    Coord c = {0, 0};
    Coord ci = {2, 2};
    Coord cno = {4, 4};
    
    vector<Coord> vect = {co,c,ci,cno};
     
    EnsCoord e;
    e.tab = vect;
    
    CHECK(e.contient(c) == true);
    CHECK(e.tab.size() == 4);
    
    e.supprime(c);
    
    CHECK(e.contient(c) == false);
    CHECK(e.tab.size() == 3);
    
    CHECK(e.contient(cno) == true);
    
    e.supprime(cno);
    
    CHECK(e.contient(cno) == false);
    CHECK(e.tab.size() == 2);
    
}

//Test de la méthode estVide

TEST_CASE("méthode estVide"){
    
    Coord co = {1, 2};
    vector<Coord> vect = {co};
     
    EnsCoord e;
    e.tab = vect;
    
    CHECK_FALSE(e.estVide() == true);
    
    e.supprime(co);
    
    CHECK(e.estVide() == true);
    
}

//Test de la méthode taille

TEST_CASE("méthode taille"){
    
    Coord co = {1, 2};
    Coord c = {0, 0};
    Coord ci = {2, 2};
    Coord cno = {4, 4};
    
    vector<Coord> vect = {co,c,ci,cno};
     
    EnsCoord e;
    e.tab = vect;
    
    CHECK(e.taille() == 4);
    
    e.supprime(c);
    
    CHECK(e.taille() == 3);
  
    e.ajoute(c);
    
    CHECK(e.taille() == 4);
    
}

//Test de la méthode ieme

TEST_CASE("méthode ieme"){
    
    Coord co = {1, 2};
    Coord c = {0, 0};
    Coord ci = {2, 2};
    Coord cno = {4, 4};
    
    vector<Coord> vect = {co,c,ci,cno};
     
    EnsCoord e;
    e.tab = vect;
    
    CHECK(e.ieme(2) == ci);
    CHECK(e.ieme(0) == co);
    CHECK(e.ieme(3) == cno);
    
}



/*
//Test de la fonction voisines

TEST_CASE("la fonction voisines"){
    
    Coord c(3,4);
    
    Coord t1(2,3);
    Coord t2(2,4);
    Coord t4(3,3);
    Coord t5(3,5);
    
    
    EnsCoord e;
    e.tab = voisines(c);
    
    CHECK(e.taille() == 8);
    CHECK(e.tab[0]==t1);
    CHECK(e.tab[1]==t2);
    CHECK(e.tab[3]==t4);
    CHECK(e.tab[4]==t5);
    
    Coord d(2,1);
    
    Coord u1(1,0);
    Coord u2(1,1);
    Coord u3(1,2);
    Coord u4(2,0);
    Coord u5(2,2);
    Coord u6(3,0);
    Coord u7(3,1);
    Coord u8(3,2);
    
    
    EnsCoord f;
    f.tab = voisines(d);
    
    CHECK(f.taille() == 8);
    CHECK(f.tab[0]==u1);
    CHECK(f.tab[1]==u2);
    CHECK(f.tab[2]==u3);
    CHECK(f.tab[3]==u4);
    CHECK(f.tab[4]==u5);
    CHECK(f.tab[5]==u6);
    CHECK(f.tab[6]==u7);
    CHECK(f.tab[7]==u8);
    
    Coord k(0,0);
    
    Coord r1(0,1);
    Coord r2(1,0);
    Coord r3(1,1);
    
    
    EnsCoord z;
    z.tab = voisines(k);
    
    CHECK(z.taille() == 3);
    CHECK(z.tab[0]==r1);
    CHECK(z.tab[1]==r2);
    CHECK(z.tab[2]==r3);
    
    
    Coord u(4,4);
    
    Coord q1(3,3);
    Coord q2(3,4);
    
    
    EnsCoord p(voisines(u));
    
    CHECK(p.taille() == 8);
    CHECK(p.tab[0]==q1);
    CHECK(p.tab[1]==q2);

}
    */

TEST_SUITE_END();

int main(int argc, const char** argv){
    doctest::Context context(argc, argv);
    int test_result = context.run();
    if (context.shouldExit()) return test_result;
    srand(time(NULL));
    EnsCoord all({});
    Grille g;
    
    EnsCoord Fourm1{{Coord(8,8),Coord(8,9),Coord(8,10),Coord(8,11),Coord(9,8),Coord(10,8),Coord(11,8),Coord(11,9),Coord(11,10),Coord(11,11),Coord(10,11),Coord(9,11)}};
    
    EnsCoord Fourm2{{Coord(28,28),Coord(28,29),Coord(28,30),Coord(28,31),Coord(29,28),Coord(30,28),Coord(31,28),Coord(31,29),Coord(31,30),Coord(31,31),Coord(30,31),Coord(29,31)}};
    EnsCoord Fourm3{{Coord(2,34),Coord(2,35),Coord(2,36),Coord(3,37),Coord(4,34),Coord(5,34),Coord(5,34),Coord(5,35),Coord(5,36),Coord(5,37),Coord(4,37),Coord(3,37)}};
    
    EnsCoord leNid1{{Coord(9,9),Coord(9,10),Coord(10,9),Coord(10,10)}};
    EnsCoord leNid2{{Coord(29,29),Coord(29,30),Coord(30,29),Coord(30,30)}};
    EnsCoord leNid3{{Coord(3,35),Coord(3,36),Coord(4,35),Coord(4,36)}};
    
    Colonie Col1(Fourm1,leNid1, 1,'g');
    Colonie Col2(Fourm2,leNid2, 2,'b');
    Colonie Col3(Fourm3,leNid3, 3,'r');
    
    vector<Colonie> lesColonies = {Col1,Col2, Col3};
    
    EnsCoord leSucre{{Coord(10,20),Coord(16,32),Coord(35,20),Coord(30,22),Coord(37,29),Coord(30,35),Coord(5,29),Coord(19,1),Coord(15,10), Coord(3,6),Coord(36,13),Coord(20,20)}};
    
    
    creerPlacesGrille(all,g);
    initialiserEmplacements(lesColonies,leSucre,all,g);
    
    for(int i = 0; i <500; i++){
        mettreAJourEnsColonie(g,lesColonies);
        dessinerGrille(g);
        majPheroSucre(g);
        /*for (size_t i = 0; i < g.rail.size();i++){
            if( i% (TAILLEGRILLE+1)==0){
                cout<<endl;
            }
            cout <<setw(4)<< g.rail[i].pheroSucre()<<setfill('.')<< " " ;
        
        }*/
        //cout<<endl;
    }
    cout<<endl;
    /*
    cout << "2 : " << deux<< endl;
    cout << "3 : " << trois<<endl;
    cout << "4 : " << quatre<<endl;
    cout << "5 : " << cinq << endl;
    cout << "6 : " << six<< endl;
    cout << "7 : " << sept<<endl;
    */

    
    //convert -scale 300 -delay 10 proj*.ppm anim.gif
    return 0;
}













