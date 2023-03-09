//
// Created by hilto on 3/5/2023.
//

#include "Relation.h"
#include <sstream>
#include<bits/stdc++.h>

Relation::Relation(const string& name, const Scheme& scheme): name(name), scheme(scheme) {
    this->name = name;
    this->scheme = scheme;
};

void Relation::addTuple(const Tuple& tuple) {
    tuples.insert(tuple);
}

string Relation::toString() const {
    stringstream out;
    for (auto& tuple : tuples)
        out << tuple.toString(scheme) << endl;
    return out.str();
}

Relation Relation::select(int index, const string& value) const {
    Relation result(name, scheme);
    for (auto &tuple: tuples) {
        if (tuple.at(index) == value) {
            result.addTuple(tuple);
        }
    }
    return result;
}
