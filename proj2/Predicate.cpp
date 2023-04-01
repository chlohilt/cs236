#include "Predicate.h"

Predicate::Predicate() {}

void Predicate::setId(string idName) {
    this->id = idName;
}

void Predicate::setParameters(vector<Parameter> parameters) {
    this->parameters = parameters;
}

string Predicate::toString() {
    stringstream ss;
    ss << id << "(";
    for (unsigned int i = 0; i < parameters.size(); ++i) {
        if (parameters[i].stringName.length() != 0 && i == (parameters.size()-1)) {
            ss << parameters[i].stringName << ")";
        } else if (parameters[i].idName.length() != 0 && i == (parameters.size()-1)){
            ss << parameters[i].idName << ")";
        } else if (parameters[i].stringName.length() != 0) {
            ss << parameters[i].stringName << ",";
        } else if (parameters[i].idName.length() != 0) {
            ss << parameters[i].idName << ",";
        }
    }

    return ss.str();
}