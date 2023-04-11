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

    out << endl;

    return out.str();
}

Graph Graph::reverseDependencyGraph() {
    Graph newGraph = Graph();
    newGraph.nodes = this->nodes;
    for (auto& newGraphNode: newGraph.nodes) {
        newGraphNode.second.adjacentNodeIDs.clear();
    }
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

void Graph::explore(int ruleNum, Node& node) {
    node.visitedAlready = true;
    for (auto &edge: node.adjacentNodeIDs) {
        for (auto& graphNode: this->nodes) {
            if (graphNode.first == edge) {
                if (!graphNode.second.visitedAlready) {
                    explore(edge, graphNode.second);
                }
            }
        }
    }
    // push rule number to the stack
    postOrder.push(ruleNum);
}

stack<int> Graph::dfs() {
    for (auto &allNode: this->nodes) {
        allNode.second.visitedAlready = false;
    }
    for (auto &node: this->nodes) {
        if (!node.second.visitedAlready) {
            explore(node.first, node.second);
        }
    }

    return postOrder;
}

vector<vector<int>> Graph::dfsForestReversePostOrder(stack<int> postOrderStack) {
    vector<vector<int>> scComponents;
    for (auto &allNode: this->nodes) {
        allNode.second.visitedAlready = false;
    }

    while (!postOrderStack.empty()) {
        vector<int> oneScComponent;
        for (auto &node: this->nodes) {
            if (node.first == postOrderStack.top()) {
                if (!node.second.visitedAlready) {
                    oneScComponent = explorePartTwo(oneScComponent, node.first, node.second);
                    scComponents.push_back(oneScComponent);
                }
            }
        }
        postOrderStack.pop();
    }
    return scComponents;

}

vector<int> Graph::explorePartTwo(vector<int>& oneScComponent, int ruleNum, Node& node) {
    node.visitedAlready = true;
    for (auto &edge: node.adjacentNodeIDs) {
        for (auto& graphNode: this->nodes) {
            if (graphNode.first == edge) {
                if (!graphNode.second.visitedAlready) {
                    oneScComponent = explorePartTwo(oneScComponent, edge, graphNode.second);
                }
            }
        }
    }
    oneScComponent.push_back(ruleNum);
    return oneScComponent;
}
