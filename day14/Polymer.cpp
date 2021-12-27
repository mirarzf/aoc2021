#include "Polymer.h"

#include <string> 
#include <vector>
#include <sstream> 
#include <map> 

using namespace std; 

// Constructors 

Polymer::Polymer() : polymer(""), rules({}), frequenciesPair({}) {}; 

// Getters and setters 

string Polymer::getPolymerChain() { 
    return polymer; 
}

map<string, vector<string>> Polymer::getRules() { 
    return rules; 
}

vector<string> Polymer::getPolymerizedPair(string unpolymerized) { 
    if (rules.count(unpolymerized) != 0) { 
        return rules[unpolymerized]; 
    }
    return {}; 
}

void Polymer::setPolymerChain(string polymerchain) { 
    polymer = polymerchain; 
    int n = polymerchain.size(); 
    frequenciesPair = {}; 
    for (int i = 1; i < n; i++) { 
        string keyPaire = ""; 
        keyPaire = keyPaire + polymerchain[i-1] + polymerchain[i]; 
        if (frequenciesPair.count(keyPaire) == 0) { 
            frequenciesPair[keyPaire] = 1; 
        } else { 
            frequenciesPair[keyPaire]++; 
        }
    }
}

void Polymer::addRule(string rule) { 
    stringstream inputrule(rule); 
    string paire; 
    string value; 
    inputrule >> paire;  
    char givenLetter = rule.back(); 
    string nouvPaire1 = ""; 
    nouvPaire1 = nouvPaire1 + paire[0] + givenLetter; 
    string nouvPaire2 = ""; 
    nouvPaire2 = nouvPaire2 + givenLetter + paire[1]; 
    vector<string> vecteurPaire = {nouvPaire1, nouvPaire2}; 
    rules.insert(pair<string, vector<string>>(paire, vecteurPaire)); 
}

// Other methods 

void Polymer::Polymerize() {
    map<string, unsigned long long int> copyFrequencies = frequenciesPair; 
    map<string, unsigned long long int>::iterator it = copyFrequencies.begin(); 
    while (it != copyFrequencies.end()) { 
        string keyPaire = it->first; 
        unsigned long long int keyPairIter = it->second; 
        vector<string> newPairs = getPolymerizedPair(keyPaire); 

        /* 
        We lessen the frequency of the keyPaire as it gets "destroyed" 
        by the creation of two new pairs 
        */ 
       frequenciesPair[keyPaire] -= keyPairIter; 

       /*
       We increase the frequence of the two new pairs as they get "created" 
       instead by the creation of two new pairs
       */ 
        if (frequenciesPair.count(newPairs[0]) == 0) { 
            frequenciesPair[newPairs[0]] = keyPairIter; 
        } else { 
            frequenciesPair[newPairs[0]] += keyPairIter; 
        }
        
        if (frequenciesPair.count(newPairs[1]) == 0) { 
            frequenciesPair[newPairs[1]] = keyPairIter; 
        } else { 
            frequenciesPair[newPairs[1]] += keyPairIter; 
        }

        it++; 
    }
}

unsigned long long int Polymer::countIterations() { 
    map<char, unsigned long long int> itPerCharMap; 
    map<string, unsigned long long int>::iterator itFreq = frequenciesPair.begin(); 

    while (itFreq != frequenciesPair.end()) { 
        string keyPaire = itFreq->first; 
        unsigned long long int keyPaireIter = itFreq->second; 
        char firstChar = keyPaire[0]; 

        if (itPerCharMap.count(firstChar) == 0) { 
            itPerCharMap[firstChar] = keyPaireIter; 
        } else { 
            itPerCharMap[firstChar] += keyPaireIter; 
        }

        itFreq++; 
    }

    // We need to add the frequency of the last character 
    char lastChar = polymer.back();
    itPerCharMap[lastChar]++;  
    
    unsigned long long int maximum = 0; 
    unsigned long long int minimum = 0; 

    map<char, unsigned long long int>::iterator itChar = itPerCharMap.begin(); 
    while (itChar != itPerCharMap.end()) { 
        unsigned long long int value = itChar->second; 
        if (maximum < value) { 
            maximum = value; 
        }

        if (value > 0 && (minimum > value || minimum == 0)) { 
            minimum = value; 
        }

        itChar++; 
    }

    return maximum-minimum; 
}