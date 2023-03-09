#include <vector>
#include <iostream>
#include <string>
#pragma once
using namespace std;
class Scheme : public vector<string> {

private:

    vector<string> names;

public:

    Scheme(vector<string> names);
    // TODO: add more delegation functions as needed

    friend class Tuple;

};
