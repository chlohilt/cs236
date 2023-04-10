//
// Created by hilto on 4/3/2023.
//

#include "Graph.h"

Graph::Graph(){}

Graph::Graph(int size) {
    for (int nodeID = 0; nodeID < size; nodeID++)
        nodes[nodeID] = Node();
}

void Graph::addEdge(int fromNodeID, int toNodeID) {
    nodes[fromNodeID].addEdge(toNodeID);
}

string Graph::toString() {
    stringstream out;
    for (auto& pair: nodes) {
        int nodeID = pair.first;
        out << "R" << nodeID << ":";
        Node node = pair.second;
        out << node.toString() << endl;
    }

    return out.str();
}

Graph Graph::reverseDependencyGraph() {
    Graph newGraph = Graph();
    for (auto& node: this->nodes) {
        int nodeID = node.first;
        for (auto &secondIteration: this->nodes) {
            for (auto &secondNodeID: secondIteration.second.adjacentNodeIDs) {
                if (nodeID == secondNodeID) {
                    newGraph.addEdge(nodeID, secondIteration.first);
                }
            }
        }
    }
    return newGraph;

}

void Graph::explore(Node& node) {
    node.visitedAlready = true;
    for (auto &edge: node.adjacentNodeIDs) {
        for (auto& graphNode: this->nodes) {
            if (graphNode.first == edge) {
                if (!graphNode.second.visitedAlready) {
                    cout << "node ID: " << graphNode.first << endl;
                    explore(graphNode.second);
                }
            }
        }
    }
}

void Graph::dfs() {
    for (auto &allNode: this->nodes) {
        allNode.second.visitedAlready = false;
    }
    for (auto &node: this->nodes) {
        if (!node.second.visitedAlready) {
            explore(node.second);
        }
    }
}

void Graph::dfsForest() {

}
