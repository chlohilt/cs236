//
// Created by hilto on 3/4/2023.
//

#include "Tuple.h"
#include <sstream>

Tuple::Tuple(vector<string> values) : vector<string>(values) {
    this->values = values;
}

string Tuple::toString(const Scheme& scheme) const {
    const Tuple& tuple = *this;
    stringstream out;
    vector<int> visitedAlready;
    vector<string> schemeNonConstants;
    // counting how many are constants
    for (unsigned int nameValue = 0; nameValue < scheme.names.size(); nameValue++) {
        if ((scheme.names.at(nameValue)).find("'") == -1) {
            schemeNonConstants.push_back(scheme.names.at(nameValue));
        }
    }
    for (unsigned int nameValue = 0; nameValue < scheme.names.size(); nameValue++) {
        if ((scheme.names.at(nameValue)).find("'") == -1) {
            visitedAlready.push_back(nameValue);
            if (visitedAlready.size() == 1) {
                out << "  ";
            }
            out << scheme.names.at(nameValue) << "=" << tuple.values.at(nameValue);
            if (scheme.names.at(nameValue) != schemeNonConstants.at(schemeNonConstants.size() - 1)) {
                out << ", ";
            }
        }
    }

    return out.str();
}