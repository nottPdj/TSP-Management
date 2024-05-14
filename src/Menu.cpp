#include "Menu.h"
#include "Auxiliar.h"
#include "Management.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>


/**
 * @brief Constructor of the Menu class. Stores the graph containing all of the chosen dataset information
 * in the private field.
 * @param g Graph containing all of the dataset information
 */
Menu::Menu(Graph *g) : g(g)  {}

/**
 * @brief This method is called to start the interface.
 */
void Menu::run(){
    system("clear");
    clearOutputFile();
    printMainMenu();
    system("clear");
}

/**
 * @brief Clears output file
 */
void Menu::clearOutputFile() {
    std::ofstream ofs;
    ofs.open(outputFile);
    ofs.close();
}

/**
 * @brief Prints the main menu.
 */
void Menu::printMainMenu() {
    system("clear");
    std::cout << center("ROUTING ALGORITHM FOR OCEAN SHIPPING AND URBAN DELIVERIES", '*', MENU_WIDTH) << "\n\n"
              << "0 - Choose dataset (current: " << datasets[curDataset] << ")" << "\n"
              << "\t1 - Backtracking algorithm" << "\n"
              << "\t2 - Triangular Approximation Heuristic" << "\n"
              << "\t3 - Other Heuristics" << "\n"
              << "\t4 - In the Real World" << "\n";

    printExit();
    std::cout << "Press the number corresponding the action you want." << "\n";
    waitMenu();
}

/**
 * @brief Waits for the input and depending on it, calls the method responsible for accomplishing what was asked.
 */
void Menu::waitMenu(){
    std::string choice;
    std::cin >> choice;             // Fetch the option chosen
    if (choice == "q")              // Quit
        return;
    system("clear");
    printingOptions options;
    switch (stoi(choice)) {
        // Backtracking algorithm
        case 1: {
            auto start = std::chrono::high_resolution_clock::now();
            double cost = Management::tspBacktracking(g);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start).count();

            options.message = "TSP using a Backtracking Algorithm\n - For graph: " + datasets[curDataset] + ", starting in node 0";
            printTspResults(options, cost, duration);
            break;
        }
        // Triangular Approximation Heuristic
        case 2: {
            auto start = std::chrono::high_resolution_clock::now();
            double cost = Management::tspTriangular(g);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start).count();

            options.message = "TSP using the Triangular Approximation Algorithm\n - For graph: " + datasets[curDataset] + ", starting in node 0";
            printTspResults(options, cost, duration);
            break;
        }
        // Other Heuristics
        case 3: {
            auto start = std::chrono::high_resolution_clock::now();
            double cost = Management::tspOther(g)
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start).count();

            options.message = "TSP using Other Heuristics\n - For graph: " + datasets[curDataset] + ", starting in node 0";
            printTspResults(options, cost, duration);
            break;
        }
        // In the Real World
        case 4: {
            int startingPoint = chooseStartingPoint();

            auto start = std::chrono::high_resolution_clock::now();
            double cost = Management::tspRealWorld(g, startingPoint);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start).count();

            options.message = "TSP using Other Heuristics\n - For graph: " + datasets[curDataset] + ", starting in node " + startingPoint;
            printTspResults(options, cost, duration);
            break;
        }
        // Choose dataset
        case 8: {
            chooseDataset();
            g = new Graph();
            Auxiliar::readDataset(g, curDataset);
        }
        default: {
            printMainMenu();
        }
    }
}

/**
 * @brief Prints the list of datasets available and sets the current database to the one chosen by the user
 */
void Menu::chooseDataset() {
    std::cout << "Choose what dataset to use:\n\n";
    std::cout << "\tToy Graphs\n"
    std::cout << "\t\t0 - Shipping\n";
    std::cout << "\t\t1 - Stadiums\n";
    std::cout << "\t\t2 - Tourism\n\n";
    std::cout << "\tExtra Fully Connected Graphs\n"
    std::cout << "\t\t3 - 25 nodes\n";
    std::cout << "\t\t4 - 50 nodes\n";
    std::cout << "\t\t5 - 75 nodes\n";
    std::cout << "\t\t6 - 100 nodes\n";
    std::cout << "\t\t7 - 200 nodes\n";
    std::cout << "\t\t8 - 300 nodes\n";
    std::cout << "\t\t9 - 400 nodes\n";
    std::cout << "\t\t10 - 500 nodes\n";
    std::cout << "\t\t11 - 600 nodes\n";
    std::cout << "\t\t12 - 700 nodes\n";
    std::cout << "\t\t13 - 800 nodes\n";
    std::cout << "\t\t14 - 900 nodes\n";
    std::cout << "\tReal World Graphs\n";
    std::cout << "\t\t15 - Graph 1\n";
    std::cout << "\t\t16 - Graph 2\n";
    std::cout << "\t\t17 - Graph 3\n";
    std::cin >> curDataset;
}

/**
 * @brief Get the starting point for the tour
 * @return Identifier label of the starting point
 */
int Menu::chooseStartingPoint() {
    int startingPoint;
    std::cout << "Choose a starting point for the tour: ";
    std::cin >> startingPoint;
    return startingPoint;
}


/**
 * @brief Prints the results of the executed TSP algorithm
 * @param options Printing options
 * @param cost Cost of the tour
 * @param duration Execution time of the algorithm
 */
void Menu::printTspResults(printingOptions options, double cost, long duration) {
    std::ostringstream oss;

    if (options.clear)
        system("clear");
    if (options.printMessage)
        oss << options.message;

    oss << "\n\n";

    oss << "Cost: " << cost << "\n"
    oss << "Execution time: " << duration + "ms\n";

    std::cout << oss.str();

    if (options.outputToFile) {
        std::ofstream ofs;
        ofs.open(outputFile, std::ios_base::app);
        ofs << oss.str();
        ofs.close();
    }

    if (options.showEndMenu)
        endDisplayMenu();

    getInput();
}


/**
 * @brief Return a string of length width with str centered and surrounded by sep.
 * @param str
 * @param sep
 * @param width
 * @return String of length width with str centered and surrounded by sep
 */
std::string Menu::center(const std::string &str, char sep, int width) {
    std::ostringstream oss;
    std::string str2 = str;
    if (str.length() > width) {
        str2 = str.substr(0, width);
    }
    int space = (width - str2.length()) / 2;
    oss << std::setw(space) << std::setfill(sep) << "" << str2 << std::setw(width - str2.length() - space) << std::setfill(sep) << "";
    return oss.str();
}


void Menu::printBackToMenu() {
    std::cout << "Press 'm' to go back to the main menu.\n";
}

void Menu::printExit() {
    std::cout << "Press 'q' to quit.\n";
}

/**
 * @brief Receives input from the user.
 * @return
 */
char Menu::getInput() {
    char input;
    std::cin >> input;
    if (input == 'm') {
        printMainMenu();
    }
    return input;
}

/**
 * @brief Prints default menu after displaying anything that allows to go back to the main menu or exit the program.
 */
void Menu::endDisplayMenu() {
    printBackToMenu();
    printExit();
}
