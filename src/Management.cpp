#include "Management.h"
#include <cmath>
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

    double minBound = 0;
    mst(graph, 0, minBound);

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
        minBound += graph->getDist(path.back()->getInfo(), r->getInfo());
        std::cout << minBound << '\n';
        path.push_back(r);
    }

    std::cout << "Min bound = " << minBound << "\n";
    std::cout << "2-op = " << (minBound * 2) << "\n";
    std::cout << "3/2-opp = " << (minBound * 3 / 2) << "\n\n";

    return cost;
}


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
//                    path = curPath;
                    minCost = cost;
                    std::cout << "\n\nFOUND: " << cost << "\n";
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

void Management::perfectMatching(Graph *graph, Graph *mst){
    std::vector<int>::iterator v, closest;

    std::vector<int> odds = findOdds(graph);

    while(!odds.empty()){
        v = odds.begin();
        auto it = odds.begin() + 1;
        auto end = odds.end();
        int cost = INF;
        for(; it != end; it++){
            double newDist = graph->getDist(*v,*it);
            if(newDist < cost){
                cost = newDist;
                closest = it;
            }
        }
        mst->addBidirectionalEdge(*v, *closest, cost);
        odds.erase(closest);
        odds.erase(v);
    }

}


std::vector<int> Management::findOdds(Graph *graph){
    std::vector<int> odds;
    for(Vertex* v : graph->getVertexSet()){
        int degree = 0;
        if (v->getParent() != nullptr) {
            degree++;
        }
        degree += v->getChildren().size();
        if(degree % 2 == 1){
            odds.push_back(v->getInfo());
        }
    }
    return odds;
}

void Management::mst(Graph *graph, int start, double &minBound) {

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
    setChildren(graph, minBound);
}

void Management::setChildren(Graph *graph, double &minBound) {

    for (Vertex *v: graph->getVertexSet()) {
        if (v->getParent() != nullptr) {
            v->getParent()->addChild(v);
            minBound += graph->getDist(v->getInfo(), v->getParent()->getInfo());
        }
    }
}

void Management::createMstGraph(Graph *graph, Graph *mst) {
    for (Vertex *v : graph->getVertexSet()) {
        mst->addVertex(v->getInfo());
        for (Vertex *w : v->getChildren()) {
            mst->addVertex(w->getInfo());
            mst->addBidirectionalEdge(v->getInfo(), w->getInfo(), graph->getDist(v->getInfo(), w->getInfo()));
        }
    }
}

void Management::preorderVisit(Graph *g, Vertex *v, double &cost, std::vector<Vertex *> &path) {
    cost += g->getDist(v->getInfo(), path.back()->getInfo());
    path.push_back(v);

    for (Vertex *w: v->getChildren()) {
        preorderVisit(g, w, cost, path);
    }
}

void Management::findEulerTour(Graph *graph, Vertex *v, std::vector<Vertex *> &tour) {
    v->setVisited(true);
    tour.push_back(v);
    for (Edge *e : v->getAdj()) {
        if (!e->getDest()->isVisited()) {
            findEulerTour(graph, e->getDest(), tour);
            tour.push_back(v);
        }
    }
}

std::vector<Vertex * > Management::removeRepeatedVertices(Graph *graph, std::vector<Vertex *> &tour) {

    for (Vertex *i : tour){
        i->setVisited(false);
    }

    Vertex *root = tour.front();
    std::vector<Vertex *>::iterator cur = tour.begin();
    std::vector<Vertex *>::iterator iter = tour.begin()+1;
    tour[0]->setVisited(true);

    while(iter != tour.end()){
        Vertex * v = *iter;
        if(!v->isVisited()){
            cur = iter;
            v->setVisited(true);
            iter = cur + 1;
        }
        else{
            iter = tour.erase(iter);
        }
    }
    return tour;
}

// convert our passed value to radians_t
double Management::convert(const double angle) {
    return angle * (M_PI / 180);
}

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

double Management::tspOther(Graph *graph) {
    double minBound = 0;
    mst(graph, 0, minBound);

    Graph * mst = new Graph();
    createMstGraph(graph, mst);

    perfectMatching(graph, mst);

    for (Vertex *v : mst->getVertexSet()) {
        v->setVisited(false);
    }
    std::vector<Vertex *> tour;
    findEulerTour(mst, mst->findVertex(0), tour);
    removeRepeatedVertices(mst, tour);

    double cost = 0;
    for (int i = 0; i < tour.size() - 1; i++) {
        cost += graph->getDist(tour[i]->getInfo(), tour[i + 1]->getInfo());
    }
    if (tour.size() > 1) {
        cost += graph->getDist(tour[tour.size() - 1]->getInfo(), tour[0]->getInfo());
    }

    return cost;
}

