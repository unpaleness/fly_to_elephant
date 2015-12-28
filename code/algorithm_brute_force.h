#ifndef _ALGORITHM_BRUTE_FORCE_H_
#define _ALGORITHM_BRUTE_FORCE_H_

#include <string>

#include "algorithm.h"

// Concrete algorithm of "brute force" (very greedy, but simple)
// Check every possibility before the first match
class AlgorithmBruteForce : public Algorithm
{
public:
    AlgorithmBruteForce();
    ~AlgorithmBruteForce();
    void setParams();
    void run();

private:
    bool search(size_t iteration); // Recursive function for search, "iteration" - current iteration
};

#endif // _ALGORITHM_BRUTE_FORCE_H_
