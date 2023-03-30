#pragma once
#include "Token.h"
#include "DatalogProgram.h"
#include <queue>
#include <vector>

class Parser {
private:
    queue<Token> tokens;
public:
    Parser(const queue<Token>& tokens);

    TokenType tokenType() const;

    void advanceToken();

    void throwError();

    void match(TokenType t);

    void idList(vector<Parameter> &idList);

    void stringList(vector<Parameter> &myStringList);

    void schemeList(vector<Predicate> &schemes);

    void factList(vector<Predicate> &facts);

    void ruleList(vector<Rule> &rules);

    void queryList(vector<Predicate> &queries);

    Predicate scheme();

    Predicate query();

    Predicate fact();

    Predicate predicate();

    Rule rule();

    Predicate headPredicate(Rule r);

    Parameter parameter();

    void predicateList(vector<Predicate> &predicates);

    void parameterList(vector<Parameter> &currParamList);

    DatalogProgram datalogProgram();

};