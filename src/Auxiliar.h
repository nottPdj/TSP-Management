#ifndef PROJECT2_AUXILIAR_H
#define PROJECT2_AUXILIAR_H
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
    static double** initMatrix(int n);

};

#endif //PROJECT2_AUXILIAR_H
