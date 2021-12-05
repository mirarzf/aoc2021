#include "Coord.h" 

Coord::Coord() : xcoord(0), ycoord(0) {} 

Coord::Coord(int x, int y) { 
    xcoord = x; 
    ycoord = y;
}

int Coord::getX() { 
    return xcoord; 
}

int Coord::getY() { 
    return ycoord; 
}