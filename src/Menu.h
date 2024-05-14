#ifndef PROJECT2_MENU_H
#define PROJECT2_MENU_H

#include <string>
#include <vector>

#include "Graph.h"


/**
 * @brief Menu auxiliary struct storing the printing options for a printing function.
 */
struct printingOptions {
    std::string message;
    bool clear = true;
    bool printMessage = true;
    bool outputToFile = true;
    bool showEndMenu = true;
};

/**
 * @brief Menu is used to create an interface between the user and the program.
 * Uses the console to receive and output inputs. There are some functionalities available only for Ubuntu.
 * */
class Menu {
private:
    /**
     * @brief Graph containing all of the chosen dataset information that is being managed.
     */
    Graph *g;

    /**
     * @brief Contains the names of the datasets available.
     */
    std::string datasets[18] = {
        "Shipping",
        "Stadiums",
        "Tourism",
        "25 nodes",
        "50 nodes",
        "75 nodes",
        "100 nodes",
        "200 nodes",
        "300 nodes",
        "400 nodes",
        "500 nodes",
        "600 nodes",
        "700 nodes",
        "800 nodes",
        "900 nodes",
        "Graph 1",
        "Graph 2",
        "Graph 3"
    };

    /**
     * @brief Currently loaded dataset (index to dataset array)
     */
    int curDataset = 0;

    /**
     * @brief Path of the output file
     */
    std::string outputFile = "../data/output.txt";

    /**
     * @brief Column widths
     */
    const static int MENU_WIDTH = 86;

public:
    Menu(Graph *g);
    void run();

private:
    // Wait for inputs
    void waitMenu();
    char getInput();
    void chooseDataset();
    int chooseStartingPoint();

    // Print menus
    void printMainMenu();
    void endDisplayMenu();
    void printBackToMenu();
    void printExit();

    // Output file
    void clearOutputFile();

    // Auxiliary formatting functions
    std::string center(const std::string &str, char sep, int width);

    // Printing
    void printTspResults(printingOptions options, double cost, long duration);
};


#endif //PROJECT2_MENU_H
