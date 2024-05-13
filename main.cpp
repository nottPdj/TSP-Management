#include <iostream>
#include "src/Graph.h"
#include "src/Auxiliar.h"
#include "src/Menu.h"

int main() {
    Graph *g = new Graph();
    Auxiliar::readDataset(g);
    Menu menu = Menu(g);
    menu.run();
    return 0;
}
