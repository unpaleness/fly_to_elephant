// Testing methods of abstract "Algorithm" class
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testAlgorithm
#include <boost/test/unit_test.hpp>

#include "../../code/algorithm.h"

BOOST_AUTO_TEST_SUITE(testSuiteAlgorithm)

// Defective class for testing common functionality
class AlgorithmTest : public Algorithm
{
public:
    ~AlgorithmTest() {}
    void setParams() {} // Not testing here
    void run() {} // Not testing here

    // Getters
    const std::string &getFly() { return fly; }
    const std::string &getElephant() { return elephant; }
    const std::set <std::string> &getDictionary() { return dictionary; }
    const std::vector <std::string> &getPath() { return path; }
    bool areNeighboursTest(const std::string &prev, const std::string &next) { return areNeighbours(prev, next); }
};

struct Fixture
{
    Fixture() : algorithmTest() {}
    ~Fixture() {}

    AlgorithmTest algorithmTest;
};

// Test case for nonexisting files with words and dictionary
BOOST_FIXTURE_TEST_CASE(nonexisting_files, Fixture)
{
    std::string filename { "42" };
    // Should return false cause file "42" doesn't exist
    BOOST_CHECK_EQUAL(algorithmTest.readWords(filename), false);
    // Should return false cause file "42" doesn't exist
    BOOST_CHECK_EQUAL(algorithmTest.readDictionary(filename), false);
}

// Test case for existing files with words and dictionary
BOOST_FIXTURE_TEST_CASE(existing_files, Fixture)
{
    std::string filename { "words" };
    std::string fly { "cat" };
    std::string elephant { "mol" };
    std::string dict[] { "cat", "mal", "male", "mate", "mol", "sat", "sate", "tac", "tat" };
    std::set <std::string> dictionary(dict, dict + 9);
    // Should return true cause file "words" exists
    BOOST_CHECK_EQUAL(algorithmTest.readWords(filename), true);
    // Checking correctness of reading of "fly" and "elephant"
    BOOST_CHECK_EQUAL(algorithmTest.getFly(), fly);
    BOOST_CHECK_EQUAL(algorithmTest.getElephant(), elephant);

    filename = "dictionary";
    // Should return true cause file "dictionary" exists
    BOOST_CHECK_EQUAL(algorithmTest.readDictionary(filename), true);
    // Checking size of dictionary
    BOOST_CHECK_EQUAL(algorithmTest.getDictionary().size(), dictionary.size());
    // Checking each word in dictionary
    if (algorithmTest.getDictionary().size() == dictionary.size()) // If size is OK
    {
        auto it2 = dictionary.begin();
        for (auto it1 = algorithmTest.getDictionary().begin(); it1 != algorithmTest.getDictionary().end(); ++it1, ++it2)
            BOOST_CHECK_EQUAL(*it1, *it2);
    }
}

// Test case for detecting neighbours
BOOST_FIXTURE_TEST_CASE(neighbours, Fixture)
{
    // Equal words are not neighbours
    std::string word1 { "abcde" };
    std::string word2 { "abcde" };
    BOOST_CHECK_EQUAL(algorithmTest.areNeighboursTest(word1, word2), false);

    // Words are case sensitive (change only one)
    word2 = "abCde";
    BOOST_CHECK_EQUAL(algorithmTest.areNeighboursTest(word1, word2), true);

    // If the are more than one change words won't be neihgbours any more
    word2 = "abCdf";
    BOOST_CHECK_EQUAL(algorithmTest.areNeighboursTest(word1, word2), false);

    // Adding a one letter to START or END of a word leads to neibourhood
    word2 = "1abcde";
    BOOST_CHECK_EQUAL(algorithmTest.areNeighboursTest(word1, word2), true);
    word2 = "abcde9";
    BOOST_CHECK_EQUAL(algorithmTest.areNeighboursTest(word1, word2), true);
}

BOOST_AUTO_TEST_SUITE_END()
