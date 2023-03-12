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
    for (auto relation: collection) {
        if (p.id == relation.name) {
            return relation;
        }
    }
}

