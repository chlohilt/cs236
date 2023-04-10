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

    Rule(Predicate headPredicate);

    void addBodyPredicate(Predicate bodyPredicate);

    void setName(string name);

    Predicate getBodyPredicate(int predicateIndex);

    Predicate getHeadPredicate();

    string toString();

    void setPredicates(vector<Predicate> predicates);

    friend class Parser;

    friend class Interpreter;

    friend class Graph;

};