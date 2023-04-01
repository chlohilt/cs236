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

void Relation::newName(const string& name) {
    this->name = name;
}

void Relation::newScheme(Scheme newScheme) {
    this->scheme = scheme;
}

Relation Relation::project2(vector<int> posOfColsForResult) {
    // go through columns and push to a new scheme, create a relation with that scheme
    // then go through columns and tuples and push tuples at that column to the new relation
    // return the relation
    vector<string> values;
    for(unsigned j = 0; j < posOfColsForResult.size(); j++) {
        values.push_back(this->scheme.names.at(posOfColsForResult.at(j)));
    }
    Scheme tempScheme = Scheme(values);
    Relation newRelation = Relation(this->name, tempScheme);

    for (auto& tuple : tuples) {
        vector<string> newValues;
        for (unsigned int i = 0; i < posOfColsForResult.size(); i++){
            newValues.push_back(tuple.at(posOfColsForResult.at(i)));
        }
        Tuple newTuple = Tuple(newValues);
        newRelation.addTuple(newTuple);
    }

    return newRelation;
}

Relation Relation::rename(Scheme newScheme) {
    Relation newRelation = Relation(this->name, newScheme);
    for (auto tuple: this->tuples) {
        newRelation.addTuple(tuple);
    }
    return newRelation;
}

bool Relation::joinable(const Scheme& leftScheme, const Scheme& rightScheme,
                        const Tuple& leftTuple, const Tuple& rightTuple) {
    bool isJoinable = true;
    for (unsigned int i = 0; i < leftScheme.size(); i++) {
        const string& leftName = leftScheme.at(i);
        const string& leftValue = leftTuple.at(i);
        cout << "left name: " << leftName << " value: " << leftValue << endl;
        for (unsigned int j = 0; j < rightScheme.size(); j++) {
            const string& rightName = rightScheme.at(j);
            const string& rightValue = rightTuple.at(j);
            cout << "right name: " << rightName << " value: " << rightValue << endl;
            if (rightName == leftName && rightValue != leftValue) {
                isJoinable = false;
            }
        }
    }

    return isJoinable;
}

Relation Relation::join(const Relation& right) {
    const Relation& left = *this;
    Scheme combinedScheme = combineSchemes(left, right);
    Relation result = Relation(combinedScheme.getTopName(), combinedScheme);

    for (const Tuple& leftTuple : left.tuples) {
        for (const Tuple& rightTuple : right.tuples) {
            if (joinable(left.scheme, right.scheme, leftTuple, rightTuple)) {
                Tuple newTuple = combineTuples(leftTuple, rightTuple);
                result.addTuple(newTuple);
            }
        }
    }

    return result;
}

Scheme Relation::combineSchemes(Relation left, Relation right) {
    vector<string> newNames;
    for (auto leftScheme: left.scheme) {
        newNames.push_back(leftScheme);
    }
    for (auto rightScheme: right.scheme) {
        newNames.push_back(rightScheme);
    }
    Scheme newScheme = Scheme(newNames);
    return newScheme;
}

Tuple Relation::combineTuples(Tuple left, Tuple right) {
    vector<string> newValues;
    for (auto leftValue: left.values) {
        newValues.push_back(leftValue);
    }
    for (auto rightValue: right.values) {
        newValues.push_back(rightValue);
    }
    Tuple newTuple = Tuple(newValues);
    return newTuple;
}