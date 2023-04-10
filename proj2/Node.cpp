//
// Created by hilto on 4/3/2023.
//

#include "Node.h"

void Node::addEdge(int adjacentNodeID) {
    adjacentNodeIDs.insert(adjacentNodeID);
}

string Node::toString() {
    unsigned int i = 0;
    stringstream out;
    for (auto& nodeID : adjacentNodeIDs) {
        if (i != adjacentNodeIDs.size() - 1) {
            out << "R" << nodeID << ",";
        } else {
            out << "R" << nodeID;
        }
        ++i;
    }
    return out.str();
}
