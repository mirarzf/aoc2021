#include <iostream> 
#include <fstream> 
#include <sstream>
#include <string>

#include "LineOfChunk.h"

using namespace std; 


vector<unsigned long long int> fusionVectors(vector<unsigned long long int> vectorA, vector<unsigned long long int> vectorB) { 
    int nA = vectorA.size(); 
    int nB = vectorB.size(); 
    if (nA == 0) {
        return vectorB; 
    }
    if (nB == 0) { 
        return vectorA; 
    } 

    vector<unsigned long long int> fusedVect; 
    if (vectorA[0] < vectorB[0]) { 
        fusedVect.push_back(vectorA[0]); 
        vector<unsigned long long int> leftOfA; 
        for (int i = 1; i < nA; i++) { 
            leftOfA.push_back(vectorA[i]); 
        }
        vector<unsigned long long int> toBeFused = fusionVectors(leftOfA, vectorB); 
        for (int j = 0; j < nA + nB - 1; j++) { 
            fusedVect.push_back(toBeFused[j]); 
        }
        return fusedVect; 
    } else { 
        fusedVect.push_back(vectorB[0]); 
        vector<unsigned long long int> leftOfB; 
        for (int i = 1; i < nB; i++) { 
            leftOfB.push_back(vectorB[i]); 
        }
        vector<unsigned long long int> toBeFused = fusionVectors(leftOfB, vectorA); 
        for (int j = 0; j < nA + nB - 1; j++) { 
            fusedVect.push_back(toBeFused[j]); 
        }
        return fusedVect; 
    }
}

vector<unsigned long long int> sortVector(vector<unsigned long long int> toBeSorted) { 
    int n = toBeSorted.size(); 
    if (n == 1) { 
        return toBeSorted; 
    } else { 
        vector<unsigned long long int> vectorA; 
        vector<unsigned long long int> vectorB; 
        for (int i = 0 ; i < n/2 ; i++ ) { 
            vectorA.push_back(toBeSorted[i]); 
        }
        for (int i = n/2 ; i < n; i++) { 
            vectorB.push_back(toBeSorted[i]); 
        }
        return fusionVectors(sortVector(vectorA), sortVector(vectorB)); 
    }
}

int puzzle1(string filename) { 
    ifstream file; 
    file.open(filename); 

    int sumScore = 0; 

    string line; 
    while (file.good()) { 
        getline(file, line);
        LineOfChunk linechunk = LineOfChunk(line); 
        sumScore += linechunk.getErrorScore(); 
    } 
    file.close(); 

    return sumScore; 
} 

unsigned long long int puzzle2(string filename) { 
    ifstream file; 
    file.open(filename); 

    vector<unsigned long long int> scores; 

    string line; 
    while (file.good()) { 
        getline(file, line);
        LineOfChunk linechunk = LineOfChunk(line); 
        if (!linechunk.isCorrupted()) {
            scores.push_back(linechunk.getCompletionScore()); 
        } 
    } 
    file.close(); 
    int n = scores.size();

    return sortVector(scores)[n/2]; 
} 

int main() { 
    /* Instantiation of the file */ 
    string myfilename; 
    cout << "Filename of the input: "; 
    cin >> myfilename; 

    // Solution to puzzle 1: 243939 
    cout << "The solution to part one is : " << puzzle1(myfilename) << "\n"; 
    // Solution to puzzle 2: 2421222841
    cout << "The solution to part two is : " << puzzle2(myfilename) << "\n"; 
    return 0; 
}