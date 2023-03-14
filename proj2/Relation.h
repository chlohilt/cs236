//
// Created by hilto on 3/5/2023.
//

#ifndef INC_236_RELATION_H
#define INC_236_RELATION_H
#include <iostream>
#include "Tuple.h"
#include <set>
#include <ostream>

class Relation {

private:

    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:

    Relation(const string& name, const Scheme& scheme);

    Relation();

    void addTuple(const Tuple& tuple);

    string toString() const;

    Relation selectConstant(int index, const string& value) const;

    Relation project(vector<int> posOfColsForResult);

    Relation selectEqual(int position1, int position2);

    Relation rename(Scheme newScheme);

    friend class Database;

    friend class Interpreter;
};


#endif //INC_236_RELATION_H
