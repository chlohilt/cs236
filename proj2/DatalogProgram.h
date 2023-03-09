//
// Created by hilto on 2/15/2023.
//

#ifndef INC_236_DATALOGPROGRAM_H
#define INC_236_DATALOGPROGRAM_H

#include "Token.h"
#include <set>
#include <vector>
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {
public:
    DatalogProgram();
    void setSchemes(vector<Predicate> Schemes);
    void setFacts(vector<Predicate> Facts);
    void setRules(vector<Rule> Rules);
    void setQueries(vector<Predicate> Queries);
    string toString();
    void setDomain(set<string> domain);

private:
    set<string> domain;
    vector<Predicate> Schemes;
    vector<Predicate> Facts;
    vector<Rule> Rules;
    vector<Predicate> Queries;

};

#endif //INC_236_DATALOGPROGRAM_H
