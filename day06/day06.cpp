#include <iostream> 
#include <fstream> 
#include <string>
#include <cmath> 
#include <vector>

#include "School.h"

using namespace std; 

unsigned long long int puzzle(string filename, int nbOfDays) { 
    ifstream file; 
    file.open(filename); 

    string line; 
    getline(file, line); 
    School lfSchool = School(line, 7, 2); 

    file.close(); 

    for (int i = 0 ; i < nbOfDays; i++) { 
        lfSchool.growOneDay(); 
    }
    return lfSchool.getNbPopulation(); 
}

int main() { 
    /* Instantiation of the file */ 
    string myfilename; 
    cout << "Filename of the input: "; 
    cin >> myfilename; 

    // Solution to puzzle 1: 379414
    cout << "The solution to part one is " << puzzle(myfilename, 80) << ". \n"; 
    // Solution to puzzle 2: 1705008653296
    cout << "The solution to part two is " << puzzle(myfilename, 256) << ". \n"; 
    return 0; 
}