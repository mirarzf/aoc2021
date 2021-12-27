#include <iostream> 
#include <fstream> 
#include <string>
#include <map> 

#include "Polymer.h"

using namespace std; 

unsigned long long int puzzle(string filename, int puzzlepart) { 
    ifstream file; 
    file.open(filename); 

    string line; 
    getline(file, line); 
    Polymer poly = Polymer(); 
    poly.setPolymerChain(line); 

    getline(file, line); // to get rid of the blank line 

    while (file.good()) { 
        getline(file, line);
        poly.addRule(line); 
    } 
    file.close(); 

    if (puzzlepart == 1) { 
        for (int i = 0; i < 10; i++) { 
            poly.Polymerize(); 
        }
    } else { 
        for (int i = 0; i < 40; i++) { 
            poly.Polymerize(); 
        }
    }

    return poly.countIterations(); 
} 

int main() { 
    /* Instantiation of the file */ 
    string myfilename; 
    cout << "Filename of the input: "; 
    cin >> myfilename; 

    // Solution to puzzle 1: 2170
    cout << "The solution to part one is : " << puzzle(myfilename, 1) << "\n"; 
    // Solution to puzzle 2: 2422444761283
    cout << "The solution to part two is : " << puzzle(myfilename, 2) << "\n"; 
    return 0; 
}