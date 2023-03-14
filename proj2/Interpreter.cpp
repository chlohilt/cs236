//
// Created by hilto on 3/11/2023.
//

#include "Interpreter.h"
#include <map>

Interpreter::Interpreter(DatalogProgram datalogProgram) {
    this->datalogProgram = datalogProgram;
    // create empty database
    Database d = Database();
    this->database = d;
    makeSchemeRelations();
    makeFactRelations();
    evaluateQueries();
}

void Interpreter::makeSchemeRelations() {
    // go through Predicates and create Relation from those
    for (auto &s: datalogProgram.Schemes) {
        Scheme newScheme;
        // have to loop through each Predicate's parameters to set up scheme
        vector<string> schemeNames;
        for (auto &p: s.parameters) {
            if (p.stringName.length() != 0) {
                schemeNames.push_back(p.stringName);
            }
            else {
                schemeNames.push_back(p.idName);
            }
        }
        newScheme.setNames(schemeNames);
        Relation r = Relation(s.id, newScheme);
        database.addToCollection(r);

    }
}

void Interpreter::makeFactRelations() {
    // loop through facts in Datalog and check which fact matches a relation in the database
    for (auto &f: datalogProgram.Facts) {
        vector<string> factValues;
        Relation relationToAddTuple = database.getMatchingRelationHelper(f);
        // have to loop through each Predicate's parameters to set up fact
        for (auto &p: f.parameters) {
            if (p.stringName.length() != 0) {
                factValues.push_back(p.stringName);
            }
            else {
                factValues.push_back(p.idName);
            }
        }

        Tuple toAddTuple = Tuple(factValues);
        relationToAddTuple.addTuple(toAddTuple);
        for (Relation &relation: database.collection) {
            if (relation.name == relationToAddTuple.name) {
                relation = relationToAddTuple;
            }
        }
    }
}

void Interpreter::evaluateQueries() {
    for (auto &query: datalogProgram.Queries) {
        cout << query.toString() << "? ";
        Relation r = evaluateQuery(query);
    }
}


Relation Interpreter::evaluateQuery(Predicate query) {
    //Get Relation from Database with same name as predicate name in query
    Relation r = database.getMatchingRelationHelper(query);

    map<string, unsigned int> variablePositions;
    bool seenBefore = false;
    // make vector for indexes where variables were first seen
    vector<int> newColNames;
    // vector to rename columns to same as query variables
    vector<string> newSchemeNames;

    for (unsigned int i = 0; i < query.parameters.size(); i++) {
        // for constants
        if (query.parameters[i].isConstant) {
            r = r.selectConstant(i, query.parameters[i].stringName);
            newSchemeNames.push_back(query.parameters[i].stringName);
        }
        // for variables
        else {
            // check if we've seen it before
            for (auto mapItem: variablePositions) {
                if (query.parameters[i].idName == mapItem.first){
                    seenBefore = true;
                    r = r.selectEqual(i, mapItem.second);
                    newSchemeNames.push_back(query.parameters[i].idName);
                }
            }

            if (!seenBefore) {
                variablePositions.insert({(query.parameters[i].idName), i});
                newColNames.push_back(i);
                newSchemeNames.push_back(query.parameters[i].idName);
            }
        }

        r = r.project(newColNames);
        Scheme newScheme = Scheme(newSchemeNames);
        r = r.rename(newScheme);

    }

    // printing
    if (r.tuples.size() == 0) {
        cout << "No" << endl;
    } else {
        cout << "Yes(" << r.tuples.size() << ")" << endl;
        cout << r.toString();
    }

    return r;

}

void Interpreter::printHelper(Relation r) {
    if (r.tuples.size() == 0) {
        cout << "No" << endl;
    } else {
        cout << "Yes(" << r.tuples.size() << ")" << endl;
        // if query has a variable, print out those values
        // only print those with variables
        cout << r.toString();
    }
}
