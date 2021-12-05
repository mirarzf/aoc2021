#include <iostream> 
#include <string> 
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <cmath> 
using namespace std; 

class BingoCard { 
    private: 
        vector<int> nbBoard; 
        vector<bool> marked; 
    public: 
        // Constructors 
        BingoCard(int carteDeNb[5][5]) { 
            for (int i=0;i<5;i++) { 
                for (int j=0;j<5;j++) { 
                    nbBoard.push_back(carteDeNb[i][j]); 
                    marked.push_back(false); 
                }
            } 
        }

        // Getters 
        vector<int> getNbBoard() { 
            return nbBoard; 
        }

        vector<bool> getMarkedBoard() { 
            return marked; 
        }

        int getSumOfUnmarked() { 
            int sum = 0; 
            for (int i=0;i<25;i++) { 
                if (marked.at(i) == false) { 
                    sum += nbBoard.at(i); 
                }
            }
            return sum; 
        }

        // Other methods 
        int indexInBoard(int nb) { 
            for (int i=0;i<25;i++) { 
                if (nbBoard.at(i)==nb) { 
                    return i; 
                }
            }
            return 26; 
        }

        bool isInBoard(int nb) { 
            int index = indexInBoard(nb); 
            return (index==26) ? false : true; 
        }

        void markBoard(int nb) { 
            int index = indexInBoard(nb); 
            if (index != 26) { 
                marked[index] = true; 
            }
        }

        bool isMarked(int nb) { 
            if (isInBoard(nb)) { 
                int index = indexInBoard(nb); 
                return marked.at(index); 
            }
            return false; 
        }

        bool isWinning() { 
            bool ligne = true; 
            bool colonne = true;
            for (int i=0; i < 5; i++) { 
                int j = 0; 
                while (j < 5 && (ligne || colonne)) { 
                    if (marked.at(5*i+j) == false) { 
                        ligne = false; 
                    }
                    if (marked.at(5*j+i) == false) { 
                        colonne = false; 
                    }
                    j++; 
                }

                if (ligne || colonne) { 
                    return true; 
                } else { 
                    ligne = true; 
                    colonne = true; 
                }
            }
            return false; 
        }

}; 

class BingoBoard { 
    private: 
        vector<BingoCard> bboard; 
        vector<bool> hasWon; 
    
    public: 
        // Constructors 
        BingoBoard() { 
            vector<BingoCard> bboard; 
            vector<bool> hasWon; 
        }
        BingoBoard(vector<BingoCard> bingoCardList) { 
            bboard = bingoCardList; 
            int n = bingoCardList.size(); 
            for (int i = 0; i < n; i++) { 
                hasWon.push_back(false); 
            }
        }

        // Getters and Setters 
        BingoCard getCardNumber(int i) { 
            return bboard.at(i); 
        }

        vector<bool> getWinnersList() { 
            return hasWon; 
        }

        bool getHasWon(int cardNb) { 
            return hasWon.at(cardNb); 
        }

        int getNbOfBoards() { 
            return bboard.size(); 
        }

        int getNbOfWinners() { 
            int nbOfWinners = 0; 
            for (int i = 0; i < getNbOfBoards() ; i++) { 
                if (getHasWon(i)) { 
                    nbOfWinners++; 
                }
            }
            return nbOfWinners; 
        }

        void addBingoCard(BingoCard bcard) { 
            bboard.push_back(bcard); 
            hasWon.push_back(false); 
        }

        void setCardAsWinner(int cardNb) { 
            if (cardNb < getNbOfBoards()) { 
                hasWon[cardNb] = true; 
            }
        }

        // Other Methods 
        void markTheCards(int nbTire) { 
            for (int i = 0; i < getNbOfBoards() ; i++) { 
                bboard.at(i).markBoard(nbTire); 
            }
        }

        int getWinner() { 
            int n = getNbOfBoards(); 
            int indexWinner = n; 
            for (int i=0; i<n; i++) { 
                if (getWinnersList().at(i) == false && getCardNumber(i).isWinning()) { 
                    setCardAsWinner(i); 
                    indexWinner = i; 
                }
            }
            return indexWinner; 
        }
}; 

class Tirage { 
    private: 
        vector<int> listeTirage; 
        int currIndex; 
    
    public: 
        // Constructors 
        Tirage() { 
            vector<int> listeTirage; 
            currIndex = 0; 
        }
        Tirage(vector<int> listeNb) { 
            listeTirage = listeNb; 
            currIndex = 0; 
        }

        // Getters and setters 
        vector<int> getListe() { 
            return listeTirage; 
        }

        int getCurrIndex() { 
            return currIndex; 
        }

        int getLenTirage() { 
            return listeTirage.size(); 
        }

        void addTirageNb(int nb) { 
            listeTirage.push_back(nb); 
        }

        // Other methods 
        int tirerUnNb() { 
            if (currIndex < getLenTirage()) {
                int nbTire = listeTirage.at(currIndex); 
                currIndex++; 
                return nbTire; 
            } else { 
                cout << "Tirage terminé. \n"; 
                return 0; 
            }
        }

        bool isTirageTermine() { 
            return (getCurrIndex() == getLenTirage()); 
        }
    
}; 

//..............................................................................................

int puzzle(string filename, int puzzlepart = 1) { 
    ifstream file; 
    file.open(filename); 
     
    // Create the draw 
    string line; 
    getline(file, line); 
    stringstream ss(line); 
    Tirage tirage = Tirage(); 
    
    string newTirageNb; 
    while (getline(ss, newTirageNb, ',')) { 
        tirage.addTirageNb(stoi(newTirageNb)); 
    } 
    getline(file, line); // Helps get rid of the empty line 

    // Create the bingo board and the bingo cards 
    BingoBoard board = BingoBoard(); 

    while (file.good()) { 
        string line; 
        int carteDeNb[5][5]; 
        for (int i = 0; i<5; i++) { 
            getline(file, line); 
            stringstream ss(line); 
            string newNb; 
            int j = 0; 
            while (ss >> newNb) { 
                carteDeNb[i][j] = stoi(newNb); 
                j++; 
            }

        } 
        BingoCard card = BingoCard(carteDeNb); 
        board.addBingoCard(card); 
        getline(file, line); // helps to get rid of the empty line separating bingo cards 

    } 

    file.close(); 

    int nbOfCards = board.getNbOfBoards(); 
    int nbDeNbTires = tirage.getLenTirage(); 

    // For puzzle part 2 
    int lastWinningNb; 
    int lastSumOfWinningUnmarked; 

    for (int i = 0; i < nbDeNbTires; i++) { 
        int nbTire = tirage.tirerUnNb(); 
        board.markTheCards(nbTire); 
        int winningBoardNb = board.getWinner(); 
        if (winningBoardNb < nbOfCards) { 
            int sumUnmarkedWinningBoard = board.getCardNumber(winningBoardNb).getSumOfUnmarked(); 

            if (puzzlepart == 1) { 
                return sumUnmarkedWinningBoard * nbTire;  
            } else { 
                if (sumUnmarkedWinningBoard > 0) { 
                    lastWinningNb = nbTire; 
                    lastSumOfWinningUnmarked = sumUnmarkedWinningBoard; 
                    
                    if (board.getNbOfWinners() == nbOfCards && sumUnmarkedWinningBoard != 0) { 
                        return sumUnmarkedWinningBoard * nbTire; 
                    }
                } 
            }
        }
    }

    return lastSumOfWinningUnmarked * lastWinningNb; 
    
}

int main() {     
    /* Instantiation of the file */ 
    string myfilename; 
    cout << "Filename of the input: "; 
    cin >> myfilename; 

    // Solution to puzzle 1: 44736 
    cout << "The solution to part one is " << puzzle(myfilename, 1) << ". \n"; 
    // Solution to puzzle 2: 1827
    cout << "The solution to part two is " << puzzle(myfilename, 2) << ". \n"; 
    return 0; 
}