#include "Octopusgrid.h"

#include <string>
#include <vector>
#include <sstream>

using namespace std; 

Octopusgrid::Octopusgrid() : nrow(1), ncol(1), grid({{0}}) {}; 

Octopusgrid::Octopusgrid(string completegrid) {
    stringstream inputss(completegrid); 
    string row; 
    while (inputss.good()) { 
        vector<int> rowVect; 
        getline(inputss, row); 
        int n = row.length(); 
        if (n > 0) {
            for (int i = 0; i < n ; i++) { 
                rowVect.push_back(row[i] - '0'); 
            }
            grid.push_back(rowVect); 
        } 
    }
    ncol = grid[0].size(); 
    nrow = grid.size(); 
}

// Getters and setters 

int Octopusgrid::getNrow() { 
    return nrow; 
}

int Octopusgrid::getNcol() { 
    return ncol; 
}

int Octopusgrid::getEnergyLevelAtPoint(int i, int j) { 
    return grid[i][j]; 
}

void Octopusgrid::setEnergyLevelAtPoint(int i, int j, int energylevel) { 
    grid[i][j] = energylevel; 
}

// Other methods 

int Octopusgrid::getFlashesNbForOneStep() { 
    int nbFlash = 0; 
    vector<vector<int>> stackOfPoints; 
    vector<bool> rowHF(ncol, false); 
    vector<vector<bool>> hasFlashed(nrow, rowHF); 
    
    for (int i0 = 0; i0 < nrow; i0++) { 
        for (int j0 = 0; j0 < ncol; j0++) { 
            setEnergyLevelAtPoint(i0,j0,getEnergyLevelAtPoint(i0,j0)+1); 
            if (getEnergyLevelAtPoint(i0,j0) > 9) { 
                stackOfPoints.push_back({i0, j0}); 
                hasFlashed[i0][j0] = true; 
                setEnergyLevelAtPoint(i0,j0,0); 
            }
        }
    }

    while (stackOfPoints.size() > 0) { 
        int i = stackOfPoints.back()[0]; 
        int j = stackOfPoints.back()[1]; 
        stackOfPoints.pop_back(); 
        nbFlash++;

        for (int indi = i-1; indi < i+2 ; indi++) { 
            for (int indj = j-1; indj < j+2; indj++) { 
                bool condi = (indi < nrow && indi >= 0); 
                bool condj = (indj < nrow && indj >= 0); 
                bool condBothNull = (indi == i && indj == j); 
                if (condi && condj && !hasFlashed[indi][indj] && !condBothNull) { 
                    setEnergyLevelAtPoint(indi, indj, getEnergyLevelAtPoint(indi, indj)+1); 
                    if (getEnergyLevelAtPoint(indi,indj) > 9) {
                        stackOfPoints.push_back({indi, indj}); 
                        hasFlashed[indi][indj] = true; 
                        setEnergyLevelAtPoint(indi, indj, 0); 
                    }
                }
            }
        }
    }
    
    return nbFlash; 
}