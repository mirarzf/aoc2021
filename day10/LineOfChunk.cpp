#include "LineOfChunk.h"

#include <string>
#include <vector>

using namespace std; 

// Useful functions 

bool isABeginner(char beginChar) { 
    return (beginChar == '(' || beginChar == '[' || beginChar == '{' || beginChar == '<'); 
}

bool isAnEnder(char endChar) { 
    return (endChar == ')' || endChar == ']' || endChar == '}' || endChar == '>'); 
}

char closerToBeginner(char beginChar) { 
    if (beginChar == '(') { 
        return ')'; 
    }
    if (beginChar == '[') { 
        return ']'; 
    }
    if (beginChar == '{') { 
        return '}'; 
    }
    if (beginChar == '<') { 
        return '>'; 
    }
    return ' '; 
}

char beginnerToCloser(char endChar) { 
    if (endChar == ')') { 
        return '('; 
    }
    if (endChar == ']') { 
        return '['; 
    }
    if (endChar == '}') { 
        return '{'; 
    }
    if (endChar == '>') { 
        return '<'; 
    }
    return ' '; 
}

// Constructors 

LineOfChunk::LineOfChunk() : beginners({'('}), enders({')'}), corrupted() {}; 

LineOfChunk::LineOfChunk(string line) { 
    int n = line.length(); 
    for (int i = 0; i < n ; i++) { 
        if (isABeginner(line[i])) { 
            beginners.push_back(line[i]); 
            corrupted.push_back(line[i]); 
        }
        if (isAnEnder(line[i])) { 
            enders.push_back(line[i]); 
            if (corrupted.back() == beginnerToCloser(line[i])) { 
                corrupted.pop_back(); 
            } else { 
                corrupted.push_back(line[i]); 
            }
        }
    }
}

// Getters and setters 

char LineOfChunk::getLastBeginner() { 
    return beginners.back(); 
}

char LineOfChunk::getLastCloser() { 
    return enders.back(); 
}

// Other methods 

bool LineOfChunk::isCorrupted() { 
    int n = corrupted.size(); 
    for (int i = 0; i < n ; i++) { 
        if (isAnEnder(corrupted[i])) { 
            return true; 
        }
    }
    return false; 
}

int LineOfChunk::getCharScore(char character) { 
    if (character == ')') { 
        return 3; 
    } else if (character == ']') { 
        return 57; 
    } else if (character == '}') { 
        return 1197; 
    } else if (character == '>') { 
        return 25137; 
    } else if (character == '(') { 
        return 1; 
    } else if (character == '[') { 
        return 2; 
    } else if (character == '{') { 
        return 3; 
    } else if (character == '<') { 
        return 4; 
    } else { 
        return 0; 
    }    
}

int LineOfChunk::getErrorScore() {
    if (isCorrupted()) { 
        int n = corrupted.size(); 
        for (int i = 0; i < n ; i++) { 
            if (isAnEnder(corrupted[i])) { 
                return getCharScore(corrupted[i]); 
            }
        }
    } 
    return 0; 
}

unsigned long long int LineOfChunk::getCompletionScore() { 
    if (!isCorrupted()) { 
        int n = corrupted.size(); 
        unsigned long long int score = 0; 
        for (int i = n-1 ; i >= 0 ; i--) { 
            score = score*5; 
            score += getCharScore(corrupted[i]); 
        }
        return score; 
    }
    return 0; 
}