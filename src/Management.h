#ifndef PROJECT2_MANAGEMENT_H
#define PROJECT2_MANAGEMENT_H

#include "Graph.h"
#include "Vertex.h"

class Management {

public:
    static double tspBacktracking(Graph *graph);
    static double tspBacktrackingAlgorithm(Graph *graph, int currIdx, int n, int count, double cost, double& ans);
    static double tspTriangular(Graph* graph);
    static double tspOther(Graph* graph);
    static double tspRealWorld(Graph* graph, int start);

};


#endif //PROJECT2_MANAGEMENT_H
