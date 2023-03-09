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
    for (int nameValue = 0; nameValue < scheme.names.size(); nameValue++) {
        out << scheme.at(nameValue) << "=" << tuple.values.at(nameValue);
            if (nameValue != tuple.values.size() - 1) {
                out << ", ";
            }
            else {
                out << " ";
            }
        }

    return out.str();
}