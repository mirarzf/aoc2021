#ifndef DEF_OCTOPUSGRID
#define DEF_OCTOPUSGRID 

#include <string>
#include <vector> 

class Octopusgrid { 
    private: 
    int nrow; 
    int ncol; 
    std::vector<std::vector<int>> grid; 

    public: 

    // Constructors 
    Octopusgrid(); 
    Octopusgrid(std::string completegrid); 

    // Getters and setters 
    int getNcol(); 
    int getNrow(); 
    int getEnergyLevelAtPoint(int i, int j); 
    void setEnergyLevelAtPoint(int i, int j, int energylevel); 

    // Other methods 
    int getFlashesNbForOneStep(); 
}; 

#endif 