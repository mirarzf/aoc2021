#include <iostream> 
#include <fstream> 
#include <string>
#include <cmath> 
#include <vector>

#include "Coord.h"
#include "Hvent.h" 
#include "VentMap.h"

using namespace std; 

int puzzle(string filename, int puzzlepart) { 
    ifstream file; 
    file.open(filename); 

    // Read the coordinates of the hydrothermal vents and keep them in a vector of Hvents  
    vector<Hvent> hventVector; 
    vector<Coord> coordVector; 
    while (file.good()) { 
        string line; 
        getline(file, line); 
        Hvent newHvent = Hvent(line); 
        hventVector.push_back(newHvent); 
        Coord newBeginCoord = Coord(newHvent.getBeginX(), newHvent.getBeginY()); 
        coordVector.push_back(newBeginCoord); 
        Coord newFinalCoord = Coord(newHvent.getFinalX(), newHvent.getFinalX()); 
        coordVector.push_back(newFinalCoord); 
    }

    file.close(); 

    VentMap mapofv = VentMap(coordVector); 
    int n = hventVector.size(); 
    for (int i = 0 ; i < n ; i++) {
        // cout << hventVector[i].getBeginX() << "," << hventVector[i].getBeginY() << "\n"; 
        // cout << hventVector[i].getFinalX() << "," << hventVector[i].getFinalY() << "\n"; 
        mapofv.addVentToMap(hventVector[i], puzzlepart); 
    }

    // cout << "ceci est un test : " << mapofv.getNbOfDangerZone() << "\n"; 

    return mapofv.getNbOfDangerZone(); 
}

int main() { 
    /* Instantiation of the file */ 
    string myfilename; 
    cout << "Filename of the input: "; 
    cin >> myfilename; 

    // Solution to puzzle 1: 5835
    cout << "The solution to part one is " << puzzle(myfilename, 1) << ". \n"; 
    // Solution to puzzle 2: 17013 
    cout << "The solution to part two is " << puzzle(myfilename, 2) << ". \n"; 
    return 0; 
}