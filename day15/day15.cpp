#include <iostream> 
#include <fstream> 
#include <sstream>
#include <string>
#include <vector> 
#include <cmath> 

#include "Graphe.h"

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

    Graphe risks = Graphe(inputss.str(), puzzlepart); 

    return risks.Dijkstra(); 
} 

int main() { 
    /* Instantiation of the file */ 
    string myfilename; 
    cout << "Filename of the input: "; 
    cin >> myfilename; 

    // Solution to puzzle 1: 537
    cout << "The solution to part one is : " << puzzle(myfilename, 1) << "\n"; 
    // Solution to puzzle 2: 2881
    cout << "The solution to part two is : " << puzzle(myfilename, 2) << "\n"; 
    return 0; 
}