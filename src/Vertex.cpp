#include "Vertex.h"
#include "Edge.h"


/**
 * @brief Vertex Constructor
 */
Vertex::Vertex(int in, double lat, double lng): info(in),lat(lat),lng(lng) {}

/**
 * @brief Auxiliary function to add an outgoing edge to a vertex (this), with a given destination vertex (d) and edge weight (w).
 * @return newEdge
 */
Edge * Vertex::addEdge(Vertex *d, double w) {
    Edge* newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}



/**
 * @brief Auxiliary function to remove an outgoing edge (with a given destination (d)) from a vertex (this).
 * @param in
 * @return removedEdge -> true if successful, and false if such edge does not exist
 * @details Time Complexity = O(n) n-> number of incoming or adjacent edges
 */
bool Vertex::removeEdge(int in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}


/**
 * @brief Auxiliary function to remove an outgoing edge of a vertex
 * @details Time Complexity = O(n) n-> number of incoming or adjacent edges
 */
void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}


int Vertex::getInfo() const {
    return this->info;
}


std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

bool Vertex::isProcessing() const {
    return this->processing;
}


unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setInfo(int in) {
    this->info = in;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setProcesssing(bool processing) {
    this->processing = processing;
}

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

/**
 * @brief Deletes incoming edge
 * @param edge to delete
 * @details Time Complexity = O(n) n-> number of incoming edges
 */
void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

double Vertex::getDist() const {
    return dist;
}

Vertex *Vertex::getParent() const {
    return parent;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setParent(Vertex *parent) {
    this->parent =parent;
}

double Vertex::getLat() const {
    return lat;
}

double Vertex::getLon() const {
    return lon;
}

void Vertex::clearChildren() {
    this->children = {};
}

void Vertex::addChild(Vertex *child) {
    this->children.push_back(child);
}

std::vector<Vertex *> Vertex::getChildren() const {
    return children;
}
