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
    vector<string> schemeNames;
    // go through Predicates and create Relation from those
    for (auto s: datalogProgram.Schemes) {
        Scheme newScheme;
        // have to loop through each Predicate's parameters to set up scheme
        for (auto p: s.parameters) {
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
    for (auto f: datalogProgram.Facts) {
        vector<string> factValues;
        Relation relationToAddTuple = database.getMatchingRelationHelper(f);
        // have to loop through each Predicate's parameters to set up fact
        for (auto p: f.parameters) {
            if (p.stringName.length() != 0) {
                factValues.push_back(p.stringName);
            }
            else {
                factValues.push_back(p.idName);
            }
        }

        Tuple toAddTuple = Tuple(factValues);
        // TODO: Might need to go through database and delete the original and replace
        //it with the one with tuples
        relationToAddTuple.addTuple(toAddTuple);
    }
}

void Interpreter::evaluateQueries() {
    for (auto query: datalogProgram.Queries) {
        cout << query.toString() << "? ";
        Relation r = evaluateQuery(query);
        if (r.tuples.size() == 0) {
            cout << "No" << endl;
        }
        else {
            cout << "Yes" << endl;
        }
    }
}

Relation Interpreter::evaluateQuery(Predicate query) {
    vector<Relation> afterSelection;

    //Get Relation from Database with same name as predicate name in query
    Relation r = database.getMatchingRelationHelper(query);

    // use select ops to select tuples from Relation that match the query
    map<string, vector<int>> variablePositions;
    int index = 0;
    //bool matchesRelation;

    // SELECTION
    for (auto parameter: query.parameters) {

        // is a constant
        if (parameter.isConstant) {
            afterSelection.push_back(r.selectConstant(index, parameter.stringName));
        }
        // is a variable
        else {
            // if the variable is already in the map
            if (variablePositions.count(parameter.stringName)) {
                // add the parameter index to the map then loop through map
                // select when it's equal
                (variablePositions[parameter.stringName]).push_back(index);
                for (auto mapItem: variablePositions) {
                    for (auto j: mapItem.second) {
                        for (auto i: mapItem.second) {
                            r.selectEqual(j, i);
                            r.project(mapItem.second);
                            r.project(mapItem.second);
                            //afterSelectEqual.rename();
                        }
                    }
                }
            }
            else {
                vector<int> positions;
                positions.push_back(index);
                variablePositions.insert({parameter.stringName, positions});
            }
        }
        index++;
    }

/*    for (auto v: variablePositions) {
        r.project(v);
        r.rename(v);
    }*/


    // PROJECTION
    return r;

}
