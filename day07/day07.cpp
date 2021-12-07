#include <iostream> 
#include <fstream> 
#include <string>
#include <cmath> 
#include <vector>

#include "Armycrab.h"

using namespace std; 

vector<int> fusionVectors(vector<int> vectorA, vector<int> vectorB) { 
    int nA = vectorA.size(); 
    int nB = vectorB.size(); 
    if (nA == 0) {
        return vectorB; 
    }
    if (nB == 0) { 
        return vectorA; 
    } 

    vector<int> fusedVect; 
    if (vectorA[0] < vectorB[0]) { 
        fusedVect.push_back(vectorA[0]); 
        vector<int> leftOfA; 
        for (int i = 1; i < nA; i++) { 
            leftOfA.push_back(vectorA[i]); 
        }
        vector<int> toBeFused = fusionVectors(leftOfA, vectorB); 
        for (int j = 0; j < nA + nB - 1; j++) { 
            fusedVect.push_back(toBeFused[j]); 
        }
        return fusedVect; 
    } else { 
        fusedVect.push_back(vectorB[0]); 
        vector<int> leftOfB; 
        for (int i = 1; i < nB; i++) { 
            leftOfB.push_back(vectorB[i]); 
        }
        vector<int> toBeFused = fusionVectors(leftOfB, vectorA); 
        for (int j = 0; j < nA + nB - 1; j++) { 
            fusedVect.push_back(toBeFused[j]); 
        }
        return fusedVect; 
    }
}

vector<int> sortVector(vector<int> toBeSorted) { 
    int n = toBeSorted.size(); 
    if (n == 1) { 
        return toBeSorted; 
    } else { 
        vector<int> vectorA; 
        vector<int> vectorB; 
        for (int i = 0 ; i < n/2 ; i++ ) { 
            vectorA.push_back(toBeSorted[i]); 
        }
        for (int i = n/2 ; i < n; i++) { 
            vectorB.push_back(toBeSorted[i]); 
        }
        return fusionVectors(sortVector(vectorA), sortVector(vectorB)); 
    }
}

int puzzle(string filename, int puzzlepart) { 
    ifstream file; 
    file.open(filename); 

    string line; 
    getline(file, line); 
    Armycrab crabes = Armycrab(line); 
    file.close(); 

    vector<int> sortedHPos = sortVector(crabes.getHorizontalPositions()); 
    Armycrab sortedCrabes = Armycrab(sortedHPos); 
    
    if (puzzlepart == 1) { 
        int mediane = sortedCrabes.getPositionOfCrabeNb(sortedCrabes.getNbCrabes() / 2); 
        return sortedCrabes.getFuelToGetPosition(mediane); 
    } else { 
        int nbCrabes = sortedCrabes.getNbCrabes(); 
        int min = sortedCrabes.getFuelToGetPositionAdv(0); 
        for (int i = 1; i < nbCrabes; i++) { 
            int fuel = sortedCrabes.getFuelToGetPositionAdv(i);
            if (fuel < min) { 
                min = fuel; 
            } 
        } 
        return min; 
    }
}

int main() { 
    /* Instantiation of the file */ 
    string myfilename; 
    cout << "Filename of the input: "; 
    cin >> myfilename; 

    // Solution to puzzle 1: 328262
    cout << "The solution to part one is " << puzzle(myfilename,1) << ". \n"; 
    // // Solution to puzzle 2: 90040997
    cout << "The solution to part two is " << puzzle(myfilename, 2) << ". \n"; 
    return 0; 
}