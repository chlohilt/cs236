//
// Created by hilto on 3/11/2023.
//

#ifndef INC_236_INTERPRETER_H
#define INC_236_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"

class Interpreter {
private:
    DatalogProgram datalogProgram;
    Database database;
    Graph graph;

public:
    Interpreter(DatalogProgram datalogProgram);

    void makeSchemeRelations();

    void makeFactRelations();

    void evaluateQueries();

    void evaluateRules();

    Relation evaluateRule(Rule r);

    void printHelper(Relation r);

    Relation evaluatePredicate(Predicate& p);

    Relation evaluateQuery(Predicate& query);

    vector<int> projectHelper(Predicate head, Scheme originalScheme);

    static Graph makeGraph(const vector<Rule>& rules);

};


#endif //INC_236_INTERPRETER_H
