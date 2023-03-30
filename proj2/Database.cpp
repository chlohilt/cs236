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

void Database::unionWithDatabase(Relation r, Scheme originalScheme, Predicate head) {
    vector<string> printedBefore;
    bool printedBeforeBool = false;
    vector<string> schemeValues;
    for (unsigned int i = 0; i < head.parameters.size(); ++i) {
        schemeValues.push_back(head.parameters.at(i).idName);
    }
    Scheme headScheme = Scheme(schemeValues);

    for (unsigned int i = 0; i < this->collection.size(); ++i) {
        if (this->collection.at(i).name == r.name) {
            for (auto itr: r.tuples) {
                if (this->collection.at(i).tuples.insert(itr).second) {
                    for (unsigned int i = 0; i < printedBefore.size(); ++i) {
                        if (itr.toStringPartTwo(originalScheme, r.scheme, headScheme) == printedBefore.at(i)) {
                            printedBeforeBool = true;
                        } else {
                            printedBeforeBool = false;
                        }
                    }
                    if (!printedBeforeBool) {
                        cout << itr.toStringPartTwo(originalScheme, r.scheme, headScheme) << endl;
                        printedBefore.push_back(itr.toStringPartTwo(originalScheme, r.scheme, headScheme));
                    }
                }
            }
        }
    }
}
