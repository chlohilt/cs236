#include <iostream>
#include <string>
#include <vector>
#include "Scheme.h"
#pragma once
using namespace std;
class Tuple : public vector<string> {
private:
    vector<string> values;

public:

    Tuple(vector<string> values);

    string toString(const Scheme& scheme) const;

    friend class Relation;

};
