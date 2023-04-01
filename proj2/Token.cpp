#include "Token.h"
Token::Token (TokenType type, string value, int line) : type(type), value(value), line(line){}

string Token::toString() const {
    stringstream out;
    out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")";
    return out.str();
}


string Token::typeName(TokenType type) const {
    switch (type){
        case COMMA:
            return "COMMA";
        case PERIOD:
            return "PERIOD";
        case Q_MARK:
            return "Q_MARK";
        case LEFT_PAREN:
            return "LEFT_PAREN";
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
        case COLON:
            return "COLON";
        case COLON_DASH:
            return "COLON_DASH";
        case MULTIPLY:
            return "MULTIPLY";
        case ADD:
            return "ADD";
        case SCHEMES:
            return "SCHEMES";
        case FACTS:
            return "FACTS";
        case RULES:
            return "RULES";
        case QUERIES:
            return "QUERIES";
        case ID:
            return "ID";
        case STRING:
            return "STRING";
        case COMMENT:
            return "COMMENT";
        case UNDEFINED:
            return "UNDEFINED";
        case EOF1:
            return "EOF";
        default:
            return "UNDEFINED";
    }

}
