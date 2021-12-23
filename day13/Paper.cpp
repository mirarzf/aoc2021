#include "Paper.h"

#include <vector>
#include <string> 
#include <sstream> 
#include <iostream>

using namespace std; 

// Constructors 
Paper::Paper() : visibleDots({{0,0}}), limitx(0), limity(0), instructAxis({}), instructLineNb({}) {}; 

Paper::Paper(string line) { 
    limitx = 0; 
    limity = 0; 

    stringstream inputss(line); 
    string dotCoord; 
    getline(inputss, dotCoord, '\n'); 
    do { 
        stringstream coordinates(dotCoord); 
        string x; 
        string y; 
        getline(coordinates, x, ','); 
        getline(coordinates, y, ','); 
        visibleDots.push_back({stoi(x), stoi(y)}); 
        if (visibleDots.back()[0] > limitx) { 
            limitx = visibleDots.back()[0]; 
        }
        if (visibleDots.back()[1] > limity) { 
            limity = visibleDots.back()[1]; 
        }
        getline(inputss, dotCoord, '\n'); 
    } 
    while (inputss.good() && dotCoord != ""); 
    limitx++; 
    limity++; 

    string foldInstructions; 
    getline(inputss, foldInstructions, '\n'); 
    while (inputss.good() && foldInstructions != "") { 
        stringstream instruction(foldInstructions); 
        string axis; 
        string number; 
        getline(instruction, axis, '='); 
        getline(instruction, number, '='); 
        instructAxis.push_back(axis.back()); 
        instructLineNb.push_back(stoi(number)); 
        getline(inputss, foldInstructions, '\n'); 
    }
}

// Getters and setters 
int Paper::getLimitX() { 
    return limitx; 
}

int Paper::getLimitY() { 
    return limity; 
}

void Paper::setLimitX(int x) { 
    limitx = x; 
}

void Paper::setLimitY(int y) { 
    limity = y; 
}

// Other methods 
void Paper::applyInstruction(char axis, int linenb) { 
    if (axis == 'x') { 
        setLimitX(linenb); 
    }
    else if (axis == 'y') { 
        setLimitY(linenb); 
    }

    int xlim = getLimitX(); 
    int ylim = getLimitY(); 
    int nvdots = visibleDots.size(); 

    for (int i = 0; i < nvdots; i++) { 
        int x = visibleDots[i][0]; 
        int y = visibleDots[i][1]; 

        int distx = x-xlim; 
        int disty = y-ylim; 

        if (axis == 'x' && distx > 0 && xlim-distx >= 0) { 
            visibleDots[i][0] = xlim-distx; 
        }

        if (axis == 'y' && disty > 0 && ylim-disty >= 0) { 
            visibleDots[i][1] = ylim-disty; 
        }
    }
}

int Paper::getNbOfVisibleDots(int puzzlepart) { 
    // We apply all instructions 
    if (puzzlepart == 1) { 
        applyInstruction(instructAxis[0], instructLineNb[0]); 

    } else {
        int ninstr = instructAxis.size(); 
        for (int i = 0; i < ninstr; i++) {
            applyInstruction(instructAxis[i], instructLineNb[i]); 
        }
    }

    int countVisible = 0; 
    int xlim = getLimitX(); 
    int ylim = getLimitY(); 

    // Creation of the array of dots 
    vector<vector<bool>> arrayOfDots(ylim, vector<bool>(xlim, false)); 

    int nvdots = visibleDots.size(); 
    for (int i = 0; i < nvdots; i++) { 
        if (visibleDots[i][0] < xlim && visibleDots[i][1] < ylim) { 
            int x = visibleDots[i][0]; 
            int y = visibleDots[i][1]; 
            if (!arrayOfDots[y][x]) { 
                countVisible++; 
                arrayOfDots[y][x] = true; 
            }
        }
    }
    if (puzzlepart == 2) {
        cout << "\n"; 
        for (int y = 0; y < ylim; y++) { 
            for (int x = 0; x < xlim; x++) { 
                if (arrayOfDots[y][x]) { 
                    cout << "#"; 
                } else { 
                    cout << "."; 
                }
            }
            cout << "\n"; 
        }
    } 

    return countVisible; 

}