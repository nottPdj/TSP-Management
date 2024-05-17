#include "Auxiliar.h"

#include <sstream>
#include <fstream>
#include <algorithm>

/**
 * @brief Reads the selected DataSet
 * @param g The main graph
 * @param dataset dataset to load
 */


void Auxiliar::readDataset(Graph *g, int dataset) {
    std::string files[18];
    files[0] = "../data/Toy_Graphs/shipping.csv";
    files[1] = "../data/Toy_Graphs/stadiums.csv";
    files[2] = "../data/Toy_Graphs/tourism.csv";
    files[3] = "../data/Extra_Fully_Connected_Graphs/edges_25.csv";
    files[4] = "../data/Extra_Fully_Connected_Graphs/edges_50.csv";
    files[5] = "../data/Extra_Fully_Connected_Graphs/edges_75.csv";
    files[6] = "../data/Extra_Fully_Connected_Graphs/edges_100.csv";
    files[7] = "../data/Extra_Fully_Connected_Graphs/edges_200.csv";
    files[8] = "../data/Extra_Fully_Connected_Graphs/edges_300.csv";
    files[9] = "../data/Extra_Fully_Connected_Graphs/edges_400.csv";
    files[10] = "../data/Extra_Fully_Connected_Graphs/edges_500.csv";
    files[11] = "../data/Extra_Fully_Connected_Graphs/edges_600.csv";
    files[12] = "../data/Extra_Fully_Connected_Graphs/edges_700.csv";
    files[13] = "../data/Extra_Fully_Connected_Graphs/edges_800.csv";
    files[14] = "../data/Extra_Fully_Connected_Graphs/edges_900.csv";
    files[15] = "../data/Real_World_Graphs/graph1/";
    files[16] = "../data/Real_World_Graphs/graph2/";
    files[17] = "../data/Real_World_Graphs/graph3/";
    std::string filename = files[dataset];

    if (dataset <= 2){
        Auxiliar::readSmall(g, filename);
    }
    else if (dataset <= 14){
        Auxiliar::readMedium(g, filename);
    }
    else if (dataset <= 17){
        Auxiliar::readLarge(g, filename);
    }

}

/**
 * @brief Reads the small dataset
 * @param g The main graph
 * @param filename file to read
 * @details Time Complexity O(n) n = number of stations
 */
void Auxiliar::readSmall(Graph *g, std::string filename) {

    std::ifstream file(filename);
    std::string line, orig, dest, distance;
    getline(file, line);

    while (std::getline(file, line)){
        std::istringstream ss(line);
        getline(ss, orig, ',');
        getline(ss, dest, ',');
        getline(ss, distance, ',');
        g->addVertex(std::stoi(orig));
        g->addVertex(std::stoi(dest));
        g->addBidirectionalEdge(std::stoi(orig), std::stoi(dest), std::stod(distance));
    }

}

/**
 * @brief Reads the medium graph
 * @param g The main graph
 * @param filename file to read
 * @param dataset Time Complexity O(n) n = number of edges
 */
void Auxiliar::readMedium(Graph *g, std::string filename) {

    std::ifstream file(filename);
    std::string line, orig, dest, distance;
    getline(file, line);

    while (std::getline(file, line)){
        std::istringstream ss(line);
        getline(ss, orig, ',');
        getline(ss, dest, ',');
        getline(ss, distance, '\r');

      g->addVertex(std::stoi(orig));
        g->addVertex(std::stoi(dest));
        g->addEdge(std::stoi(orig), std::stoi(dest), std::stod(distance));
        g->addBidirectionalEdge(std::stoi(orig), std::stoi(dest), std::stod(distance));

    }

}

/**
 * @brief Reads the large dataset
 * @param g The main graph
 * @param filename file to read
 * @details Time Complexity O(n) n = number nodes
 */
void Auxiliar::readLarge(Graph *g, std::string filename) {

    std::ifstream vertexFile(filename + "nodes.csv");
    std::string line;
    std::string id, longitude, latitude;
    getline(vertexFile, line);

    while (std::getline(vertexFile, line)){

        std::istringstream ss(line);
        getline(ss, id, ',');
        getline(ss, longitude, ',');
        getline(ss, latitude, '\r');
        g->addVertex(std::stoi(id), std::stod(longitude), std::stod(latitude));
    }

    std::ifstream file(filename + "edges.csv");
    std::string orig, dest, distance;
    getline(file, line);

    while (std::getline(file, line)){
        std::istringstream ss(line);
        getline(ss, orig, ',');
        getline(ss, dest, ',');
        getline(ss, distance, '\r');
        g->addBidirectionalEdge(std::stoi(orig), std::stoi(dest), std::stod(distance));
    }

}
