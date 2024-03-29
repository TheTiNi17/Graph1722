#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

#include "node.h"

class Graph
{
private:
    std::map<int, Node> nodes;
    std::set<std::pair<int, int>> edges;

public:
    Graph();
    void addNode(int id, const std::string& name, const std::string& description);
    void removeNode(int id);
    void addEdge(int id1, int id2);
    void removeEdge(int id1, int id2);
    void printGraph();
    std::string saveToJson();

};

#endif // GRAPH_H
