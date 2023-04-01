#include "Token.h"
#include "Predicate.h"
#include <vector>
#pragma once

class Rule {
private:
    string name;
    vector<Predicate> predicates;
public:
    Rule();

    void setName(string name);

    string toString();

    void setPredicates(vector<Predicate> predicates);

    friend class Parser;

    friend class Interpreter;

};