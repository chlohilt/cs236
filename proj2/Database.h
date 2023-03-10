//
// Created by hilto on 3/10/2023.
//

#ifndef INC_236_DATABASE_H
#define INC_236_DATABASE_H
#include "DatalogProgram.h"
#include "Relation.h"

class Database {
private:
    vector<Relation> collection;
public:
    Database();

    void fullEvaluation(DatalogProgram d);

    void evaluateSchemes(vector<Predicate> schemes);

    void addToCollection(Relation r);

    void evaluateFacts(vector<Predicate> facts);

    Relation getMatchingRelationHelper(Predicate fact);

    void evaluateQueries(vector<Predicate> queries);

};


#endif //INC_236_DATABASE_H
