#ifndef DEF_POLYMER
#define DEF_POLYMER 

#include <string> 
#include <vector> 
#include <map> 

class Polymer {
    private: 
    std::string polymer; 
    std::map<std::string, char> rules; 
    std::map<char, unsigned long long int> countIter; 
    
    public: 
    // Constructors 
    Polymer(); 

    // Getters and setters 
    std::string getPolymerChain(); 
    std::map<std::string, char> getRules(); 
    void setPolymerChain(std::string polymerchain); 
    void addRule(std::string rule); 

    // Other methods 
    void Polymerize(std::string inputpaire, int nbiter); 
    unsigned long long int countIterations(int nbIter); 

}; 

#endif 