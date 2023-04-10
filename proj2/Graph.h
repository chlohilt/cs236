//
// Created by hilto on 4/3/2023.
//

#ifndef INC_236_GRAPH_H
#define INC_236_GRAPH_H
#include "Node.h"
#include <map>
#include "Rule.h"

class Graph {

private:

    map<int,Node> nodes;

public:

    Graph();

    Graph(int size);

    void addEdge(int fromNodeID, int toNodeID);

    string toString();

    Graph reverseDependencyGraph();

    void dfs();

    void explore(Node& node);

    void dfsForest();

};


#endif //INC_236_GRAPH_H
