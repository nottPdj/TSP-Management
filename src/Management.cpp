#include "Management.h"
#include <limits>

/**
 * @brief Initializes values for the algorithm
 * @param graph
 * @return
 */
double Management::tspBacktracking(Graph *graph){
    int n = graph->getVertexSet().size();
    double ans = INF;
    graph->getVertexSet()[0]->setVisited(true);
    tspBacktrackingAlgorithm(graph,0,n,1,0,ans);
    return ans;
}

/**
 * @brief TSP Backtracking Algorithm
 * @param graph - current graph
 * @param currIdx - current index
 * @param n - number of vertices
 * @param count - counter of vertices in path
 * @param cost - current cost of travel
 * @param ans - Optimal travelling cost
 * @return ans
 * @details Time Complexity O(n!) -> number of nodes
*/
double Management::tspBacktrackingAlgorithm(Graph *graph, int currIdx, int n, int count, double cost, double& ans) {

    // Base case: If all nodes are visited and there is a path back to the starting point
    if (count == n) {
        for (Edge *edge : graph->getVertexSet()[currIdx]->getAdj()) {
            if (edge->getDest() == graph->getVertexSet()[0]) {  // Assuming the start is the first vertex
                ans = std::min(ans, cost + edge->getWeight());
            }
        }
        return ans;
    }

    //adjacent vertices
    for (Edge *edge : graph->getVertexSet()[currIdx]->getAdj()) {
        int nextIdx = graph->findVertexIdx(edge->getDest()->getInfo());
        Vertex * v = graph->getVertexSet()[nextIdx];
        if (!v->isVisited()) {
            v->setVisited(true);
            tspBacktrackingAlgorithm(graph, nextIdx, n, count + 1, cost + edge->getWeight(), ans);
            v->setVisited(false);
        }
    }

    return ans;
}

double Management::tspTriangular(Graph *graph) {
    return 0;
}

double Management::tspOther(Graph *graph) {
    return 0;
}

double Management::tspRealWorld(Graph *graph, int start) {
    return 0;
}
