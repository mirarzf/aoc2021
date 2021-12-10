#ifndef DEF_HEIGHTMAP 
#define DEF_HEIGHTMAP 

#include <sstream>
#include <vector> 

class Heightmap{ 
    private: 
    std::vector<std::vector<int>> map; 

    public: 

    // Constructors 
    Heightmap(); 
    Heightmap(std::string input); 

    // Getters and setters 
    int getHeightIn(int i, int j); 
    int getNbRow(); 
    int getNbCol(); 

    // Other methods 
    std::vector<std::vector<int>> getLowPoints(); 
    int getSumRiskLevel(); 
    int getBasinSizeAroundLowPoint(int x, int y); 
}; 

#endif 