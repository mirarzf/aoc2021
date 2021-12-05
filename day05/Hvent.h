#ifndef DEF_H_VENT 
#define DEF_H_VENT 

#include <iostream> 
#include <string>  
#include <vector>

#include "Coord.h"

class Hvent { 
    private: 

    int beginX; 
    int beginY;
    int finalX; 
    int finalY; 

    public: 

    // Constructors 
    Hvent(); 
    Hvent(int x0, int y0, int x1, int y1); 
    Hvent(std::string instr); 

    // Getters and setters 
    int getBeginX(); 
    int getBeginY(); 
    int getFinalX(); 
    int getFinalY();  

    void setBeginX(int x0); 
    void setBeginY(int y0); 
    void setFinalX(int x1); 
    void setFinalY(int y1); 

    // Other methods 
    std::vector<Coord> getPointsBetween(int puzzlepart); 

}; 

#endif 