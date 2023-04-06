#include <cmath>   //for math operation
#include <iomanip> //for declaring decimals
#include <sstream> //for reading word by word
#include <algorithm> //for filtering token char
#include <vector> //for vector
#include <fstream> //for textfile
#include <string> //to cast string into number
#include <iostream>
using namespace std;

void lexer(vector<string> lexemes);

int main() {
  char tokenChar[10] = {'<', '>', '+', '-', '*', '/', '(', ')', ';', '='};
  vector<string> tokenVector;

  //read from textfile
  string fileText;
  string input;
  ifstream MyReadFile("input_scode.txt");
  while (getline (MyReadFile, fileText)) {
    input = fileText;
  }
  MyReadFile.close();

  //extract and filter out the input into lexemes, remove space
  istringstream iss(input);
  do {
    string subs;
    iss >> subs;
    for (char i : subs) {
      for (int a = 0; a < 9; a++) {
        if (i == tokenChar[a]) {
          string str;
          str = i;
          if (subs != str) {
            subs.erase(remove(subs.begin(), subs.end(), i), subs.end());
            tokenVector.push_back(str);
          }
        }
      }
    }
    tokenVector.push_back(subs);
  } while (iss);

  //now we have a complete vector of lexemes, display them
  lexer(tokenVector);

  return 0;
}



void lexer(vector<string> lexemes) {
  string operatorArr[7] = {"+","-", "*", "/", "=", "<", ">"};
  string separatorArr[3] = {"(",")", ";"};
  bool continuing = true;

  ofstream outputFile;
  outputFile.open ("output.txt");

  outputFile << left << setw(16) << "Token" << "Lexeme" << endl;
  outputFile << "----------------------" << endl;
  for (string a : lexemes) {
    continuing = true;
    for (string b : operatorArr) {
      if (b == a) {
        outputFile << left << setw(16) << "operator" << a << endl;
        continuing = false;
        break;
      }
    }
    if (continuing) {
      for (string c : separatorArr) {
        if (c == a) {
          outputFile << left << setw(16) << "separator" << a << endl;
          continuing = false;
          break;
        }
      }
    }
    
    if (continuing) {
      for (char d : a) {
        if (d == '.') {
          outputFile << left << setw(16) << "real" << a << endl;
          continuing = false;
          break;
        }
      }
    }
    
    if (continuing) {
      if (a.length() == 1) {
        outputFile << left << setw(16) << "identifier" << a << endl;
      } else if (a.length() > 1) {
        outputFile << left << setw(16) << "keyword" << a << endl; 
      }
    }
  }

  outputFile.close();
}