#include "Parser.h"
#include "Predicate.h"
#include <stdexcept>

Parser::Parser(const queue<Token> &tokens) : tokens(tokens) {

}

TokenType Parser::tokenType() const {
    return (tokens.front()).type;
}

void Parser::advanceToken() {
    tokens.pop();
}

void Parser::match(TokenType t) {
    if ((tokens.front()).type == t) {
        advanceToken();
    }
    else {
        throw tokens.front();
    }
}

void Parser::throwError() {
    cout << "Syntax error!" << endl;
    throw 1;
}

void Parser::idList(vector<Parameter> &myIdList) {
    if (tokenType() == COMMA) {
        match(COMMA);
        Parameter p = Parameter();
        p.setId(tokens.front().value);
        myIdList.push_back(p);
        match(ID);
        idList(myIdList);
    } else {
        // lambda
    }
}

void Parser::stringList(vector<Parameter> &myStringList) {
    if (tokenType() == COMMA) {
        match(COMMA);
        Parameter p = Parameter();
        p.setString(tokens.front().value);
        myStringList.push_back(p);
        match(STRING);
        stringList(myStringList);
    } else {
        // lambda
    }
}

void Parser::schemeList(vector<Predicate> &schemes) {
    if (tokenType() == ID) {
        schemes.push_back(scheme());
        schemeList(schemes);
    } else {
        // lambda
    }
}

void Parser::factList(vector<Predicate> &facts) {
    if (tokenType() == ID) {
        facts.push_back(fact());
        factList(facts);
    } else {
        // lambda
    }
}

void Parser::ruleList(vector<Rule> &rules) {
    if (tokenType() == ID) {
        rules.push_back(rule());
        ruleList(rules);
    } else {
        // lambda
    }
}

void Parser::queryList(vector<Predicate> &queries) {
    if (tokenType() == ID) {
        queries.push_back(query());
        queryList(queries);
    } else {
        // lambda
    }
}

void Parser::predicateList(vector<Predicate> &predicates) {
    if (tokenType() == COMMA) {
        match(COMMA);
        predicates.push_back(predicate());
        predicateList(predicates);
    } else {
        // lambda
    }
}

Predicate Parser::scheme() {
    if (tokenType() == ID) {
        Predicate p = Predicate();
        p.setId(tokens.front().value);
        match(ID);
        match(LEFT_PAREN);
        vector<Parameter> myIdList;
        Parameter par = Parameter();
        par.setId(tokens.front().value);
        myIdList.push_back(par);
        match(ID);
        idList(myIdList);
        p.setParameters(myIdList);
        match(RIGHT_PAREN);
        return p;
    } else {
        throw tokens.front();
    }
}

Predicate Parser::query() {
    if (tokenType() == ID) {
        Predicate p = predicate();
        match(Q_MARK);
        return p;
    } else {
        throw tokens.front();
    }
}

Predicate Parser::fact() {
    if (tokenType() == ID) {
        Predicate p = Predicate();
        p.setId(tokens.front().value);
        match(ID);
        match(LEFT_PAREN);
        vector<Parameter> myStringList;
        Parameter par = Parameter();
        par.setString(tokens.front().value);
        myStringList.push_back(par);
        match(STRING);
        stringList(myStringList);
        p.setParameters(myStringList);
        match(RIGHT_PAREN);
        match(PERIOD);
        return p;
    } else {
        throw tokens.front();
    }
}

Predicate Parser::predicate() {
    if (tokenType() == ID) {
        Predicate pre = Predicate();
        pre.setId(tokens.front().value);
        match(ID);
        match(LEFT_PAREN);
        vector<Parameter> parameters;
        parameters.push_back(parameter());
        parameterList(parameters);
        pre.setParameters(parameters);
        match(RIGHT_PAREN);
        return pre;
    } else {
        throw tokens.front();
    }
}

Rule Parser::rule() {
    if (tokenType() == ID) {
        Rule r = Rule();
        vector<Predicate> predicates;
        predicates.push_back(headPredicate(r));
        //head pred not pushing all params
        match(COLON_DASH);
        predicates.push_back(predicate());
        predicateList(predicates);
        r.setPredicates(predicates);
        match(PERIOD);
        return r;
    } else {
        throw tokens.front();
    }
}

Parameter Parser::parameter() {
    if (tokenType() == STRING) {
        Parameter p = Parameter();
        p.setString(tokens.front().value);
        match(STRING);
        return p;
    } else if (tokenType() == ID) {
        Parameter p = Parameter();
        p.setId(tokens.front().value);
        match(ID);
        return p;
    }
    else {
        throw tokens.front();
    }
}

Predicate Parser::headPredicate(Rule r) {
    if (tokenType() == ID) {
        Predicate p = Predicate();
        p.setId(tokens.front().value);
        match(ID);
        match(LEFT_PAREN);
        vector<Parameter> myIdList;
        Parameter firstId = Parameter();
        firstId.setId(tokens.front().value);
        myIdList.push_back(firstId);
        match(ID);
        idList(myIdList);
        match(RIGHT_PAREN);
        p.setParameters(myIdList);
        return p;
    } else {
        throw tokens.front();
    }
}

void Parser::parameterList(vector<Parameter> &currParamList) { // pass the current vector by reference
// also return the parameter for parameter function
    if (tokenType() == COMMA) {
        match(COMMA);
        currParamList.push_back(parameter());
        parameterList(currParamList);
    }
    else {
        // lambda
    }
}

DatalogProgram Parser::datalogProgram() {
    DatalogProgram d = DatalogProgram();
    try {
        // SCHEMES
        match(SCHEMES);
        match(COLON);
        vector<Predicate> schemes;
        schemes.push_back(scheme());
        schemeList(schemes);
        d.setSchemes(schemes);
        // FACTS
        match(FACTS);
        match(COLON);
        vector<Predicate> facts;
        factList(facts);
        match(RULES);
        match(COLON);
        d.setFacts(facts);
        set<string> domain;
        for (unsigned int i = 0; i < facts.size(); ++i) {
            for (unsigned int j = 0; j < facts.at(i).parameters.size(); ++j) {
                domain.insert(facts.at(i).parameters.at(j).stringName);
            }
        }
        d.setDomain(domain);
        // RULES
        vector<Rule> rules;
        ruleList(rules);
        d.setRules(rules);
        // QUERIES
        vector<Predicate> queries;
        match(QUERIES);
        match(COLON);
        queries.push_back(query());
        queryList(queries);
        match(EOF1);
        d.setQueries(queries);
        //cout << d.toString();
        return d;
    } catch(Token t) {
        throw tokens.front();
    }

}

