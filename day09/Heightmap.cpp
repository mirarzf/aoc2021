#include "Heightmap.h"

#include <string>
#include <vector>
#include <sstream>

using namespace std; 

// Constructors 

Heightmap::Heightmap() : map({{0}}) {}; 

Heightmap::Heightmap(string input) { 
    stringstream inputss(input); 
    string line; 
    while (inputss.good()) { 
        getline(inputss, line, '\n'); 
        int n = line.length(); 
        if (n > 0) { 
            vector<int> row; 
            for (int i = 0; i < n ; i++) { 
                row.push_back(line[i] - '0'); 
            }
            map.push_back(row); 
        } 
    }
}

// Getters and Setters 

int Heightmap::getHeightIn(int i, int j) { 
    return map[i][j]; 
}

int Heightmap::getNbRow() { 
    return map.size(); 
}

int Heightmap::getNbCol() { 
    if (getNbRow() > 0) { 
        return map[0].size(); 
    } else { 
        return 0; 
    }
}

// Other methods 

vector<vector<int>> Heightmap::getLowPoints() { 
    vector<vector<int>> lowPoints; 
    int nrow = getNbRow(); 
    int ncol = getNbCol(); 
    for (int i = 0; i < nrow ; i++) { 
        for (int j = 0; j < ncol ; j++) { 
            bool north, east, south, west; 

            // North condition 
            if ((i > 0 && getHeightIn(i-1, j) > getHeightIn(i,j)) || i == 0) { 
                north = true; 
            } else { 
                north = false; 
            }

            // East condition 
            if ((j < ncol-1 && getHeightIn(i, j+1) > getHeightIn(i,j)) || j >= ncol-1) { 
                east = true; 
            } else { 
                east = false; 
            } 

            // South condition 
            if ((i < nrow-1 && getHeightIn(i+1, j) > getHeightIn(i,j)) || i >= nrow-1) { 
                south = true; 
            } else { 
                south = false; 
            }

            // West condition 
            if ((j > 0 && getHeightIn(i, j-1) > getHeightIn(i,j)) || j == 0) { 
                west = true; 
            } else { 
                west = false; 
            }

            if (north && east && south && west) { 
                vector<int> pushLowPoint = {i, j}; 
                lowPoints.push_back(pushLowPoint); 
            }
        }
    }
    return lowPoints; 
}

int Heightmap::getSumRiskLevel() { 
    vector<vector<int>> lowPoints = getLowPoints(); 
    int n = lowPoints.size(); 
    int sum = 0; 
    for (int i = 0; i < n ; i++) { 
        sum += 1+getHeightIn(lowPoints[i][0], lowPoints[i][1]); 
    }
    return sum; 
}

int Heightmap::getBasinSizeAroundLowPoint(int x, int y) { 
    int nrow = getNbRow(); 
    int ncol = getNbCol(); 
    int basinSize = 0; 
    vector<vector<bool>> inTheBasin; 
    for (int i = 0 ; i < nrow ; i++) { 
        vector<bool> itbRow(ncol, false); 
        inTheBasin.push_back(itbRow); 
    }
    inTheBasin[x][y] = true; 

    vector<vector<int>> basinPoints = {{x,y}}; 
    int i0, j0; 

    while (basinPoints.size() > 0) { 
        vector<int> lastAddedBasinPoint = basinPoints.back(); 
        i0 = lastAddedBasinPoint[0]; 
        j0 = lastAddedBasinPoint[1]; 
        basinPoints.pop_back(); 
        basinSize++; 
        if (i0-1 >= 0 && map[i0-1][j0] != 9) {
            if (!inTheBasin[i0-1][j0]) { 
                inTheBasin[i0-1][j0] = true; 
                basinPoints.push_back({i0-1,j0}); 
            }
        }
        if (i0+1 < nrow && map[i0+1][j0] != 9) { 
            if (!inTheBasin[i0+1][j0]) { 
                inTheBasin[i0+1][j0] = true; 
                basinPoints.push_back({i0+1,j0}); 
            }
        }
        if (j0-1 >= 0 && map[i0][j0-1] != 9) { 
            if (!inTheBasin[i0][j0-1]) { 
                inTheBasin[i0][j0-1] = true; 
                basinPoints.push_back({i0,j0-1}); 
            }
        }
        if (j0+1 < ncol && map[i0][j0+1] != 9) { 
            if (!inTheBasin[i0][j0+1]) { 
                inTheBasin[i0][j0+1] = true; 
                basinPoints.push_back({i0,j0+1}); 
            }
        }
    }

    return basinSize; 
}