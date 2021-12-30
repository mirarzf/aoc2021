#ifndef DEF_GRAPHE
#define DEF_GRAPHE

#include <string> 
#include <vector>

class Graphe {
    private: 
    int cote; 
    std::vector<int> poids; 
    
    public: 
    // Constructors 
    Graphe(std::string input, int puzzlepart); 

    // Getters and setters 
    int getCote(); 
    bool areLinked(int numSommet1, int numSommet2); 
    int getPoids(int numSommet); 

    // Other methods 
    std::vector<int> getVoisins(int numSommet); 
    std::vector<int> getVoisinsValides(int numSommet, std::vector<bool> nonVisites); 
    int Dijkstra(int numDebut, int numFin); 
    int Dijkstra(); 
}; 

#endif 