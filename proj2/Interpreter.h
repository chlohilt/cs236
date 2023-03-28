//
// Created by hilto on 3/11/2023.
//

#ifndef INC_236_INTERPRETER_H
#define INC_236_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"


class Interpreter {
private:
    DatalogProgram datalogProgram;
    Database database;

public:
    Interpreter(DatalogProgram datalogProgram);

    void makeSchemeRelations();

    void makeFactRelations();

    void evaluateQueries();

    void evaluateRules();

    Relation evaluateRule(Rule r);

    void printHelper(Relation r);

    Relation evaluatePredicate(Predicate& p);

    vector<int> projectHelper(Predicate head);

};


#endif //INC_236_INTERPRETER_H
