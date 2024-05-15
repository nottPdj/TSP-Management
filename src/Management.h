#ifndef PROJECT2_MANAGEMENT_H
#define PROJECT2_MANAGEMENT_H

#include "Graph.h"

class Management {

public:
    static double tspBacktracking(Graph* graph);
    static double tspTriangular(Graph* graph);
    static double tspOther(Graph* graph);
    static double tspRealWorld(Graph* graph, int start);

private:
    static void mst(Graph *graph, int start);
    static void setChildren(Graph *graph);
    static void preorderVisit(Graph *g, Vertex *v, double &cost, std::vector<Vertex *> &path);

    static double convert(const double angle);
    static double getHaversineDist(Vertex *v1, Vertex *v2);
};


#endif //PROJECT2_MANAGEMENT_H
