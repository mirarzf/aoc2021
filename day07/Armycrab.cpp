#include "Armycrab.h"

#include <vector>
#include <string> 
#include <sstream> 

using namespace std; 

Armycrab::Armycrab() : hpos({0}) {}; 

Armycrab::Armycrab(string popInit) { 
    stringstream ss(popInit); 
    string temp = ""; 
    while (ss.good()) { 
        getline(ss, temp, ','); 
        hpos.push_back(stoi(temp)); 
    }
}

Armycrab::Armycrab(vector<int> popInitVect) { 
    int n = popInitVect.size(); 
    for (int i = 0; i < n;i++) { 
        hpos.push_back(popInitVect[i]);
    }  
}

vector<int> Armycrab::getHorizontalPositions() { 
    return hpos; 
}

int Armycrab::getPositionOfCrabeNb(int indCrab) { 
    return hpos.at(indCrab); 
}

int Armycrab::getNbCrabes() {
    return hpos.size(); 
}

int Armycrab::getFuelToGetPosition(int position) { 
    int sum = 0; 
    int n = getNbCrabes(); 
    for (int i = 0; i< n ; i++) { 
        sum += abs(getPositionOfCrabeNb(i) - position); 
    }
    return sum; 
}

int Armycrab::getFuelToGetPositionAdv(int position) { 
    int sum = 0; 
    int n = getNbCrabes(); 
    for (int i = 0; i< n ; i++) { 
        int m = abs(getPositionOfCrabeNb(i) - position); 
        sum += m * (m+1) / 2; 
    }
    return sum; 
}