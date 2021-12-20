#ifndef DEF_CAVECONNECTIONS 
#define DEF_CAVECONNECTIONS 

#include <string>
#include <vector>
#include <map> 

class CaveConnections { 
    private: 
    std::map<std::string, int> caves; 
    std::map<std::string, std::vector<std::string>> connectmap; 
    std::map<std::string, int> caveType; 

    public: 

    // Constructors 
    CaveConnections(); 
    CaveConnections(std::string listOfConnections); 

    // Getters and setters 
    bool areConnected(std::string caveA, std::string caveB); 
    int getNbCaves(); 
    std::vector<std::string> getCaveNames(); 
    int getTypeCave(std::string caveName); 
    void setTypeCave(std::string caveName); 
    std::vector<std::string> getNeighbours(std::string caveName); 

    // Other methods 
    std::vector<std::string> getVisitableNeighbours(std::string caveName, std::vector<int> nbVisits, bool smallCaveTwice, int puzzlepart); 
    std::vector<std::vector<std::string>> getPathsToEnd(std::vector<std::string> beginningPath, int puzzlepart); 
    std::vector<std::vector<std::string>> getAllPaths(int puzzlepart); 
    bool containsASmallCave(std::vector<std::string> path); 
    int getNbOfPathsThroughSmallCaves(); 
}; 

#endif 