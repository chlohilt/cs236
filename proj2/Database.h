//
// Created by hilto on 3/10/2023.
//

#ifndef INC_236_DATABASE_H
#define INC_236_DATABASE_H
#include "DatalogProgram.h"
#include "Relation.h"
using namespace std;

class Database {
private:
    vector<Relation> collection;
public:
    Database();

    void fullEvaluation(DatalogProgram d);

    void addToCollection(Relation r);

    Relation getMatchingRelationHelper(Predicate fact);

    void evaluateQueries(vector<Predicate> queries);

    int tupleCount();

    void unionWithDatabase(Relation r);

    friend class Interpreter;

};


#endif //INC_236_DATABASE_H
