#ifndef PROJECT2_MANAGEMENT_H
#define PROJECT2_MANAGEMENT_H

#include "Graph.h"
#include "Vertex.h"

/**
 * @brief Management Class Definition
 */
class Management {

public:
    static double tspBacktracking(Graph *graph);
    static double tspTriangular(Graph* graph);
    static double tspOther(Graph* graph);
    static double tspRealWorld(Graph* graph, int start);
    static double getHaversineDist(Vertex *v1, Vertex *v2);

private:
    static double tspBacktrackingAlgorithm(Graph *graph, int currIdx, int n, int count, double cost, double& ans);

    static void mst(Graph *graph, int start);
    static void setChildren(Graph *graph);
    static void preorderVisit(Graph *g, Vertex *v, double &cost, std::vector<Vertex *> &path);

    static void tspBB(Graph *g, Vertex *cur, int n, std::vector<int> curPath, double cost, double &minCost);

    static double convert(const double angle);
};


#endif //PROJECT2_MANAGEMENT_H
