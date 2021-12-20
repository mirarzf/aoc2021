#include "CaveConnections.h" 

#include <string>
#include <sstream>
#include <vector>

using namespace std; 

// Constructors 

CaveConnections::CaveConnections() : 
    caves({{"start", 0},{"end", 1}}), 
    connectmap({{ "start", {"end"} }, { "end", {"start"} }}), 
    caveType({{"start", 0}, {"end", 1}})
    {} 

CaveConnections::CaveConnections(string listOfConnections) { 
    caves["start"] = 0; 
    caves["end"] = 1; 

    caveType["start"] = 0; 
    caveType["end"] = 1; 

    // Get all the cave names first 
    stringstream inputss(listOfConnections); 
    string connectstr; 
    int nbOfCaves = 2; 
    while (inputss.good()) { 
        getline(inputss, connectstr, '\n'); 
        string cavenameA; 
        string cavenameB; 
        stringstream caveconnectionss(connectstr); 
        getline(caveconnectionss, cavenameA, '-'); 
        getline(caveconnectionss, cavenameB, '-'); 

        if (caves.count(cavenameA) == 0) { 
            caves[cavenameA] = nbOfCaves; 
            connectmap[cavenameA] = {cavenameB}; 
            setTypeCave(cavenameA); 
            nbOfCaves++; 
        } else { 
            connectmap[cavenameA].push_back(cavenameB); 
        }

        if (caves.count(cavenameB) == 0) { 
            caves[cavenameB] = nbOfCaves; 
            connectmap[cavenameB] = {cavenameA}; 
            setTypeCave(cavenameB); 
            nbOfCaves++; 
        } else { 
            connectmap[cavenameB].push_back(cavenameA); 
        }
    }
}

// Getters and setters 

bool CaveConnections::areConnected(string caveA, string caveB) { 
    if (caves.count(caveA) == 1 && caves.count(caveB) == 1) { 
        int nbNeighboursA = connectmap[caveA].size(); 
        for (int i = 0; i < nbNeighboursA; i++) { 
            if (connectmap[caveA].at(i) == caveB) { 
                return true; 
            }
        }
    }
    return false; 
}

int CaveConnections::getNbCaves() { 
    return caves.size(); 
}

vector<string> CaveConnections::getCaveNames() { 
    vector<string> listcavenames; 
    for(map<string,int>::iterator it = caves.begin(); it != caves.end(); ++it) {
        listcavenames.push_back(it->first);
    }
    return listcavenames; 
}

int CaveConnections::getTypeCave(string caveName) { 
    return caveType[caveName]; 
}

void CaveConnections::setTypeCave(string caveName) { 
    if (caveName == "start") { 
        caveType[caveName] = 0; 
    } else if (caveName == "end") { 
        caveType[caveName] = 1;
    } else if (caveName[0] >= 'a' && caveName[0] <= 'z') { 
        caveType[caveName] = 2;
    } else { 
        caveType[caveName] = 3;
    }
}

vector<string> CaveConnections::getNeighbours(string caveName) { 
    if (connectmap.count(caveName) == 1) { 
        return connectmap[caveName];
    } 
    return {""}; 
}

vector<string> CaveConnections::getVisitableNeighbours(string caveName, vector<int> nbVisits, bool smallCaveTwice, int puzzlepart) { 
    vector<string> neighbours = getNeighbours(caveName); 
    int nnghb = neighbours.size(); 
    vector<string> visitableNeighbours; 
    
    for (int i = 0; i < nnghb; i++) { 
        bool conditionStartNghb = getTypeCave(neighbours[i]) == 0; 
        bool conditionSmallCave = getTypeCave(neighbours[i]) == 2 && nbVisits[caves[neighbours[i]]] == 1; 
        if (puzzlepart == 2) { 
            conditionSmallCave = getTypeCave(neighbours[i]) == 2 && nbVisits[caves[neighbours[i]]] > 0 && smallCaveTwice; 
        }

        if (!conditionStartNghb && !conditionSmallCave) { 
            visitableNeighbours.push_back(neighbours[i]); 
        }
    }
    return visitableNeighbours; 
}

vector<vector<string>> CaveConnections::getPathsToEnd(vector<string> beginningPath, int puzzlepart) { 
    vector<vector<string>> pathsToEnd; 
    string caveName = beginningPath.back(); 

    // Condition de terminaison 
    if (caveName == "end") { 
        return {beginningPath}; 
    }

    // Initialize the current path with beginningPath 
    vector<string> currentPath; 
    int nbp = beginningPath.size(); 
    for (int i = 0; i < nbp; i++) { 
        currentPath.push_back(beginningPath[i]); 
    }

    // Count the number of visits per cave and if there is a small cave that has already been visited twice 
    vector<int> nbVisits = vector<int>(getNbCaves(), 0); 
    bool smallCaveTwice = false; 
    for (int i = 0; i < nbp; i++) { 
        nbVisits[caves[beginningPath[i]]]++; 
        if (getTypeCave(beginningPath[i]) == 2 && nbVisits[caves[beginningPath[i]]] == 2) {
            smallCaveTwice = true; 
        }
    }

    vector<string> visitableNeighbours = getVisitableNeighbours(caveName, nbVisits, smallCaveTwice, puzzlepart); 
    int nvnghb = visitableNeighbours.size(); 

    if (nvnghb == 0) { 
        return {{}}; 
    }

    for (int i = 0; i < nvnghb; i++) { 
        vector<string> newBeginningPath = beginningPath; 
        newBeginningPath.push_back(visitableNeighbours[i]); 
        vector<vector<string>> pathsToAdd = getPathsToEnd(newBeginningPath, puzzlepart); 
        int nbPathsToAdd = pathsToAdd.size(); 
        for (int j = 0; j < nbPathsToAdd; j++) { 
            if (pathsToAdd[j].size() > 0) { 
                pathsToEnd.push_back(pathsToAdd[j]); 
            }
        }
    }

    return pathsToEnd; 
}

vector<vector<string>> CaveConnections::getAllPaths(int puzzlepart) { 
    vector<string> beginPath = {"start"}; 
    return getPathsToEnd(beginPath, puzzlepart); 
}

bool CaveConnections::containsASmallCave(vector<string> path) { 
    int n = path.size(); 
    for (int i = 0; i < n; i++) { 
        if (getTypeCave(path[i]) == 2) { 
            return true; 
        }
    }
    return false; 
}

int CaveConnections::getNbOfPathsThroughSmallCaves() { 
    int nbOfPathsWithSmallCaves = 0; 

    vector<vector<string>> pathsToEnd = getAllPaths(1); 
    int n = pathsToEnd.size(); 

    for (int i = 0; i < n; i++) { 
        if (containsASmallCave(pathsToEnd[i])) { 
            nbOfPathsWithSmallCaves++; 
        }
    }

    return nbOfPathsWithSmallCaves; 
}