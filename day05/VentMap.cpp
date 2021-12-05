#include "VentMap.h"
using namespace std; 

// Constructors 

VentMap::VentMap() : xlength(1), ylength(1), map({{0}}) {}; 

VentMap::VentMap(vector<Coord> listCoord) { 
    int maxX = 0, maxY = 0; 
    int n = listCoord.size(); 
    for (int i = 0 ; i < n ; i++) { 
        if (listCoord[i].getX() > maxX) { 
            maxX = listCoord[i].getX(); 
        }
        if (listCoord[i].getY() > maxY) { 
            maxY = listCoord[i].getY(); 
        }
    }
    xlength = maxX+1; 
    ylength = maxY+1; 
    for (int i = 0 ; i < maxX+1 ; i++) { 
        vector<int> row; 
        for (int j = 0 ; j < maxY+1 ; j++) { 
            row.push_back(0);
        }
        map.push_back(row); 
    }
}

// Getters and Setters 
int VentMap::getXLength() { 
    return xlength; 
}

int VentMap::getYLength() { 
    return ylength; 
}

int VentMap::getNbOfDangerZone() { 
    int sum = 0; 
    for (int i = 0 ; i < xlength ; i++) { 
        for (int j = 0 ; j < ylength ; j++) { 
            if (map[i][j] > 1) { 
                sum++; 
            } 
        }
    }
    return sum; 
}

void VentMap::addVentToMap(Hvent hydrovent, int puzzlepart) { 
    vector<Coord> vecteur = hydrovent.getPointsBetween(puzzlepart); 
    if (vecteur.size() > 0) {
        int n = vecteur.size(); 
        for (int i = 0; i < n ; i++) { 
            int x = vecteur[i].getX(); 
            int y = vecteur[i].getY(); 
            map[x][y]++; 
        }
    } 
}

// Other methods 