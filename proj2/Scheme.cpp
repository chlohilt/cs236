//
// Created by hilto on 3/4/2023.
//

#include "Scheme.h"

Scheme::Scheme(vector<string> names) : vector<string>(names) {
    this->names = names;
}

Scheme::Scheme() { };

void Scheme::setNames(vector<string> moreNames) {
    this->names = moreNames;
}

string Scheme::getTopName() {
    return this->names.front();
}

