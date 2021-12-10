#include <iostream> 
#include <fstream> 
#include <sstream>  
#include <string>
#include <cmath> 
#include <vector>

#include "Connections.h"

using namespace std; 


int puzzle1(string filename) { 
    ifstream file; 
    file.open(filename); 

    int counterUniqueSegments = 0; 

    string line; 
    while (file.good()) { 
        getline(file, line); 
        stringstream ss(line); 
        while(ss.good()) { 
            string part2; 
            getline(ss, part2, '|'); 
            getline(ss, part2, '|'); 
            stringstream ssoutput(part2); 
            while (ssoutput.good()) { 
                string output; 
                getline(ssoutput, output, ' '); 
                int ol = output.length(); 
                if ( ol == 2 || ol == 4 || ol == 3 || ol == 7 ) { 
                    counterUniqueSegments++; 
                }
            }
        } 
    } 
    file.close(); 
    return counterUniqueSegments; 
}

int puzzle2(string filename) { 
    ifstream file; 
    file.open(filename); 

    int sum = 0; 
    string line; 
    while (file.good()) { 
        getline(file, line); 
        Connections input = Connections(line); 
        sum += input.getDisplayAsInt(); 
    } 
    file.close(); 
    return sum; 
} 

int main() { 
    /* Instantiation of the file */ 
    string myfilename; 
    cout << "Filename of the input: "; 
    cin >> myfilename; 

    // Solution to puzzle 1: 284
    cout << "The solution to part one is " << puzzle1(myfilename) << ". \n"; 
    // Solution to puzzle 2: 973499
    cout << "The solution to part two is " << puzzle2(myfilename) << ". \n"; 
    return 0; 
}