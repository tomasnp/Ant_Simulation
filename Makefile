CXX=g++
CXXFLAGS= -Wall -std=c++11 -g -O3
EXEC_FILES= main

all: main

# fichier executable
main : coord.o fourmi.o grille.o main.o 
	$(CXX) $(CXXFLAGS) -o main coord.o fourmi.o grille.o main.o 

# fichiers objets
main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c main.cpp 
coord.o: coord.cpp coord.hpp 
	$(CXX) $(CXXFLAGS) -c coord.cpp coord.hpp 
fourmi.o: fourmi.cpp fourmi.hpp 
	$(CXX) $(CXXFLAGS) -c fourmi.cpp fourmi.hpp
grille.o: grille.cpp grille.hpp 
	$(CXX) $(CXXFLAGS) -c grille.cpp grille.hpp
tests.o: tests.cpp 
	$(CXX) $(CXXFLAGS) -c tests.cpp


clean:
	rm -f *.o $(EXEC_FILES)