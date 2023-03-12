#include "Token.h"
#include "Parameter.h"
#pragma once
#include <vector>

class Predicate {
private:
    string id;
    vector<Parameter> parameters;

public:
    Predicate();

    string toString();

    void setId(string idName);

    void setParameters(vector<Parameter> parameterList);

    friend class Rule;

    friend class Parser;

    friend class DatalogProgram;

    friend class Database;

    friend class Interpreter;

};
