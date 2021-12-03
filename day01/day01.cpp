#include <iostream>
#include <string> 
#include <fstream> 
using namespace std;


int sumArray(int n, int* array) { 
  int sum = 0; 
  for (int i = 0; i < n; ++i) {
    sum += array[i]; 
  }  
  return sum; 
}

int puzzle1(string filename) {
  ifstream file; 
  file.open(filename); 
  string filecontent; 
  int counter = 0; 

  if (file.is_open() ) { 
    int old = 999999999; 

    while (file.good()) { 
      getline (file, filecontent); 
      int curr = stoi(filecontent); 

      if (old < curr) { 
        ++counter; 
      }

      old = curr; 
    }
  }

  file.close(); 
  return counter; 
}

int puzzle2(string filename, int slidewidth) {
  ifstream file; 
  file.open(filename); 
  int counter = 0; 
  int slidecount = 0; 
  string filecontent; 

  int index = 0, oldsum = 0, currsum = 0; 
  int terms[slidewidth]; 

  if (file.is_open()) {
    while (file.good()) { 
      getline (file, filecontent); 
      int idxcurr = index % slidewidth; 
      terms[idxcurr] = stoi(filecontent); 
      if (index >= slidewidth) {
        int currsum = sumArray(slidewidth, terms); 

        if (oldsum < currsum) { 
          ++counter; 
        }

        oldsum = currsum; 
      } 
      ++index; 
    } 
  }

  file.close(); 
  return counter; 
}


int main() {
  /* Instantiation of the file */ 
  string myfilename; 
  cout << "Filename of the input: "; 
  cin >> myfilename; 

  // Solution to puzzle 1: 1665 
  cout << "The solution to part one is " << puzzle1(myfilename) << ". \n"; 
  // Solution to puzzle 2: 1702 
  cout << "The solution to part two is " << puzzle2(myfilename, 3) << ". \n"; 

  return 0; 
}