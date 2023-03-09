#include <iostream>
#pragma once
#include <string>
#include <sstream>
using namespace std;

enum TokenType { COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EOF1 };

class Token {
private:
    TokenType type;
    string value;
    int line;

public:
    Token (TokenType type, string value, int line);

    string toString() const;

    string typeName(TokenType type) const;

    friend class Parser;

};