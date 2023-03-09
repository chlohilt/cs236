#include "DatalogProgram.h"

DatalogProgram::DatalogProgram(){}

void DatalogProgram::setSchemes(vector<Predicate> schemes){
    this->Schemes = schemes;
}

void DatalogProgram::setFacts(vector<Predicate> Facts){
    this->Facts = Facts;
}

void DatalogProgram::setRules(vector<Rule> Rules){
    this->Rules = Rules;
}

void DatalogProgram::setQueries(vector<Predicate> Queries){
    this->Queries = Queries;
}

string DatalogProgram::toString(){

    stringstream ss;
    ss << "Success!" << endl;
    ss << "Schemes(" << Schemes.size() << "):" << endl;
    for (unsigned int i = 0; i < Schemes.size(); ++i) {
        ss << "  " << Schemes[i].toString() << endl;
    }

    ss << "Facts(" << Facts.size() << "):" << endl;
    for (unsigned int i = 0; i <Facts.size(); ++i) {
        ss << "  " << Facts[i].toString() << "." << endl;
    }

    ss << "Rules(" << Rules.size() << "):" <<  endl;
    for (unsigned int i = 0; i < Rules.size(); ++i) {
        ss << "  " << Rules[i].toString() << "." << endl;
    }

    ss << "Queries(" << Queries.size() << "):" <<  endl;
    for (unsigned int i = 0; i < Queries.size(); ++i) {
        ss << "  " << Queries[i].toString() << "?" << endl;
    }

    ss << "Domain(" << domain.size() << "):" <<  endl;
    for (auto it = domain.begin(); it != domain.end(); ++it) {
        ss << "  " << *it << endl;
    }

    string datalog = ss.str();
    return datalog;

}

void DatalogProgram::setDomain(set<string> domain){
    this->domain = domain;
}
