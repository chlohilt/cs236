#include <iostream>
#include <cctype>
#include <fstream>
#include <list>
#include <queue>
#include <string>
#include <bits/stdc++.h>
using namespace std;
#include "Token.h"

class Scanner {
private:
    string input;
    int line = 1;
public:
    Scanner(const string& input);
    ~Scanner();

    queue<Token> mainScanner();

    // this function prints out the queue of tokens
    void printQueue(queue<Token> TokenQueue);

    // this function keeps track of the whitespace
    bool isWhitespace(char currentChar);

    // this function checks if the current character is a letter
    bool letterCheck(char currentChar);

    bool otherCaseCheck(char currentChar);

    // this function check if the current character is a digit
    bool digitCheck(char currentChar);

    // while the input is a char or a digit, parse through to get the whole string
    // once that's done then pass the string into string function
    // else pass into token thing
    Token stringCheck(string checkString);

    // this function check for comments, colon dashes, and strings
    Token checkOtherStrings(string & currentString);

    // this function scans in values to see if it is a certain character
    Token scanToken(string valueString);
};