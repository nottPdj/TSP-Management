#ifndef PROJECT2_VERTEX_H
#define PROJECT2_VERTEX_H

#include "Edge.h"
#include <vector>

/**
 * @brief Vertex Class Definition
 */
class Vertex {
public:
    Vertex(int in, double lat, double lng);

    int getInfo() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;

    void setInfo(int info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setPath(Edge *path);
    Edge * addEdge(Vertex *dest, double w);
    bool removeEdge(int in);
    void removeOutgoingEdges();

protected:
    int info;                // info node
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false;
    bool processing = false;
    unsigned int indegree;
    double lat = 0;
    double lng = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    void deleteEdge(Edge *edge);
};


#endif //PROJECT2_VERTEX_H
