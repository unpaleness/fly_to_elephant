#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

// Abstract class, need for inheritance of concrete algorithms
class Algorithm
{
public:
    // Default constructor
    Algorithm() { }
    // Setter of "name"
    void setName(const std::string &n) { name = n; }
    // Getter of "fly"
    const std::string &getFly() { return fly; }
    // Getter of "elephant"
    const std::string &getElephant() { return elephant; }
    // Getter of "path"
    const std::vector <std::string> &getPath() { return path; }
    //Reads start and end words from "fileNameWords" file
    bool readWords(const std::string &fileNameWords)
    {
        try
        {
            std::ifstream input(fileNameWords, std::ios::in); // Filestream of words
            if (!input.is_open())
                return false;
            getline(input, fly);
            getline(input, elephant);
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
    // Reads dictionary from "fileNameDictionary" file
    bool readDictionary(const std::string &fileNameDictionary)
    {
        try
        {
            std::string buffer; // Temporary string for reading each string
            std::ifstream input(fileNameDictionary, std::ios::in); // Filestream of dictionary
            if (!input.is_open())
                return false;
            while (getline(input, buffer))
                dictionary.insert(buffer);
        }
        catch (...)
        {
            return false;
        }
        return true;
    }

    virtual ~Algorithm() {}       // Abstract destructor
    virtual void setParams() = 0; // Virtual function to set algorithm parameters
    virtual void run() = 0;       // Virtual function to run calculations

protected:
    size_t iterationLimit;             // Iteration limit
    size_t iterationLimitMax;          // Maximum iteration limit
    std::string name;                  // Name of algorithm
    std::string fly;                   // A "fly" - start word
    std::string elephant;              // An "elephant" - end word
    std::set <std::string> dictionary; // Dictionary in representation of set
    std::vector <std::string> path;    // A "path" of words leading from "fly" to "elephant"

    // Shows whether "prev" and "next" are neighbours or not (have minimal difference)
    bool areNeighbours(const std::string &prev, const std::string &next)
    {
        // If strings are the same size:
        // neighbours are strings that differs only by 1 symbol
        if (prev.size() == next.size())
        {
            size_t matches { 0 };             // Amount of matching symbols
            size_t size { prev.size() };      // Size of strings (in order not to call .size() every time)
            for (size_t i = 0; i < size; ++i) // Cycle by all symbols
                if (prev[i] == next[i])       // In case of match
                    ++matches;                // "mathes" increments
            if (matches == size - 1)          // In case of neighbourhood
                return true;
        }
        // If their sizes differ:
        // 1) thier sizes must differ only by 1
        // 2) small string must fully occur in large one
        else
        {
            // Permanently exit if the 1st condition is false
            if (std::fabs(int(prev.size()) - int(next.size())) > 1)
                return false;
            // if one of the strings has another
            if (prev.find(next) != std::string::npos || next.find(prev) != std::string::npos)
                return true;
        }
        return false;
    }
};

#endif // _ALGORITHM_H_
