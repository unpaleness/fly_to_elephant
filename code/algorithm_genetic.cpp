#include <iostream>
#include <map>

#include "algorithm_genetic.h"

AlgorithmGenetic::AlgorithmGenetic()
{
    iterationLimitMax = 20;
    populationSizeMax = 10;
}

AlgorithmGenetic::~AlgorithmGenetic()
{

}

void AlgorithmGenetic::setParams()
{
    std::string temp; // Temporary string for input
    std::cout << name << ": iteration limit (max: " << iterationLimitMax << "): ";
    std::cin >> temp;
    try { iterationLimit = std::stod(temp); } // Try to convert value input into size_t
    catch (...) { iterationLimit = iterationLimitMax; } // In case of failure just max value
    if (iterationLimit > iterationLimitMax)
        iterationLimit = iterationLimitMax;
    std::cout << name << ": iteration limit set to " << iterationLimit << std::endl;
    std::cout << name << ": population size (max: " << populationSizeMax << "): ";
    std::cin >> temp;
    try { populationSize = std::stod(temp); } // Try to convert value input into size_t
    catch (...) { populationSize = populationSizeMax; } // In case of failure just max value
    if (populationSize > populationSizeMax)
        populationSize = populationSizeMax;
    std::cout << name << ": population size set to " << populationSize << std::endl;
}

void AlgorithmGenetic::run()
{
    path.push_back(fly); // Set up begin word
    if(!search(0)) // If no solvation found
        path.push_back("42");
}

int AlgorithmGenetic::fitness(const std::string &word)
{
    int res { 0 }; // This will be return value
    // First we check whether letters of "word" are in "elephant" (order is important)
    for (auto c : word)
        if (elephant.find(c) != std::string::npos)
            ++res;
    // Then we compare sizes
    res -= std::abs(word.size() - elephant.size());
    return res;
}

bool AlgorithmGenetic::search(size_t iteration)
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
    std::multimap <int, std::string> population; // multimap with fitness as a key and a word as a value
    // Main
    for (auto &word : dictionary)             // Cycle by every word in dictionary
        if (areNeighbours(path.back(), word)) // If dictionary word and current word are neighbours
            population.insert(std::pair <int, std::string> { fitness(word), word }); // Then put fitness value and word to multimap
    size_t size { populationSize }; // Size of population
    if (population.size() < size)   // If real population size is fewer then set
        size = population.size();   // Than correct it
    auto it = population.end();   // Iterator to the end of population (the greatest values)
    for (size_t i = 0; i < size; ++i)
    {
        --it;
        path.push_back((*it).second); // Then push dictionary word into path and try to search deeper
        if (search(iteration + 1))    // In case of success our path is found
                return true;
    }

    // If there are no one neighbour
    path.pop_back(); // Delete the last path element
    return false;
}

