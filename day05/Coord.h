#ifndef DEF_COORDINATES
#define DEF_COORDINATES

class Coord { 
    private: 

    int xcoord; 
    int ycoord; 

    public: 

    // Constructors 
    Coord(); 
    Coord(int x, int y); 

    // Getters 
    int getX(); 
    int getY(); 
}; 

#endif 