#include <iostream>
#include <string>

#include "control.h"
#include "algorithm_brute_force.h"
#include "algorithm_genetic.h"

/******************/
/* PUBLIC METHODS */
/******************/

Control::Control() {}

Control::Control(int argc, char **argv)
{
    if (argc < 3) // Not enough parameters
    {
        std::cout << "Not enough command line parameters\n";
        return;
    }

    algorithmNames.push_back("Brute force"); // Adding "Brute force" algorithm to names
    algorithmNames.push_back("Genetic"); // Adding "Genetic" algorithm to names

    std::string fileNameWords { argv[1] };      // 1 command line parameter is a filename for words
    std::string fileNameDictionary { argv[2] }; // 2 command line parameter is a filename for dictionary

    bool isRead = true; // Flag for successful reading words and dictionary
    if (init()) // If algorithm initialized
    {
        if (!algorithm->readWords(fileNameWords))
        {
            std::cout << "Error while reading start and end words\n";
            isRead = false;
        }
        if (!algorithm->readDictionary(fileNameDictionary))
        {
            std::cout << "Error while reading dictionary\n";
            isRead = false;
        }
        if (isRead) // If files read successfully then implement calculations
        {
            algorithm->setParams(); // Set algorithm parameters
            algorithm->run();       // Start calculations
            std::cout << "Path from \"" << algorithm->getFly() << "\" to \"" << algorithm->getElephant() << "\" looks like:\n";
            for (auto &word : algorithm->getPath())
                std::cout << word << std::endl;
        }
        // deallocate memory (only if init() was successful)
        delete algorithm;
    }
}

Control::~Control() {}

/*******************/
/* PRIVATE METHODS */
/*******************/

bool Control::init()
{
    std::string temp; // Temporary string for input
    size_t idAlgorithm;  // Identifier of the algorithm chosen
    std::cout << "Which method would you like to use?\n";
    for (size_t i = 0; i < algorithmNames.size(); ++i)
        std::cout << i << " - " << algorithmNames[i] << '\n';
    std::cout << "I choose (type a number): ";
    std::cin >> temp;
    try { idAlgorithm = std::stod(temp); }    // Try to convert value input into size_t
    catch (...) { idAlgorithm = 0; }          // In case of failure just set 0 index
    if (idAlgorithm >= algorithmNames.size()) // Wheather id is more then amount of algorithms avaliable
        idAlgorithm = algorithmNames.size() - 1;
    std::cout << algorithmNames[idAlgorithm] << " chosen\n";

    switch (idAlgorithm) // Creating appropriate algorithm
    {
        case 1:
            algorithm = new AlgorithmGenetic();
            break;
        default:
            algorithm = new AlgorithmBruteForce();
            break;
    }
    algorithm->setName(algorithmNames[idAlgorithm]); // Set algorithm name

    return true;
}
