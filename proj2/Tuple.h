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

    string toString(const Scheme& scheme) const;

    string toStringPartTwo(const Scheme& originalScheme, const Scheme& relationScheme, const Scheme& headScheme);

    friend class Relation;

    friend class Interpreter;

};
