#include <iostream> 
#include <fstream> 
#include <sstream>
#include <string>
#include <vector> 
#include <cmath> 

#include "Octopusgrid.h"

using namespace std; 

int puzzle(string filename, int puzzlepart) { 
    ifstream file; 
    file.open(filename); 

    string line; 
    stringstream inputss; 
    while (file.good()) { 
        getline(file, line);
        inputss << line; 
        inputss << "\n"; 
    } 
    file.close(); 

    Octopusgrid og = Octopusgrid(inputss.str()); 
    
    if (puzzlepart == 1) {
        int totalNbFlashes = 0; 
        for (int stepcount = 0; stepcount < 100; stepcount++) { 
            totalNbFlashes += og.getFlashesNbForOneStep(); 
        }
        return totalNbFlashes; 
    } else { 
        int stepcount = 1; 
        int nbFlashesToMatch = og.getNcol()*og.getNrow(); 
        while (og.getFlashesNbForOneStep() != nbFlashesToMatch) { 
            stepcount++; 
        }
        return stepcount; 
    }

    return 0; 
} 

int main() { 
    /* Instantiation of the file */ 
    string myfilename; 
    cout << "Filename of the input: "; 
    cin >> myfilename; 

    // Solution to puzzle 1: 1691
    cout << "The solution to part one is : " << puzzle(myfilename, 1) << "\n"; 
    // Solution to puzzle 2: 
    cout << "The solution to part two is : " << puzzle(myfilename, 2) << "\n"; 
    return 0; 
}