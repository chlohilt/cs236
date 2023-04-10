//
// Created by hilto on 4/3/2023.
//

#ifndef INC_236_GRAPH_H
#define INC_236_GRAPH_H
#include "Node.h"
#include <map>
#include "Rule.h"
#include <stack>

class Graph {

private:

    map<int,Node> nodes;

    stack<int> postOrder;

public:

    Graph();

    Graph(int size);

    void addEdge(int fromNodeID, int toNodeID);

    string toString();

    Graph reverseDependencyGraph();

    stack<int> dfs();

    void explore(int ruleNum, Node& node);

    vector<vector<int>> dfsForestReversePostOrder(stack<int> postOrderStack);

    vector<int> explorePartTwo(vector<int>& oneScComponent, int ruleNum, Node& node);

};


#endif //INC_236_GRAPH_H
