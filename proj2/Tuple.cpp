//
// Created by hilto on 3/4/2023.
//

#include "Tuple.h"
#include <sstream>
#include <algorithm>

Tuple::Tuple(vector<string> values) : vector<string>(values) {
    this->values = values;
}

string Tuple::toString(const Scheme& scheme) const {
    const Tuple& tuple = *this;
    stringstream out;
    vector<string> visitedAlready;
    vector<string> schemeNonConstants;
    int numberOfGoodIterations = 0;
    // counting how many are constants
    for (int nameValue = 0; unsigned(nameValue) < scheme.names.size(); nameValue++) {
        if (int((scheme.names.at(nameValue)).find("'")) == -1) {
            schemeNonConstants.push_back(scheme.names.at(nameValue));
        }
    }
    int sizePrint = 0;
    vector<string> visitedAlreadyPartTwo;
    // checking how big the list is I need to print
    for (int nameValue = 0; unsigned(nameValue) < scheme.names.size(); nameValue++) {
        if (int((scheme.names.at(nameValue)).find("'")) == -1) {
            vector<string>::iterator it = find(visitedAlreadyPartTwo.begin(), visitedAlreadyPartTwo.end(), scheme.names.at(nameValue));
            if (it == visitedAlreadyPartTwo.end()) {
                sizePrint++;
            }
        }
        visitedAlreadyPartTwo.push_back(scheme.names.at(nameValue));
    }

    for (int nameValue = 0; unsigned(nameValue) < scheme.names.size(); nameValue++) {
        if (int((scheme.names.at(nameValue)).find("'")) == -1) {
            if (numberOfGoodIterations == 0) {
                out << "  ";
            }
            vector<string>::iterator it = find(visitedAlready.begin(), visitedAlready.end(), scheme.names.at(nameValue));
            if (it == visitedAlready.end()) {
                out << scheme.names.at(nameValue) << "=" << tuple.values.at(nameValue);
                if (numberOfGoodIterations < sizePrint - 1) {
                    out << ", ";
                }

            }
            numberOfGoodIterations++;
            visitedAlready.push_back(scheme.names.at(nameValue));
        }
    }

    return out.str();
}

string Tuple::toStringPartTwo(const Scheme& originalScheme, const Scheme& relationScheme, const Scheme& headScheme) {
    const Tuple& tuple = *this;
    stringstream out;
    vector<string> visitedAlready;
    vector<string> schemeNonConstants;
    int numberOfGoodIterations = 0;
    // counting how many are constants
    for (int nameValue = 0; unsigned(nameValue) < originalScheme.names.size(); nameValue++) {
        if (int((originalScheme.names.at(nameValue)).find("'")) == -1) {
            schemeNonConstants.push_back(originalScheme.names.at(nameValue));
        }
    }
    int sizePrint = 0;
    vector<string> visitedAlreadyPartTwo;
    // checking how big the list is I need to print
    for (int nameValue = 0; unsigned(nameValue) < relationScheme.names.size(); nameValue++) {
        if (int((relationScheme.names.at(nameValue)).find("'")) == -1) {
            vector<string>::iterator it = find(visitedAlreadyPartTwo.begin(), visitedAlreadyPartTwo.end(), originalScheme.names.at(nameValue));
            if (it == visitedAlreadyPartTwo.end()) {
                sizePrint++;
            }
        }
        visitedAlreadyPartTwo.push_back(relationScheme.names.at(nameValue));
    }

    for (int nameValue = 0; unsigned(nameValue) < originalScheme.names.size(); nameValue++) {
        if (int((originalScheme.names.at(nameValue)).find("'")) == -1) {
            if (numberOfGoodIterations == 0) {
                out << "  ";
            }
            vector<string>::iterator it = find(visitedAlready.begin(), visitedAlready.end(), originalScheme.names.at(nameValue));
            // not already visited, original scheme spot matches relation scheme
            vector<string> schemesVisited;
            for (unsigned int i = 0; i < relationScheme.names.size(); i++) {
                // find what index the tuple is in the original one
                for (unsigned int k = 0; k < originalScheme.names.size(); ++k) {
                    for (unsigned int j = 0; j < headScheme.names.size(); ++j) {
                        if (originalScheme.names.at(k) == headScheme.names.at(j)) {
                            if (it == visitedAlready.end() &&
                                originalScheme.names.at(nameValue) == relationScheme.names.at(i) &&
                                find(schemesVisited.begin(), schemesVisited.end(), originalScheme.names.at(nameValue)) != originalScheme.end()) {
                                out << originalScheme.names.at(nameValue) << "=" << tuple.values.at(k);
                                schemesVisited.push_back(originalScheme.names.at(nameValue));
                                if (numberOfGoodIterations < sizePrint - 1) {
                                    out << ", ";
                                }
                            }
                        }
                    }
                }

                numberOfGoodIterations++;
            }
            visitedAlready.push_back(originalScheme.names.at(nameValue));
        }
    }

    return out.str();
}
