#ifndef CHARACTERISTICS_H
#define CHARACTERISTICS_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Characteristics {
private:
    int score = 0;

    vector<string> words;
    int countPalindromes = 0;
    int countNoRepeatedLetters = 0;
    int countNoVowels = 0;
    int countNoConsonants = 0;
    int countAlternatingVowelsConsonants = 0;
    int countAlphabeticalOrder = 0;
    int countReverseAlphabeticalOrder = 0;
    int countStartEndSameLetter = 0;
    int countScrabbleScore20 = 0;
    int countScrabbleScore30 = 0;
    int countScrabbleScore40 = 0;
    int countDoubleConsecutiveLetters = 0;
    int countTripleConsecutiveLetters = 0;
    int countContainsRarityWord = 0;
    int countIsRarityWord = 0;
    vector<int> countLengths;

    bool isPalindrome(const string& word) const;
    bool noRepeatedLetters(const string& word) const;
    bool containsNoVowels(const string& word) const;
    bool containsNoConsonants(const string& word) const;
    bool alternatingVowelsConsonants(const string& word) const;
    bool alphabeticalOrder(const string& word) const;
    bool reverseAlphabeticalOrder(const string& word) const;
    bool startEndSameLetter(const string& word) const;
    bool containsRarityWord(const string& word) const;
    bool isRarityWord(const string& word) const;
    int rareLetters(const string& word) const;
    int calculateScrabbleScore(const string& word) const;
    int consecutiveLetters(const string& word) const;
    bool contains(const string& word, char letter) const;

public:
    void calculateCounts();
    void printCounts() const;
    void printScore(const string& word);
    void addPoints(const string& rule, int frequency);
    string randomWord() const;
    void createJSONFile(const string& outputPath = "../../frontend/public/stats.json") const;
};

#endif // CHARACTERISTICS_H