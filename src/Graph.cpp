#include <iostream>
#include <algorithm>
#include "Graph.h"


int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/**
 * @brief Auxiliary function to find a vertex with a given content
 * @return v if dound
 * @details Time Complexity O(n) = number of vertices
 */
Vertex * Graph::findVertex(const int &in) const {
    for (auto v : vertexSet)
        if (v->getInfo() == in)
            return v;
    return nullptr;
}

/**
 * @brief Finds the index of the vertex with a given content
 * @return i if found
 * @details Time Complexity O(n) = number of vertices
 */
int Graph::findVertexIdx(const int &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getInfo() == in)
            return i;
    return -1;
}

/**
 * @brief Adds a vertex with a given content or info (in) to a graph (this).
 * @return true if added
 * @details Time Complexity O(n) = number of vertices
 */
bool Graph::addVertex(const int &in, const double lat, const double lng) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(in, lat, lng));
    return true;
}


/**
 * @brief  Removes a vertex with a given content (in) from a graph (this), and all outgoing and incoming edges.
 * @param in
 * @return true if removed
 * @details Time Complexity O(n) = number of vertices
 */
bool Graph::removeVertex(const int &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getInfo() == in) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getInfo());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}


/**
 * @brief Adds an edge to a graph (this), given the contents of the source and destination vertices and the edge weight (w)
 * @param sourc
 * @param dest
 * @param w
 * @return true if successful
 * @details Time Complexity O(n) = number of vertices
 *
 */
bool Graph::addEdge(const int &sourc, const int &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

/**
 * @brief  Removes an edge from a graph (this).
 * @param sourc
 * @param dest
 * @return true if successful
 * @details Time Complexity O(n) = number of vertices
 */
bool Graph::removeEdge(const int &sourc, const int &dest) {
    Vertex * srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

/**
 * @brief Adds an bidirectional edge to a graph (this), given the contents of the source and destination vertices and the edge weight (w)
 * @param sourc
 * @param dest
 * @param w
 * @return true if successful
 * @details Time Complexity O(n) = number of vertices
 */
bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}