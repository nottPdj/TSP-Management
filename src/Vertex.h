#ifndef PROJECT2_VERTEX_H
#define PROJECT2_VERTEX_H

#include "Edge.h"
#include <vector>
#include <queue>

/**
 * @brief Vertex Class Definition
 */
class Vertex {
public:
    Vertex(int in, double lon, double lat);

    int getInfo() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Vertex *getParent() const;
    std::vector<Vertex *> getChildren() const;
    double getLat() const;
    double getLon() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;

    void setInfo(int info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setPath(Edge *path);
    void setDist(double dist);
    void setParent(Vertex *parent);
    void clearChildren();
    void addChild(Vertex *child);
    Edge * addEdge(Vertex *dest, double w);
    bool removeEdge(int in);
    void removeOutgoingEdges();

    struct greaterDist {
        bool operator() (const std::pair<Vertex *, double> l, const std::pair<Vertex *, double> r) const {
            return l.second > r.second;
        }
    };

protected:
    int info;                // info node
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false;
    bool processing = false;
    unsigned int indegree;
    double lat = 0;
    double lon = 0;
    double dist;
    Vertex *parent;
    std::vector<Vertex *> children;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    void deleteEdge(Edge *edge);
};

#endif //PROJECT2_VERTEX_H
