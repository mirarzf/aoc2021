#include <iostream>
#include <string> 
#include <fstream> 
#include <cmath> 
#include <vector> 
using namespace std;


int toDecimal(string binary) { 
    int n = binary.length(); 
    int decimal = 0; 
    for (int i = 0; i < n; i++) {
        if (binary[i]=='1') {
            decimal += pow(2, n-1-i); 
        } 
    }
    return decimal; 
}

char valueToMatch(int linecount, int counterBit, string ratingType) {
    if (ratingType == "Ox") { 
        return ( (linecount-counterBit) > counterBit) ? '0' : '1'; 
    }
    return ( (linecount-counterBit) <= counterBit) ? '0' : '1'; 
}

int rating(vector<string> vs, int counterBitPosition, int bitnumber, string ratingType) { 
    int bitPosition = 1; 
    while (vs.size() > 1 && bitPosition < bitnumber) { 
        char vtm = valueToMatch(vs.size(), counterBitPosition, ratingType); 
        counterBitPosition = 0; 
        vector<string> newvs = {}; 
        for (int i = 0; i < vs.size(); i++) {
            if (vs.at(i)[bitPosition] == vtm) { 
                newvs.push_back(vs.at(i));
                if (bitPosition < bitnumber-1 && vs.at(i)[bitPosition+1] == '1') { 
                    counterBitPosition++; 
                }
            }
        }
        vs = newvs; 
        bitPosition++; 
        if (vs.size() == 0) { 
            cout << "vs empty"; 
        }
    }
    return toDecimal(vs.at(0)); 
}

int puzzle2(int linecount, string filename, char firstbitOx, int n) {
    ifstream file; 
    file.open(filename); 
    vector<string> vsOx = {};
    vector<string> vsCO = {}; 

    int counterBitPositionOx = 0; 
    int counterBitPositionCO = 0; 

    while (file.good()) { 
        string line; 
        getline(file, line); 
        if (line[0] == firstbitOx) { 
            vsOx.push_back(line);
            if (line[1] == '1') { 
                counterBitPositionOx++; 
            }
        } else { 
            vsCO.push_back(line); 
            if (line[1] == '1') { 
                counterBitPositionCO++; 
            }
        }
    } 
    
    file.close(); 

    int ratingOx = rating(vsOx, counterBitPositionOx, n, "Ox"); 
    int ratingCO = rating(vsCO, counterBitPositionCO, n, "CO"); 

    return ratingOx * ratingCO; 
}

int puzzle(string filename, int puzzlepart) {
    ifstream file; 
    file.open(filename); 

    int linecounter = 0; 
    string line; 
    getline(file, line); 
    int n = line.length(); 
    int counter[n]; 

    for (int i = 0; i < n; i++) { 
        counter[i] = 0; 
    }

    while(file.good()) { 
        if (linecounter > 0) { 
            getline(file,line); 
        } 

        for (int j = 0; j < n ; j++) {
            if (line[j] == '1') { 
                counter[j] += 1;
            } 
        }

        linecounter++; 
    }
    file.close(); 

    if (puzzlepart == 1) { 
        string gammarate = ""; 
        string epsilonrate = ""; 

        for (int k = 0; k < n; k++) { 
            if (counter[k] > linecounter/2) {
                gammarate.append("1"); 
                epsilonrate.append("0"); 
            } else { 
                gammarate.append("0"); 
                epsilonrate.append("1"); 
            }
        }

        return toDecimal(gammarate) * toDecimal(epsilonrate);
    } else {
        char firstBitOx = (counter[0] < linecounter/2) ? '0' : '1'; 
        return puzzle2(linecounter, filename, firstBitOx, n); 
    }

    return 0; 
}

int main() {     
    /* Instantiation of the file */ 
    string myfilename; 
    cout << "Filename of the input: "; 
    cin >> myfilename; 

    cout << "The solution to part one is " << puzzle(myfilename, 1) << ". \n"; // Expected solution: 2035764
    cout << "The solution to part two is " << puzzle(myfilename, 2) << ". \n"; // Expected solution: 2817661

    return 0; 
}