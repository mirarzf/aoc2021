#include "Hvent.h"
#include <string> 
using namespace std; 


// Constructors 

Hvent::Hvent() : beginX(0), beginY(0), finalX(0), finalY(0) {}

Hvent::Hvent(int x0, int y0, int x1, int y1) { 
    beginX = x0; 
    beginY = y0; 
    finalX = x1; 
    finalY = y1; 
}

Hvent::Hvent(string instr) { 
    int arrayCoord[4] = {0,0,0,0}; 
    int index = 0; 
    int strlength = instr.length(); 
    string temp = ""; 
    for (int i=0 ; i < strlength ; i++) { 
        if (instr[i] == ',' || instr[i] == ' ') { 
            if (temp[0]!='-') { 
                arrayCoord[index] = stoi(temp); 
                index++; 
            } 
            temp = ""; 
        } else { 
            temp += instr[i]; 
        } 
    }
    arrayCoord[index] = stoi(temp); 

    beginX = arrayCoord[0]; 
    beginY = arrayCoord[1]; 
    finalX = arrayCoord[2]; 
    finalY = arrayCoord[3]; 
} 

// Getters and setters 
int Hvent::getBeginX() { 
    return beginX; 
}

int Hvent::getBeginY() { 
    return beginY; 
}

int Hvent::getFinalX() { 
    return finalX; 
}

int Hvent::getFinalY() { 
    return finalY; 
}

void Hvent::setBeginX(int x0) { 
    beginX = x0; 
}

void Hvent::setBeginY(int y0) { 
    beginY = y0; 
}

void Hvent::setFinalX(int x1) { 
    finalX = x1; 
}

void Hvent::setFinalY(int y1) { 
    finalY = y1; 
}

// Other methods 
vector<Coord> Hvent::getPointsBetween(int puzzlepart) { 
    vector<Coord> pointsBetween = {}; 
    if (beginX == finalX && beginY != finalY) { 
        int nPoints = abs(finalY - beginY)+1; 
        for (int i=0;i<nPoints;i++) { 
            if (beginY < finalY) { 
                pointsBetween.push_back(Coord(beginX, beginY+i)); 
            } else { 
                pointsBetween.push_back(Coord(beginX, beginY-i)); 
            }
        }
    } else if (beginY == finalY && beginX != finalX) { 
        int nPoints = abs(finalX - beginX)+1; 
        for (int i=0;i<nPoints;i++) { 
            if (beginX < finalX) { 
                pointsBetween.push_back(Coord(beginX+i, beginY)); 
            } else { 
                pointsBetween.push_back(Coord(beginX-i,beginY)); 
            }
        }
    } else if ( puzzlepart == 2 && abs(finalY - beginY) == abs(finalX - beginX)) { 
        int nPoints = abs(finalX - beginX)+1; 
        for (int i=0 ; i < nPoints ; i++) { 
            int nextX, nextY; 
            if (beginX < finalX) { 
                nextX = beginX+i; 
            } else { 
                nextX = beginX-i; 
            } 
            if (beginY < finalY) { 
                nextY = beginY+i; 
            } else { 
                nextY = beginY-i; 
            }
            pointsBetween.push_back(Coord(nextX, nextY)); 
        }
    } 
    return pointsBetween; 
}
