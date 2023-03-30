#include <vector>
#include <iostream>
#include <string>
#pragma once
using namespace std;
class Scheme : public vector<string> {

private:

    vector<string> names;

public:
    Scheme();

    Scheme(vector<string> names);

    void addName(string name);

    void setNames(vector<string> moreNames);

    string getTopName();

    friend class Tuple;

    friend class Database;

    friend class Interpreter;

    friend class Relation;

};
