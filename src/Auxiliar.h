#ifndef PROJECT1_AUXILIAR_H
#define PROJECT1_AUXILIAR_H
#include "Graph.h"

/**
 * @brief Auxiliary class to read files
 */
class Auxiliar {
public:
    static void readDataset(Graph *g, int dataset = 0);
    static void readSmall(Graph *g, std::string filename);
    static void readMedium(Graph *g, std::string filename);
    static void readLarge(Graph *g, std::string filename);
};

#endif //PROJECT1_AUXILIAR_H
