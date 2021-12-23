#ifndef DEF_TRANSPARENT_PAPER 
#define DEF_TRANSPARENT_PAPER

#include <vector> 
#include <string>

class Paper {
    private: 
    std::vector<std::vector<int>> visibleDots; 
    int limitx; 
    int limity; 
    std::vector<char> instructAxis;
    std::vector<int> instructLineNb; 

    public:     
    // Constructor 
    Paper(); 
    Paper(std::string line); 

    // Getters and Setters 
    int getLimitX(); 
    int getLimitY(); 
    void setLimitX(int x); 
    void setLimitY(int y); 

    // Other methods 
    void applyInstruction(char axis, int linenb); 
    int getNbOfVisibleDots(int puzzlepart); 
}; 

#endif 