#ifndef DEF_FISH_SCHOOL
#define DEF_FISH_SCHOOL 

#include <string>
#include <vector>

class School { 
    private: 

    std::vector<unsigned long long int> population; 
    int indexOfZeroDays; 
    int gestationTime; 
    int suppTimeOfFirstCycle; 

    public: 

    // Constructors 
    School(); 
    School(std::string initpop, int tpsGest, int tpsSuppGestFC); 

    // Getters and setters 
    unsigned long long int getNbPopulation(); 
    int getIndexOfZeroDays(); 
    int getSuppTimeFirstCycle(); 
    
    void setIndexOfZeroDays(int newindex); 

    // Other methods 
    void growOneDay(); 
}; 

#endif 