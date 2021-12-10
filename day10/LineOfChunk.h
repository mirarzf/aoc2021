#ifndef DEF_CHUNK
#define DEF_CHUNK

#include <string>
#include <vector> 

class LineOfChunk { 
    private: 
    std::vector<char> beginners; 
    std::vector<char> enders;
    std::vector<char> corrupted; 

    public: 
    // Constructors 
    LineOfChunk() ; 
    LineOfChunk(std::string line); 

    // Getters and setters 
    char getLastBeginner(); 
    char getLastCloser(); 

    // Other methods 
    bool isCorrupted(); 
    int getCharScore(char endingChar); 
    int getErrorScore(); 
    unsigned long long int getCompletionScore(); 
}; 

#endif 