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
    static double tspBacktrackingAlgorithm(Graph *graph, int currIdx, int n, int count, double cost, double& ans);
    static double tspTriangular(Graph* graph);
    static double tspOther(Graph* graph);
    static double tspRealWorld(Graph* graph, int start);
    static double getHaversineDist(Vertex *v1, Vertex *v2);

private:
    static void mst(Graph *graph, int start, double &minBound);
    static void setChildren(Graph *graph, double &minBound);
    static void preorderVisit(Graph *g, Vertex *v, double &cost, std::vector<Vertex *> &path);

    static double convert(const double angle);
    static void createMstGraph(Graph *graph, Graph *mst);
    static void findEulerTour(Graph *graph, Vertex *v, std::vector<Vertex *> &tour);
    static std::vector<Vertex *> removeRepeatedVertices(Graph *graph, std::vector<Vertex *> &tour);
    static std::vector<int> findOdds(Graph *graph);
    static void perfectMatching(Graph *graph, Graph *mst);

    static void tspBB(Graph *g, Vertex *cur, int n, std::vector<int> curPath, double cost, double &minCost);
};


#endif //PROJECT2_MANAGEMENT_H
