#ifndef DEF_POLYMER
#define DEF_POLYMER 

#include <string> 
#include <vector> 
#include <map> 

class Polymer {
    private: 
    std::string polymer; 
    std::map<std::string, std::vector<std::string>> rules; 
    std::map<std::string, unsigned long long int> frequenciesPair; 
    
    public: 
    // Constructors 
    Polymer(); 

    // Getters and setters 
    std::string getPolymerChain(); 
    std::map<std::string, std::vector<std::string>> getRules(); 
    std::vector<std::string> getPolymerizedPair(std::string unpolymerized); 
    void setPolymerChain(std::string polymerchain); 
    void addRule(std::string rule); 

    // Other methods 
    void Polymerize(); 
    unsigned long long int countIterations(); 

}; 

#endif 