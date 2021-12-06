#include "School.h" 

#include <cmath> 
#include <string>
#include <sstream>
#include <vector> 

using namespace std; 

// Constructeurs 
School::School() : population{vector<unsigned long long int>(9)}, indexOfZeroDays(0), gestationTime(7), suppTimeOfFirstCycle(2) {}; 

School::School(string initpop, int tpsGest, int tpsSuppGestFC) { 
    stringstream ss(initpop); 
    string temp = ""; 
    vector<unsigned long long int> populationTemp(tpsGest+tpsSuppGestFC, 0); 
    while (ss.good()) { 
        getline(ss, temp, ','); 
        populationTemp[stoull(temp)]++; 
    }
    population = populationTemp; 

    gestationTime = tpsGest; 
    suppTimeOfFirstCycle = tpsSuppGestFC; 
    indexOfZeroDays = 0; 
}

unsigned long long int School::getNbPopulation() { 
    int n = population.size(); 
    unsigned long long int sumpop = 0; 
    for (int i = 0 ; i<n; i++) { 
        sumpop += population[i]; 
    }
    return sumpop; 
}

int School::getIndexOfZeroDays() { 
    return indexOfZeroDays; 
}

int School::getSuppTimeFirstCycle() { 
    return suppTimeOfFirstCycle; 
}

void School::setIndexOfZeroDays(int newindex) { 
    indexOfZeroDays = newindex; 
}

void School::growOneDay() { 
    int n = population.size(); 
    int oldindex = getIndexOfZeroDays(); 
    int newindex = (oldindex+1) % n; 
    int nextIndexOfParents = (oldindex-getSuppTimeFirstCycle()+n)%n; 
    population[nextIndexOfParents] += population[oldindex]; 
    setIndexOfZeroDays(newindex); 
}
