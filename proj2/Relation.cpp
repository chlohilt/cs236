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

Relation::Relation() {

}


void Relation::addTuple(const Tuple& tuple) {
    tuples.insert(tuple);
    this->tuples = tuples;
}

string Relation::toString() const {
    stringstream out;
    for (auto& tuple : tuples)
        out << tuple.toString(this->scheme) << endl;
    return out.str();
}

// select that finds the tuples with a constant value in a certain column
Relation Relation::selectConstant(int index, const string& value) const {
    Relation result(name, scheme);
    for (auto &tuple: tuples) {
        if (tuple.at(index) == value) {
            result.addTuple(tuple);
        }
    }
    return result;
}

// this select finds all the tuples that have the same value in two different columns
Relation Relation::selectEqual(int position1, int position2) {
    Relation results(name,scheme);
    for (auto &tuple: this->tuples) {
        if (tuple.at(position1) == tuple.at(position2)) {
            results.addTuple(tuple);
        }
    }
    return results;
}

Relation Relation::project(vector<int> posOfColsForResult) {
    int index = 0;
    vector<string> values;
    for (auto tuple: tuples) {
        // this part uses the tuples values to set the schemes values
        // Idk if this part is right
        for (auto tValues: tuple.values) {
            values.push_back(tValues);
        }

        for (auto p: posOfColsForResult) {
            if (index == p) {
                this->addTuple(tuple);
            }
        }
    }
    return *this;
}

Relation Relation::rename(Scheme newScheme) {
    this->scheme = newScheme;
    return *this;
}