#include <iostream> 
#include <fstream> 
#include <sstream>
#include <string>

#include "Heightmap.h"

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
    Heightmap hmap = Heightmap(inputss.str()); 

    if (puzzlepart == 1) { 
        return hmap.getSumRiskLevel(); 
    } else { 
        vector<vector<int>> lowPoints = hmap.getLowPoints(); 
        vector<int> basinSizes; 
        int n = lowPoints.size(); 
        int max1 = 0; 
        int max2 = 0; 
        int max3 = 0; 
        for (int i = 0 ; i < n; i++) { 
            int basinSize = hmap.getBasinSizeAroundLowPoint(lowPoints[i][0], lowPoints[i][1]); 
            if (max1 < basinSize) { 
                max3 = max2; 
                max2 = max1; 
                max1 = basinSize; 
            } else if (max1 >= basinSize && max2 < basinSize) { 
                max3 = max2; 
                max2 = basinSize; 
            } else if (max2 >= basinSize && max3 < basinSize) {
                max3 = basinSize; 
            }
        }
        return max1*max2*max3; 
    }
} 

int main() { 
    /* Instantiation of the file */ 
    string myfilename; 
    cout << "Filename of the input: "; 
    cin >> myfilename; 

    // Solution to puzzle 1: 554
    cout << "The solution to part one is " << puzzle(myfilename, 1) << ". \n"; 
    // Solution to puzzle 2: 1017792
    cout << "The solution to part two is " << puzzle(myfilename, 2) << ". \n"; 
    return 0; 
}