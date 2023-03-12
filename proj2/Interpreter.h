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

    Relation evaluateQuery(Predicate p);

};


#endif //INC_236_INTERPRETER_H
