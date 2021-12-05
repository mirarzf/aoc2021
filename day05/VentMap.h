#ifndef DEF_VENT_MAP 
#define DEF_VENT_MAP

#include <vector> 
#include "Hvent.h"
#include "Coord.h"

class VentMap { 
    private: 
    int xlength; 
    int ylength; 
    std::vector< std::vector<int> > map; 

    public: 
    //Constructors 
    VentMap(); 
    VentMap(std::vector<Coord> listCoord); 

    // Getters and Setters 
    int getXLength(); 
    int getYLength(); 
    int getNbOfDangerZone(); 
    void addVentToMap(Hvent hydrovent, int puzzlepart); 

    // Other methods 
}; 

#endif