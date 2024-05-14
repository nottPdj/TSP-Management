#ifndef PROJECT2_MANAGEMENT_H
#define PROJECT2_MANAGEMENT_H

#include "Graph.h"

static class Management {

    double tspBacktracking(Graph* graph);
    double tspTriangular(Graph* graph);
    double tspOther(Graph* graph);
    double tspRealWorld(Graph* graph, int start);

};


#endif //PROJECT2_MANAGEMENT_H
