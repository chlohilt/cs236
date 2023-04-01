#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Scheme.h"
#pragma once
using namespace std;
class Tuple : public vector<string> {
private:
    vector<string> values;

public:

    Tuple(vector<string> values);

    Tuple();

    void addValue(string value);

    string toString(const Scheme& scheme) const;

    string toStringPartTwo(const Scheme& originalScheme, const Scheme& relationScheme);

    friend class Relation;

    friend class Interpreter;

};
