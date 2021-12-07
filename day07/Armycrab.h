#ifndef DEF_ARMEE_DE_CRABES
#define DEF_ARMEE_DE_CRABES

#include <string>
#include <vector> 

class Armycrab { 
    private: 

    std::vector<int> hpos; 

    public: 
    
    // Constructors 
    Armycrab(); 
    Armycrab(std::string popInit); 
    Armycrab(std::vector<int> popInitVect); 

    // Getters and setters 
    std::vector<int> getHorizontalPositions(); 
    int getPositionOfCrabeNb(int indCrab); 
    int getNbCrabes(); 

    // Other methods 
    int getFuelToGetPosition(int position); 
    int getFuelToGetPositionAdv(int position); 

}; 

#endif 