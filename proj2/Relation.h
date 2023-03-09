//
// Created by hilto on 3/5/2023.
//

#ifndef INC_236_RELATION_H
#define INC_236_RELATION_H
#include <iostream>
#include "Tuple.h"
#include <set>

class Relation {

private:

    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:

    Relation(const string& name, const Scheme& scheme);

    void addTuple(const Tuple& tuple);

    string toString() const;

    Relation select(int index, const string& value) const;
};


#endif //INC_236_RELATION_H
