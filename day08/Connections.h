#ifndef DEF_CONNECTIONS
#define DEF_CONNECTIONS

#include <string>

class Connections { 
    private: 
    std::string un; 
    std::string quatre; 
    std::string display; 

    public: 

    // Constructors 
    Connections(); 
    Connections(std::string idConn); 

    // Getters and setters 
    std::string getUn(); 
    std::string getQuatre(); 
    std::string getDisplay(); 

    // Other methods 
    bool isUn(std::string digits); 
    bool isQuatre(std::string digits); 
    bool isSept(std::string digits); 
    bool isHuit(std::string digits); 
    
    int getShareWithUn(std::string digits); 
    int getShareWithQuatre(std::string digits); 

    int getInt(std::string digits); 
    int getDisplayAsInt(); 
};

#endif 