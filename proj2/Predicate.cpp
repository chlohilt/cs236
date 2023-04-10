#include "Predicate.h"

Predicate::Predicate() {}

Predicate::Predicate(string id) {
    this->id = id;
}

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
    // if there are no parameters
    if (parameters.size() == 0) {
        ss << ")";
    }

    return ss.str();
}