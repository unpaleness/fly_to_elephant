#include <iostream>

#include "algorithm_brute_force.h"

AlgorithmBruteForce::AlgorithmBruteForce()
{
    iterationLimitMax = 20;
}

AlgorithmBruteForce::~AlgorithmBruteForce()
{

}

void AlgorithmBruteForce::setParams()
{
    std::string temp; // Temporary string for input
    std::cout << name << ": iteration limit (max: " << iterationLimitMax << "): ";
    std::cin >> temp;
    try { iterationLimit = std::stod(temp); } // Try to convert value input into size_t
    catch (...) { iterationLimit = iterationLimitMax; } // In case of failure just max value
    if (iterationLimit > iterationLimitMax)
        iterationLimit = iterationLimitMax;
    if (iterationLimit < 1)
        iterationLimit = 1;
    std::cout << name << ": iteration limit set to " << iterationLimit << std::endl;
}

void AlgorithmBruteForce::run()
{
    path.push_back(fly); // Set up begin word
    if(!search(0))       // If no solvation found
        path.push_back("42");
}

bool AlgorithmBruteForce::search(size_t iteration)
{
    // Check for coincidence with "elephant"
    if (path.back().compare(elephant) == 0)
        return true;
    // Check for loops
    for (size_t i = 0; i < path.size() - 1; ++i) // Cycle by every word in path except the last one
        if (path[i].compare(path.back()) == 0)              // In case of match the last one with any in path
        {
            path.pop_back();                     // Delete the last path element
            return false;
        }
    // Check whether iteration limit was reached
    if (iteration >= iterationLimit)
    {
        path.pop_back();
        return false;
    }
    // Main
    for (auto &word : dictionary)             // Cycle by every word in dictionary
        if (areNeighbours(path.back(), word)) // If dictionary word and current word are neighbours
        {
            path.push_back(word);             // Then push dictionary word into path and try to search deeper
            if (search(iteration + 1))        // In case of success our path is found
                return true;
        }
    // If there are no one neighbour
    path.pop_back(); // Delete the last path element
    return false;
}
