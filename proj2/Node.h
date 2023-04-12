//
// Created by hilto on 4/3/2023.
//

#ifndef INC_236_NODE_H
#define INC_236_NODE_H
using namespace std;
#include <set>
#include <iostream>
#include <sstream>

class Node {

private:

    set<int> adjacentNodeIDs;
    int postOrderNumber;
    bool visitedAlready;

public:

    void addEdge(int adjacentNodeID);

    string toString();

    friend class Graph;

    friend class Interpreter;

};

#endif //INC_236_NODE_H
