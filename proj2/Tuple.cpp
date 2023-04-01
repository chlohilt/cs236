//
// Created by hilto on 3/4/2023.
//

#include "Tuple.h"
#include <sstream>

Tuple::Tuple(vector<string> values) : vector<string>(values) {
    this->values = values;
}

Tuple::Tuple() {}

void Tuple::addValue(string value) {
    this->values.push_back(value);
}

string Tuple::toString(const Scheme& scheme) const {
    const Tuple& tuple = *this;
    stringstream out;
    vector<string> visitedAlready;
    vector<string> schemeNonConstants;
    int numberOfGoodIterations = 0;
    // counting how many are constants
    for (int nameValue = 0; unsigned(nameValue) < scheme.names.size(); nameValue++) {
        if (int((scheme.names.at(nameValue)).find("'")) == -1) {
            schemeNonConstants.push_back(scheme.names.at(nameValue));
        }
    }
    int sizePrint = 0;
    vector<string> visitedAlreadyPartTwo;
    // checking how big the list is I need to print
    for (int nameValue = 0; unsigned(nameValue) < scheme.names.size(); nameValue++) {
        if (int((scheme.names.at(nameValue)).find("'")) == -1) {
            vector<string>::iterator it = find(visitedAlreadyPartTwo.begin(), visitedAlreadyPartTwo.end(), scheme.names.at(nameValue));
            if (it == visitedAlreadyPartTwo.end()) {
                sizePrint++;
            }
        }
        visitedAlreadyPartTwo.push_back(scheme.names.at(nameValue));
    }

    for (int nameValue = 0; unsigned(nameValue) < scheme.names.size(); nameValue++) {
        if (int((scheme.names.at(nameValue)).find("'")) == -1) {
            if (numberOfGoodIterations == 0) {
                out << "  ";
            }
            vector<string>::iterator it = find(visitedAlready.begin(), visitedAlready.end(), scheme.names.at(nameValue));
            if (it == visitedAlready.end()) {
                out << scheme.names.at(nameValue) << "=" << tuple.values.at(numberOfGoodIterations);
                if (numberOfGoodIterations < sizePrint - 1) {
                    out << ", ";
                }
            }
            numberOfGoodIterations++;
            visitedAlready.push_back(scheme.names.at(nameValue));
        }
    }
    return out.str();
}

string Tuple::toStringPartTwo(const Scheme& originalScheme, const Scheme& relationScheme) {
    const Tuple& tuple = *this;
    stringstream out;
    vector<string> visitedAlready;
    vector<string> schemeNonConstants;
    int numberOfGoodIterations = 0;
    // counting how many are constants
    for (int nameValue = 0; unsigned(nameValue) < originalScheme.names.size(); nameValue++) {
        if (int((originalScheme.names.at(nameValue)).find("'")) == -1) {
            schemeNonConstants.push_back(originalScheme.names.at(nameValue));
        }
    }
    int sizePrint = 0;
    vector<string> visitedAlreadyPartTwo;
    // checking how big the list is I need to print
    for (int nameValue = 0; unsigned(nameValue) < relationScheme.names.size(); nameValue++) {
        if (int((relationScheme.names.at(nameValue)).find("'")) == -1) {
            vector<string>::iterator it = find(visitedAlreadyPartTwo.begin(), visitedAlreadyPartTwo.end(), relationScheme.names.at(nameValue));
            if (it == visitedAlreadyPartTwo.end()) {
                sizePrint++;
            }
        }
        visitedAlreadyPartTwo.push_back(relationScheme.names.at(nameValue));
    }

    for (int nameValue = 0; unsigned(nameValue) < originalScheme.names.size(); nameValue++) {
        if (int((originalScheme.names.at(nameValue)).find("'")) == -1) {
            if (numberOfGoodIterations == 0) {
                out << "  ";
            }
            vector<string>::iterator it = find(visitedAlready.begin(), visitedAlready.end(), originalScheme.names.at(nameValue));
            if (it == visitedAlready.end()) {
                out << relationScheme.names.at(nameValue) << "=" << tuple.values.at(nameValue);
                if (numberOfGoodIterations < sizePrint - 1) {
                    out << ", ";
                }
            }
            numberOfGoodIterations++;
            visitedAlready.push_back(originalScheme.names.at(nameValue));
        }
    }
    return out.str();
}
