//
// Created by hilto on 3/10/2023.
//

#include "Database.h"
#include <string>
#include <map>

Database::Database() { }

void Database::fullEvaluation(DatalogProgram d){
    this->evaluateSchemes(d.Schemes);
    this->evaluateFacts(d.Facts);
}

void Database::evaluateSchemes(vector<Predicate> schemes) {
    vector<string> schemeNames;
    // go through Predicates and create Relation from those
    for (auto s: schemes) {
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
        this->addToCollection(r);

    }
}

void Database::addToCollection(Relation r) {
    (this->collection).push_back(r);
}

void Database::evaluateFacts(vector<Predicate> facts) {
    // loop through facts in Datalog and check which fact matches a relation in the database
    for (auto f: facts) {
        vector<string> factValues;
        Relation relationToAddTuple = getMatchingRelationHelper(f);
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
        relationToAddTuple.addTuple(toAddTuple);
    }
}

// this function retrieves the relation in the database with the same name as the Predicate
Relation Database::getMatchingRelationHelper(Predicate p) {
    for (auto relation: collection) {
        if (p.id == relation.name) {
            return relation;
        }
    }
}

void Database::evaluateQueries(vector<Predicate> queries) {
    vector<Relation> afterSelection;
    for (auto query: queries) {
        query.toString();

        //Get Relation from Database with same name as predicate name in query
        Relation r = getMatchingRelationHelper(query);

        // use select ops to select tuples from Relation that match the query
        map<string, vector<int>> variablePositions;
        int index = 0;
        //bool matchesRelation;

        // SELECTION
        for (auto parameter: query.parameters) {

            // is a constant
            if (parameter.stringName.find("'") != -1) {
                afterSelection.push_back(r.selectConstant(index, parameter.stringName));
            }
            // is a variable
            else {
                // if the variable is already in the map
                if (variablePositions.count(parameter.stringName)) {
                    (variablePositions[parameter.stringName]).push_back(index);
                }
                else {
                    vector<int> positions;
                    positions.push_back(index);
                    variablePositions.insert({parameter.stringName, positions});
                }
            }
            index++;
        }

        // checks which one match variable positions
        if (!variablePositions.empty()) {
            for (auto m: variablePositions) {
                for (auto j: m.second) {
                    for (auto i: m.second) {
                        r.selectEqual(j, i);
                    }
                }
            }
        }
    }

    // PROJECTION

}
