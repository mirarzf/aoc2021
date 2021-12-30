#include "Graphe.h"

#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>

using namespace std; 

// Constructors 
Graphe::Graphe(string input, int puzzlepart) { 
    if (puzzlepart == 1) { 
        stringstream inputss(input); 
        string line; 
        inputss >> line; 
        cote = line.size(); 
        poids = vector<int>(cote*cote, 0); 
        int i = 0; 
        while (inputss.good()) { 
            for (int j = 0; j < cote; j++) { 
                poids[i*cote+j] = line[j] - '0'; 
            }
            inputss >> line; 
            i++; 
        }
    } else { 
        stringstream inputss(input); 
        string line; 
        inputss >> line; 
        int coteinitial = line.size(); 
        cote = 5*coteinitial; 
        poids = vector<int>(cote*cote, 0); 
        int i = 0; 
        while (inputss.good()) { 
            for (int j = 0; j < coteinitial; j++) { 
                for (int ki = 0; ki < 5; ki++) {
                    for (int kj = 0; kj < 5; kj++) { 
                        int oldValue = line[j] - '0'; 
                        int newValue = oldValue + ki + kj; 
                        if (newValue >= 10) { 
                            newValue -= 9; 
                        } 
                        poids[cote*(coteinitial*ki+i)+coteinitial*kj+j] = newValue; 
                    } 
                }
            }
            inputss >> line; 
            i++; 
        }
    }
}

// Getters and setters 
int Graphe::getCote() { 
    return cote; 
}

bool Graphe::areLinked(int numSommet1, int numSommet2) { 
    int i1 = numSommet1/cote; 
    int j1 = numSommet1%cote; 
    int i2 = numSommet2/cote; 
    int j2 = numSommet2%cote; 

    return (abs(i1-i2) == 1 || abs(j1-j2) == 1); 
}

int Graphe::getPoids(int numSommet) { 
    return poids[numSommet]; 
}

// Other methods 
vector<int> Graphe::getVoisins(int numSommet) { 
    vector<int> voisins = {}; 
    int i = numSommet/cote; 
    int j = numSommet%cote; 
    for (int indiceI = i-1; indiceI < i+2; indiceI++) { 
        for (int indiceJ = j-1; indiceJ < j+2; indiceJ++) { 
            bool Existant = indiceI >= 0 && indiceI < cote && indiceJ >= 0 && indiceJ < cote; 
            bool pasDiagonal = indiceI == i || indiceJ == j; 
            bool pasSommetInput = indiceI != i || indiceJ != j; 
            if (Existant && pasDiagonal && pasSommetInput) { 
                voisins.push_back(indiceI*cote+indiceJ); 
            }
        }
    }
    return voisins; 
}

vector<int> Graphe::getVoisinsValides(int numSommet, vector<bool> nonVisites) { 
    vector<int> voisins = getVoisins(numSommet); 
    vector<int> voisinsValides = {}; 
    int n = voisins.size(); 
    for (int i = 0; i < n; i++) { 
        if (nonVisites[voisins[i]]) { 
            voisinsValides.push_back(voisins[i]); 
        }
    }
    return voisinsValides; 
}

int Graphe::Dijkstra(int numDebut, int numFin) { 
    int nbTotalDeSommets = cote*cote; 
    int infini = 9*nbTotalDeSommets; 
    vector<bool> nonVisites(nbTotalDeSommets, true); 
    unordered_set<int> voisinsNonVisites; 
    vector<int> distance(nbTotalDeSommets, infini); 
    vector<int> predecessor(nbTotalDeSommets, cote); 
    distance[numDebut] = 0; 
    predecessor[numDebut] = 0; 
    int sommetActuel = numDebut; 
    int distanceActuelle = 0; 

    bool finNonTrouvee = true; 
    while (finNonTrouvee) { 
        // update de chaque distance du voisin (ou non) 
        vector<int> voisins = getVoisinsValides(sommetActuel, nonVisites); 
        int nvoisins = voisins.size(); 
        for (int k = 0; k < nvoisins; k++) { 
            int distanceNouvelle = distanceActuelle + getPoids(voisins[k]); 
            if (distanceNouvelle < distance.at(voisins[k])) { 
                distance.at(voisins[k]) = distanceNouvelle; 
                predecessor.at(voisins[k]) = sommetActuel; 
            }
            voisinsNonVisites.insert(voisins[k]); 
        }

        // on marque le sommet actuel comme étant visité 
        nonVisites[sommetActuel] = false; 

        // recherche du nouveau sommet "actuel" 
        int minimum = infini; 
        int numMini = 0; 
        for (int k : voisinsNonVisites) { 
            if (minimum > distance[k] && nonVisites[k]) { 
                minimum = distance[k]; 
                numMini = k; 
            }
        }
        sommetActuel = numMini; 
        distanceActuelle = minimum; 
        voisinsNonVisites.erase(sommetActuel); 
        finNonTrouvee = sommetActuel != numFin; 
    }
    return distance[numFin]; 
}

int Graphe::Dijkstra() { 
    return Dijkstra(0, cote*cote-1); 
}