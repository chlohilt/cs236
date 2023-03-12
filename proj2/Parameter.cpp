#include "Parameter.h"

Parameter::Parameter() {}

string Parameter::toString() {
    stringstream ss;
    if (stringName.length() != 0) {
        ss << stringName << endl;
    } else {
        ss << idName << endl;
    }
    return ss.str();
}

void Parameter::setString(string stringName){
    this->stringName = stringName;
    this->isConstant = true;
}

void Parameter::setId(string idName) {
    this->idName = idName;
    this->isConstant = false;
}