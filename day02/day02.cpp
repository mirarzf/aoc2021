#include <iostream>
#include <fstream> 
#include <string> 
#include <sstream> 
using namespace std;

class SubCommand { 
    private: 
        string instr; 
        int unit; 
    
    public: 
        // Constructors 
        SubCommand(string instruction, int unitdeplacement) { 
            instr = instruction; 
            unit = unitdeplacement; 
        }
        SubCommand(string combination) {
            stringstream ss(combination);
            ss >> instr; 
            ss >> unit; 
        }

        // Getters and Setters 
        string getInstr() { 
            return instr; 
        }
        int getUnit() { 
            return unit; 
        }
}; 

class SubPos { 
    protected: 
        int dpos; 
        int hpos; 

    public: 
        // Constructor 
        SubPos() { 
            dpos = 0; 
            hpos = 0; 
        }

        // Getters And Setters 
        int getDepth() {
            return dpos; 
        } 
        int getHorizontal() { 
            return hpos; 
        }
        void setDepth(int depth) { 
            dpos = depth; 
        }
        void setHorizontal(int horizontal) { 
            hpos = horizontal; 
        }

        // Other Class Methods 
        void forward(SubCommand commande) { 
            string instr = commande.getInstr(); 
            int unit = commande.getUnit(); 
            if (instr =="forward"){ 
                hpos += unit; 
            } 
            else if (instr =="down"){ 
                dpos += unit; 
            } 
            else if (instr == "up"){ 
                dpos -= unit; 
            }
            else { 
                cout << "no instruction given"; 
            }
        }
}; 

class SubPos2 : public SubPos { 
    private: 
        int aim; 

    public: 
        // Constructor 
        SubPos2() { 
            SubPos(); 
            aim = 0; 
        }

        // Getters And Setters 
        int getAim() { 
            return aim; 
        }

        // Other Class Methods 
        void forward(SubCommand commande) { 
            string instr = commande.getInstr(); 
            int unit = commande.getUnit(); 
            if (instr =="forward"){ 
                hpos += unit; 
                dpos += unit*aim; 
            } 
            else if (instr =="down"){ 
                aim += unit; 
            } 
            else if (instr == "up"){ 
                aim -= unit; 
            }
            else { 
                cout << "no instruction given"; 
            }
        }
}; 

int puzzle1(string filename) { 
    ifstream file; 
    file.open(filename); 
    SubPos pos = SubPos(); 

    if (file.is_open()) { 
        while (file.good()) { 
            string line; 
            getline(file, line); 
            SubCommand commande = SubCommand(line); 
            pos.forward(commande); 
        }
    }
    file.close(); 
    return pos.getDepth()*pos.getHorizontal(); 
}

int puzzle2(string filename) { 
    ifstream file; 
    file.open(filename); 
    SubPos2 pos = SubPos2(); 

    if (file.is_open()) { 
        while (file.good()) { 
            string line; 
            getline(file, line); 
            SubCommand commande = SubCommand(line); 
            pos.forward(commande); 
        }
    }
    file.close(); 
    return pos.getDepth()*pos.getHorizontal(); 
}

int main() { 
    /* Instantiation of the file */ 
    string myfilename; 
    cout << "Filename of the input: "; 
    cin >> myfilename; 

    cout << "The solution to part one is " << puzzle1(myfilename) << ". \n"; 
    cout << "The solution to part two is " << puzzle2(myfilename) << ". \n"; 

    return 0; 
}