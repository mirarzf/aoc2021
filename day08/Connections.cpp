#include "Connections.h"

#include <string> 
#include <sstream> 
#include <vector> 
#include <cmath>   

using namespace std; 

// Constructors 

Connections::Connections() : un("cf"), quatre("bcdf"), display("") {}; 

Connections::Connections(string idConn) { 
    stringstream ss(idConn); 
    string input; 
    while (ss.good()) { 
        getline(ss, input, '|'); 
        stringstream ssuniqueID(input); 
        string digits; 
        while (ssuniqueID.good()) { 
            getline(ssuniqueID, digits, ' '); 
            if (digits.length() == 2) { 
                un = digits; 
            } else if (digits.length() == 4) { 
                quatre = digits; 
            }
        } 
        getline(ss, display, '|'); 
    }
}

// Getters and setters 

string Connections::getUn() { 
    return un; 
}

string Connections::getQuatre() { 
    return quatre; 
}

string Connections::getDisplay() { 
    return display; 
}

// Other methods 

bool Connections::isUn(string digits) { 
    return digits.length() == 2; 
}

bool Connections::isQuatre(string digits) { 
    return digits.length() == 4; 
}

bool Connections::isSept(string digits) { 
    return digits.length() == 3; 
}

bool Connections::isHuit(string digits) { 
    return digits.length() == 7; 
}

int Connections::getShareWithUn(string digits) { 
    int n = digits.length(); 
    int howmany = 0; 
    for (int i = 0 ; i < n ; i++) { 
        char dig = digits[i]; 
        for (int j = 0 ; j < 2 ; j++) { 
            if (dig == un[j]) { 
                howmany++; 
            }
        }
    }
    return howmany; 
}

int Connections::getShareWithQuatre(string digits) { 
    int n = digits.length(); 
    int howmany = 0; 
    for (int i = 0 ; i < n ; i++) { 
        char dig = digits[i]; 
        for (int j = 0 ; j < 4; j++) { 
            if (dig == quatre[j]) { 
                howmany++; 
            }
        }
    }
    return howmany; 
}

int Connections::getInt(string digits) { 
    if (isUn(digits)) { 
        return 1; 
    } else if (isQuatre(digits)) { 
        return 4; 
    } else if (isSept(digits)) { 
        return 7; 
    } else if (isHuit(digits)) { 
        return 8; 
    } else { 
        int n = digits.length(); 
        int shareWithUn = getShareWithUn(digits); 
        int shareWithQuatre = getShareWithQuatre(digits); 
        if (n == 5) { 
            if (shareWithUn == 2) { 
                return 3; 
            } else if (shareWithQuatre == 2) { 
                return 2; 
            } else if (shareWithQuatre == 3) { 
                return 5; 
            }
        }
        if (n == 6) { 
            if (shareWithUn == 1) { 
                return 6; 
            } else if (shareWithQuatre == 3) { 
                return 0; 
            } else if (shareWithQuatre == 4) { 
                return 9; 
            }
        }
    }
    return 10; 
}

int Connections::getDisplayAsInt() { 
    int displayint = 0; 
    vector<int> displaydigits; 
    stringstream ss(display); 
    string temp; 
    while (ss.good()) { 
        getline(ss, temp, ' '); 
        if (temp.length()!=0) { 
            displaydigits.push_back(getInt(temp)); 
        } 
    }
    int n = displaydigits.size(); 
    for (int i = 0; i < n; i++) { 
        displayint += pow(10, n-1-i) * displaydigits[i]; 
    }
    return displayint; 
}