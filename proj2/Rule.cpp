#include "Rule.h"

Rule::Rule() {}

void Rule::setPredicates(vector<Predicate> predicates) {
    this->predicates = predicates;
}

void Rule::setName(string name) {
    this->name = name;
}

string Rule::toString() {
    stringstream ss;
    for (unsigned int i = 0; i < predicates.size(); ++i) {
        if (i == 0) {
            ss << predicates[i].toString() << " :- ";
        }
        else if (i == predicates.size() - 1){
            ss << predicates[i].toString();
        }
        else if (predicates[i].id.length() != 0) {
            ss << predicates[i].toString() << ",";
        }

    }

    return ss.str();
}