#ifndef _ALGORITHM_GENETIC_H_
#define _ALGORITHM_GENETIC_H_

#include <string>

#include "algorithm.h"

// Concrete genetic algorithm
// Chooses the most accmmodated individuals due to "fitness" function
// All operations only with them
class AlgorithmGenetic : public Algorithm
{
public:
    AlgorithmGenetic();
    ~AlgorithmGenetic();
    void setParams();
    void run();

private:
    size_t populationSize;    // Size of the most accommodated population
    size_t populationSizeMax; // Maximum avaliable size of the most accommodated population
    int fitness(const std::string &word); // Genetic fitness function for word
    bool search(size_t iteration); // Recursive function for search, "iteration" - current iteration
};

#endif // _ALGORITHM_GENETIC_H_
