#include "Management.h"
#include <cmath>
#include <limits>

/**
 * @brief Converts angle value to radians
 * @param angle
 * @return value in radians
 */
// convert our passed value to radians_t
double Management::convert(const double angle) {
    return angle * (M_PI / 180);
}

/**
 * @brief Calculates haversine distance of two vertices
 * @param v1 vertex
 * @param v2 vertex
 * @return haversine distance between v1 and v2
 */
double Management::getHaversineDist(Vertex *v1, Vertex *v2) {
    const double earths_radius = 6371000;

    // Get the difference between our two points then convert the difference into radians
    const double lat_delta = convert(v2->getLat() - v1->getLat());
    const double lon_delta = convert(v2->getLon() - v1->getLon());

    const double converted_lat1 = convert(v1->getLat());
    const double converted_lat2 = convert(v2->getLat());

    const double a = pow(sin(lat_delta / 2), 2) + cos(converted_lat1) * cos(converted_lat2) * pow(sin(lon_delta / 2), 2);
    const double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return earths_radius * c;
}



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
 * @details Time Complexity O(v) -> v: number of vertices
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


/**
 * @brief Triangular approximation heuristic
 * @param graph fully connected graph
 * @return Cost of the approximate tour
 * @details Time Complexity O(v²log(v)) -> v: number of vertices
 */
double Management::tspTriangular(Graph *graph) {

    mst(graph, 0);

    for (Vertex *v: graph->getVertexSet()) {
        v->setVisited(false);
    }

    double cost = 0;
    std::vector<Vertex *> path;
    Vertex *r = graph->findVertex(0);
    if (r == nullptr) {
        return 0;
    }

    path.push_back(r);

    for (Vertex *v: r->getChildren()) {
        preorderVisit(graph, v, cost, path);
    }

    // add last edge
    if (path.size() > 1) {
        cost += graph->getDist(path.back()->getInfo(), r->getInfo());
        path.push_back(r);
    }

    return cost;
}


/**
 * @brief Gets the minimum spanning tree (mst) using Prim's algorithm
 * @param graph graph to get the mst
 * @param start vertex to start mst
 * @details Time Complexity O(v²log(v)) -> v: number of vertices
 */
void Management::mst(Graph *graph, int start) {

    for (Vertex *v : graph->getVertexSet()) {
        v->setVisited(false);
        v->setDist(INF);
        v->setParent(nullptr);
        v->clearChildren();
    }

    Vertex *r = graph->findVertex(start);
    if (r == nullptr) {
        return;
    }
    r->setDist(0);

    std::priority_queue<std::pair<Vertex *, double>, std::vector<std::pair<Vertex *, double>>, Vertex::greaterDist> minHeap;
    for (Vertex *v: graph->getVertexSet()) {
        minHeap.push(std::make_pair(v, v->getDist()));
    }

    int verticeCount = 0;
    while (!minHeap.empty() && verticeCount < graph->getNumVertex()) {
        Vertex *v = minHeap.top().first;
        minHeap.pop();
        if (v->isVisited())
            continue;
        v->setVisited(true);
        verticeCount++;

        for (Vertex *w : graph->getVertexSet()) {
            if (w->isVisited())
                continue;

            double dist = graph->getDist(v->getInfo(), w->getInfo());
            if (dist < w->getDist()) {
                w->setParent(v);
                w->setDist(dist);
                minHeap.push(std::make_pair(w, dist));
            }
        }
    }

    // set for each vertex the children that were visited after it
    setChildren(graph);
}

/**
 * @brief Auxiliary function that saves in each vertex the children vertices according to the mst performed before
 * @param graph graph after mst
 * @details Time Complexity O(v) -> v: number of vertices
 */
void Management::setChildren(Graph *graph) {

    for (Vertex *v: graph->getVertexSet()) {
        if (v->getParent() != nullptr) {
            v->getParent()->addChild(v);
        }
    }
}

/**
 * @brief Makes a preorder visit through the mst
 * @param g graph after mst
 * @param v vertex from whom children will be added to the preorder visit
 * @param cost it will be returned as the cost of the preorder visit
 * @param path it will be returned as the preorder visit
 * @details Time Complexity O(v) -> v: number of vertices
 */
void Management::preorderVisit(Graph *g, Vertex *v, double &cost, std::vector<Vertex *> &path) {
    cost += g->getDist(v->getInfo(), path.back()->getInfo());
    path.push_back(v);

    for (Vertex *w: v->getChildren()) {
        preorderVisit(g, w, cost, path);
    }
}


/**
 * @brief Performs the nearest neighbour tsp algorithm
 * @param graph fully connected graph
 * @return Cost of the approximate tour
 * @details Time Complexity O(v²) -> v: number of vertices
 */
double Management::tspOther(Graph *graph) {
    double cost = 0;

    for (Vertex *v : graph->getVertexSet()) {
        v->setVisited(false);
    }

    Vertex *last = graph->findVertex(0);

    std::vector<int> path;
    path.push_back(last->getInfo());
    last->setVisited(true);

    while (path.size() < graph->getNumVertex()) {
        double minCost = INF;
        Vertex *minVertex;

        for (Vertex *v : graph->getVertexSet()) {
            if (v->getInfo() != last->getInfo() && !v->isVisited()) {
                if (graph->getDist(v->getInfo(), last->getInfo()) < minCost) {
                    minCost = graph->getDist(v->getInfo(), last->getInfo());
                    minVertex = v;
                }
            }
        }

        last = minVertex;
        path.push_back(last->getInfo());
        last->setVisited(true);
        cost += minCost;
    }

    cost += graph->getDist(path.back(), 0);

    return cost;
}


/**
 * @brief Performs a branch and bound algorithm
 * @param graph
 * @param start vertex to start the tour
 * @return Cost of the tour if it exists else 0
 * @details @details Time Complexity O(v!) -> v: number of vertices
 */
double Management::tspRealWorld(Graph *graph, int start) {

    std::vector<int> curPath;
    std::vector<int> path;
    double minCost = INF;

    for (Vertex *v : graph->getVertexSet()) {
        v->setVisited(false);
        if (v->getAdj().size() < 2) {
            return 0;
        }
    }

    Vertex *startV = graph->findVertex(start);
    tspBB(graph, startV, graph->getNumVertex(), curPath, 0, minCost);

    return minCost;
}


/**
 * @brief Auxiliary recursive function of branch and bound algorithm
 * @param g
 * @param cur last vertex to be added to the path
 * @param n number of vertices
 * @param curPath current path
 * @param cost current cost
 * @param minCost minimum cost so far
 * @details @details Time Complexity O(v!) -> v: number of vertices
 */
void Management::tspBB(Graph *g, Vertex *cur, int n, std::vector<int> curPath, double cost, double &minCost) {
    cur->setVisited(true);
    if (cost >= minCost) {
        cur->setVisited(false);
        return;
    }
    curPath.push_back(cur->getInfo());

    if (curPath.size() == n) {
        for (Edge *e : cur->getAdj()) {
            if (g->findVertex(curPath[0])->getInfo() == e->getDest()->getInfo()) {
                cost += e->getWeight();
                curPath.push_back(g->findVertex(curPath[0])->getInfo());
                if (cost < minCost) {
                    minCost = cost;
                }
            }
        }
    }

    for (Edge *e : cur->getAdj()) {
        if (!e->getDest()->isVisited()) {
            tspBB(g, e->getDest(), n, curPath, cost + e->getWeight(), minCost);
        }
    }

    cur->setVisited(false);
}