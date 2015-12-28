#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <vector>
#include <string>

#include "algorithm.h"

// class for elegamnt management of reading data and running calculations
class Control
{
public:
    Control();                      // Default constructor
    Control(int argc, char **argv); // Constructor with command line parameters
    ~Control();                     // Default destructor

private:
    std::vector <std::string> algorithmNames; // A vector with algorithm name (for nice output)
    Algorithm *algorithm;                     // Pointer to algorithm chosen

    bool init();                    // Allows user to choose method and other initializations
};

#endif // _CONTROL_H_
