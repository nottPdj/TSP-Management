#include "Management.h"
#include <cmath>

double Management::tspBacktracking(Graph *graph) {
    return 0;
}

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
        cost += getHaversineDist(path.back(), r);
        path.push_back(r);
    }

    return cost;
}

double Management::tspOther(Graph *graph) {
    return 0;
}

double Management::tspRealWorld(Graph *graph, int start) {
    return 0;
}

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

            double dist = getHaversineDist(v, w);
            std::cout << v->getInfo() << " " << w->getInfo() << " " << dist << "\n";
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

void Management::setChildren(Graph *graph) {
    // TODO return first the closest child
    // this cost is a lower bound of the optimal tour
//    double cost = 0;
    for (Vertex *v: graph->getVertexSet()) {
        if (v->getParent() != nullptr) {
            v->getParent()->addChild(v);
//            cost += getHaversineDist(v, v->getParent());
        }
    }
//    std::cout << "Cost = " << cost << "\n\n";
}

void Management::preorderVisit(Graph *g, Vertex *v, double &cost, std::vector<Vertex *> &path) {
    cost += getHaversineDist(v, path.back());
    path.push_back(v);

    for (Vertex *w: v->getChildren()) {
        preorderVisit(g, w, cost, path);
    }
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

