//
// Created by hilto on 3/10/2023.
//

#include "Database.h"
#include <string>

Database::Database() { }

void Database::addToCollection(Relation r) {
    (this->collection).push_back(r);
}

// this function retrieves the relation in the database with the same name as the Predicate
Relation Database::getMatchingRelationHelper(Predicate p) {
    for (Relation &relation: collection) {
        if (p.id == relation.name) {
            return relation;
        }
    }
    // return empty relation
    Relation results = Relation();
    return results;
}

int Database::tupleCount() {
    int totalTupleCount = 0;
    for (unsigned int i = 0; i < collection.size(); ++i) {
        for (unsigned int j = 0; j < collection[i].tuples.size(); ++j) {
            totalTupleCount++;
        }
    }

    return totalTupleCount;
}

void Database::unionWithDatabase(Relation r) {
    Database database = *this;
    for (unsigned int i = 0; i < database.collection.size(); ++i) {
        if (database.collection.at(i).name == r.name) {
            for (unsigned int i = 0; i < r.tuples.size(); ++i) {
                set<int>::iterator it = r.tuples.begin();
                advance(it, i);
                //TODO: Fix set at function
                database.collection.at(i).tuples.insert(r.tuples.at(r.tuples.begin(), i));
            }
        }
    }
}
