#include "Polymer.h"

#include <string> 
#include <vector>
#include <sstream> 
#include <map> 

using namespace std; 

// Constructors 

Polymer::Polymer() : polymer(""), rules({}), countIter({}) {}; 

// Getters and setters 

string Polymer::getPolymerChain() { 
    return polymer; 
}

map<string, char> Polymer::getRules() { 
    return rules; 
}

void Polymer::setPolymerChain(string polymerchain) { 
    polymer = polymerchain; 
}

void Polymer::addRule(string rule) { 
    stringstream inputrule(rule); 
    string paire; 
    string value; 
    inputrule >> paire;  
    rules.insert(pair<string, char>(paire, rule.back())); 
}

// Other methods 

void Polymer::Polymerize(string inputpaire, int nbiter) { 
    bool InputPaireNotInRules = rules.count(inputpaire) != 0; 
    if (nbiter != 0 && InputPaireNotInRules) { 
        char newLetter = rules[inputpaire]; 
        if (countIter.count(newLetter) == 0) { 
            countIter[newLetter] = 1; 
        } else {
            countIter[newLetter]++; 
        }
        string nouvellePaire = ""; 
        nouvellePaire = nouvellePaire + inputpaire[0] + newLetter; 
        Polymerize(nouvellePaire, nbiter-1);
        nouvellePaire = ""; 
        nouvellePaire = nouvellePaire + newLetter + inputpaire[1]; 
        Polymerize(nouvellePaire, nbiter-1);
    }
}

unsigned long long int Polymer::countIterations(int nbIter) { 
    char endPaire = polymer[0]; 
    if (countIter.count(endPaire) == 0) { 
        countIter[endPaire] = 1; 
    } else { 
        countIter[endPaire]++; 
    }
    
    int n = polymer.size(); 
    for (int i = 1; i < n; i++) { 
        string paire = ""; 
        paire = paire + polymer[i-1] + polymer[i]; 
        Polymerize(paire, nbIter); 
        char endPaire = polymer[i]; 
        if (countIter.count(endPaire) == 0) { 
            countIter[endPaire] = 1; 
        } else { 
            countIter[endPaire]++; 
        }
    }

    unsigned long long int maximum = 0; 
    unsigned long long int minimum = countIter[endPaire]; 
    map<char, unsigned long long int>::iterator it = countIter.begin(); 
    while (it != countIter.end()) {
        unsigned long long int value = it->second; 
        if (maximum < value) { 
            maximum = value; 
        }
        if (it == countIter.begin()) { 
            minimum = value; 
        } else { 
            if (minimum > value) { 
                minimum = value; 
            }
        }
        it++; 
    }
    return maximum-minimum; 

}