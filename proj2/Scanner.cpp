#include "Scanner.h"

Scanner::Scanner(const string& input): input(input) {}
Scanner::~Scanner() {}

queue<Token> Scanner::mainScanner() {
    string currentString = input;
    queue<Token> TokenList;
    while (currentString != "" && currentString != "\n") {
        // create current character and then run through white space
        char currentChar = currentString.at(0);
        while (isWhitespace(currentChar)) {
            if (currentChar == '\n') {
                line++;
            }
            if (currentString != "" && currentString != "\n") {
                currentString = currentString.substr(1);
                currentChar = currentString.at(0);
            }
            else {
                currentString = "";
                break;
            }
        }
        if (currentString != "") {
            // check if it's a letter and if it is add to a string and then when the string is done,
            // do the string check function that checks for schemes, ids, and other stuff
            if (letterCheck(currentChar)) {
                string inputString;
                while (letterCheck(currentChar) || digitCheck(currentChar)) {
                    inputString += currentChar;
                    currentString = currentString.substr(1);
                    currentChar = currentString.at(0);
                }
                TokenList.push(stringCheck(inputString));
            }
                // else if (digitCheck(currentChar)) {
                // }
            else if (otherCaseCheck(currentChar)) {
                TokenList.push(checkOtherStrings(currentString));
            }
            else {
                TokenList.push(scanToken(currentString));
                currentString = currentString.substr(1);
            }
        }
        else {
            break;
        }
    }
    TokenList.push(Token (EOF1, "", line));
    // then I need to print out all the Tokens created!!
    //printQueue(TokenList);
    return TokenList;
}

// this function prints out the queue of tokens
void Scanner::printQueue(queue<Token> TokenQueue) {
    int queueLength = TokenQueue.size();
    while (!TokenQueue.empty()) {
        cout << (TokenQueue.front()).toString() << endl;
        TokenQueue.pop();
    }
    cout << "Total Tokens = " << queueLength << endl;
}

// this function keeps track of the whitespace
bool Scanner::isWhitespace(char currentChar) {
    if (currentChar == ' ' || currentChar == '\n' || currentChar == '\t') {
        return true;
    }
    else {
        return false;
    }
}

// this function checks if the current character is a letter
bool Scanner::letterCheck(char currentChar) {
    if (isalpha(currentChar)) {
        return true;
    }
    else {
        return false;
    }
}

bool Scanner::otherCaseCheck(char currentChar) {
    if (currentChar == '\'' || currentChar == ':' || currentChar == '#') {
        return true;
    }
    else {
        return false;
    }
}

// this function check if the current character is a digit
bool Scanner::digitCheck(char currentChar) {
    if (isdigit(currentChar)) {
        return true;
    }
    else {
        return false;
    }
}

// while the input is a char or a digit, parse through to get the whole string
// once that's done then pass the string into string function
// else pass into token thing
Token Scanner::stringCheck(string checkString) {
    if (checkString[0] == 'S' && checkString[1] == 'c' && checkString[2] == 'h' && checkString[3] == 'e' && checkString[4] == 'm' && checkString[5] == 'e' && checkString[6] == 's'
        && !letterCheck(checkString[7]) && !digitCheck(checkString[7])) {
        return Token (SCHEMES, checkString, line);
    }
    else if (checkString[0] == 'F' && checkString[1] == 'a' && checkString[2] == 'c' && checkString[3] == 't' && checkString[4] == 's'
             && !letterCheck(checkString[5]) && !digitCheck(checkString[5])) {
        return Token (FACTS, checkString, line);
    }
    else if (checkString[0] == 'R' && checkString[1] == 'u' && checkString[2] == 'l' && checkString[3] == 'e' && checkString[4] == 's'
             && !letterCheck(checkString[5]) && !digitCheck(checkString[5])) {
        return Token (RULES, checkString, line);
    }
    else if (checkString[0] == 'Q' && checkString[1] == 'u' && checkString[2] == 'e' && checkString[3] == 'r' && checkString[4] == 'i' && checkString[5] == 'e' && checkString[6] == 's'
             && !letterCheck(checkString[7]) && !digitCheck(checkString[7])) {
        return Token (QUERIES, checkString, line);
    }
    else if (digitCheck(checkString[0])) {
        return Token (UNDEFINED, checkString, line);
    }
    else {
        return Token (ID, checkString, line);
    }

}

// this function check for comments, colon dashes, and strings
Token Scanner::checkOtherStrings(string & currentString) {
    char currentChar = currentString[0];
    stringstream valueToPassStream;
    valueToPassStream << currentChar;
    string valueToPass = valueToPassStream.str();
    // colon and colon dash
    if (currentChar == ':') {
        if (currentString[1] != '\0' && currentString[1] == '-') {
            valueToPass += currentString[1];
            currentString = currentString.substr(2);
            return Token (COLON_DASH, valueToPass, line);
        }
        currentString = currentString.substr(1);
        return Token (COLON, valueToPass, line);
    }
        // comment case
    else if (currentChar == '#') {
        // find either end of line/file or other # for end of block comment
        // multi block comment needs some stuff in between it that has letters on new line/ the new line is at an index less than the new #
        string searchString = currentString.substr(1);
        int endBlockComment = searchString.find('#');
        int startSecondLineComment = searchString.find("\n");
        string startLooking = currentString.substr(startSecondLineComment);
        char lookingChar = startLooking.at(0);
        while (isWhitespace(lookingChar)) {
            if (lookingChar == '\n') {
                line++;
            }
            if (currentString != "" && currentString != "\n") {
                currentString = currentString.substr(1);
                lookingChar = currentString.at(0);
            }
            else {
                currentString = "";
                break;
            }
        }

        char startSecondLineCommentChar = currentString.at(0);
        // need to check if a new # is found
        // if it is we also need to check that it is on the next line and
        // that the first char of the next line isn't also a #

        if ((endBlockComment != -1) && (startSecondLineComment < endBlockComment) && (startSecondLineCommentChar != '#')) {
            string multiLineComment = currentString.substr(0, endBlockComment + 2);
            currentString = currentString.substr(endBlockComment + 2);
            return Token (COMMENT, multiLineComment, line);
        }
        else {
            int endComment = searchString.find('\n');
            if (endComment != -1) {
                string comment = currentString.substr(0, endComment + 1);
                currentString = currentString.substr(endComment + 1);
                return Token (COMMENT, comment, line);
            }
            else {
                string commentToEnd = currentString;
                currentString = "";
                return Token (COMMENT, commentToEnd, line);
            }
        }
    }
    else if (currentChar == '\'') {
        // find new ' to find end of comment
        string searchString = currentString.substr(1);
        int endString = searchString.find('\'');
        if (endString != -1) {
            string fullString = currentString.substr(0, endString + 2);
            currentString = currentString.substr(endString + 2);
            return Token (STRING, fullString, line);
        }
        else {
            string fullString = currentString;
            int num_lines = count( currentString.begin(), currentString.end(), '\n' ) ;
            num_lines += ( !currentString.empty() && currentString.back() != '\n' ) ;
            line += num_lines;
            currentString = "";
            return Token (UNDEFINED, fullString, line - num_lines);
        }
    }
    else {
        return Token (UNDEFINED, currentString, line);
    }
}

// this function scans in values to see if it is a certain character
Token Scanner::scanToken(string valueString) {
    // some funky stuff to convert the char to a string
    const char value = valueString[0];
    stringstream valueToPassStream;
    valueToPassStream << value;
    string valueToPass = valueToPassStream.str();
    switch (value) {
        case ',':
            return Token (COMMA, valueToPass, line);
        case '.':
            return Token (PERIOD, valueToPass, line);
        case '?':
            return Token (Q_MARK, valueToPass, line);
        case '(':
            return Token (LEFT_PAREN, valueToPass, line);
        case ')':
            return Token (RIGHT_PAREN, valueToPass, line);
        case '*':
            return Token (MULTIPLY, valueToPass, line);
        case '+':
            return Token (ADD, valueToPass, line);
        default:
            return Token (UNDEFINED, valueToPass, line);
    }
}
