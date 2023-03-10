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

    void setNames(vector<string> moreNames);

    friend class Tuple;
    friend class Database;

};
