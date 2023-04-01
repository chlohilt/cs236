//
// Created by hilto on 3/11/2023.
//

#include "Interpreter.h"
#include <map>

Interpreter::Interpreter(DatalogProgram datalogProgram) {
    this->datalogProgram = datalogProgram;
    // create empty database
    makeSchemeRelations();
    makeFactRelations();
    cout << "Rule Evaluation" << endl;
    evaluateRules();
    cout << "Query Evaluation" << endl;
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

void Interpreter::evaluateRules() {
    int totalTuples;
    int newTotalTuples;
    int passesThrough = 0;
    do {
        totalTuples = this->database.tupleCount();
        for (unsigned int i = 0; i < this->datalogProgram.Rules.size(); ++i) {
            cout << this->datalogProgram.Rules[i].toString() << "." << endl;
            evaluateRule(this->datalogProgram.Rules[i]);
        }
        passesThrough++;
        newTotalTuples = this->database.tupleCount();
    } while (totalTuples != newTotalTuples);

    cout << endl << "Schemes populated after " << passesThrough << " passes through the Rules." << endl << endl;
}

Relation Interpreter::evaluateRule(Rule r) {
    Relation result;
    vector<Relation> joinRelations;
    for (unsigned int i = 0; i < r.predicates.size(); ++i) {
        // skip first one since it's on the left hand side of the rule
        // then evaluate same way as queries
        if (i != 0 && r.predicates.size() == 2) {
            result = evaluatePredicate(r.predicates[i]);
        }
        else if (i != 0 && r.predicates.size() > 2) {
            result = evaluatePredicate(r.predicates[i]);
            joinRelations.push_back(result);
        }
    }
// join the result relations if there is more than one
    bool oneJoinDone = false;
    while (!joinRelations.empty()){
        for (unsigned int i = 0; i < joinRelations.size(); ++i) {
            // first combine the first two result relations
            if (!oneJoinDone) {
                result = joinRelations.at(i).join(joinRelations.at(i + 1));
                joinRelations.erase(joinRelations.begin());
                joinRelations.erase(joinRelations.begin());
                oneJoinDone = true;
            }
                // then combine result from that join with every other relation
            else {
                result = result.join(joinRelations.at(i));
                joinRelations.erase(joinRelations.begin() + i);
            }
        }
    }
    // pass in head predicate to get columns needed
    vector<int> headColumnsToProject = projectHelper(r.predicates[0], result.scheme);
    Scheme originalScheme = result.scheme;
    // project, rename, union
    result = result.project2(headColumnsToProject);
    Relation matchesHead = database.getMatchingRelationHelper(r.predicates[0]);
    // rename scheme and rename the actual name
    result = result.rename(matchesHead.scheme);
    result.name = matchesHead.name;
    database.unionWithDatabase(result, originalScheme, r.predicates[0]);
    return result;
}

vector<int> Interpreter::projectHelper(Predicate head, Scheme scheme) {
    vector<int> headColumnsToProject;
    vector<string> schemeWithoutConstants;
    // need to strip out the constants
    for (auto schemeName: scheme.names) {
        vector<string>::iterator itr = find(schemeWithoutConstants.begin(), schemeWithoutConstants.end(), schemeName);
        if (int(schemeName.find("'")) == -1 && itr == schemeWithoutConstants.end()) {
            schemeWithoutConstants.push_back(schemeName);
        }
    }
    for (auto parameter: head.parameters){
        for (unsigned int i = 0; i < schemeWithoutConstants.size(); ++i) {
            if (schemeWithoutConstants.at(i) == parameter.idName) {
                headColumnsToProject.push_back(i);
            }
        }
    }

    return headColumnsToProject;
}

Relation Interpreter::evaluateQuery(Predicate& query) {
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
            seenBefore = false;
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
    }
    r = r.project2(newColNames);
    Scheme newScheme = Scheme(newSchemeNames);
    r = r.rename(newScheme);
    printHelper(r);

    return r;

}

Relation Interpreter::evaluatePredicate(Predicate& p) {
    //Get Relation from Database with same name as predicate name in query
    Relation r = database.getMatchingRelationHelper(p);

    map<string, unsigned int> variablePositions;
    bool seenBefore = false;
    // make vector for indexes where variables were first seen
    vector<int> newColNames;
    // vector to rename columns to same as query variables
    vector<string> newSchemeNames;

    for (unsigned int i = 0; i < p.parameters.size(); i++) {
        // for constants
        if (p.parameters[i].isConstant) {
            r = r.selectConstant(i, p.parameters[i].stringName);
            newSchemeNames.push_back(p.parameters[i].stringName);
        }
            // for variables
        else {
            seenBefore = false;
            // check if we've seen it before
            for (auto mapItem: variablePositions) {
                if (p.parameters[i].idName == mapItem.first){
                    seenBefore = true;
                    r = r.selectEqual(i, mapItem.second);
                    newSchemeNames.push_back(p.parameters[i].idName);
                }
            }

            if (!seenBefore) {
                variablePositions.insert({(p.parameters[i].idName), i});
                newColNames.push_back(i);
                newSchemeNames.push_back(p.parameters[i].idName);
            }
        }
        // to account for new column names pass in the head predicate that has the scheme needed or what?
    }
    r = r.project2(newColNames);
    Scheme newScheme = Scheme(newSchemeNames);
    r = r.rename(newScheme);

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
