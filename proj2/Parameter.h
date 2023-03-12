#include "Token.h"
#pragma once

class Parameter {
private:
    string stringName;
    string idName;
    bool isConstant;

public:
    Parameter();

    void setString(string stringName);

    void setId(string idName);

    string toString();

    friend class Predicate;

    friend class Parser;

    friend class Database;

    friend class Interpreter;

};