#ifndef CHARACTERISTICS_H
#define CHARACTERISTICS_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <fstream>
using namespace std;

class Characteristics {
  private:
    int score;
    int wordLength;
    int syllables;
    int definitions;
    
    int numWords;
    int countPalindromes;
    int countNoRepeatedLetters;
    int countNoVowels;
    int countNoConsonants;
    int countAlternatingVowelsConsonants;
    int countAlphabeticalOrder;
    int countReverseAlphabeticalOrder;
    int countStartEndSameLetter;
    int countScrabbleScore20;
    int countScrabbleScore30;
    int countScrabbleScore40;
    int countDoubleConsecutiveLetters;
    int countTripleConsecutiveLetters;
    int countContainsRarityWord;
    int countIsRarityWord;
    
  public:
    void calculateCounts();
    void printCounts();
    void printScore(string word);
    void addPoints(string rule, int frequency);
    
    bool isPalindrome(string word);
    bool noRepeatedLetters(string word);
    bool containsNoVowels(string word);
    bool containsNoConsonants(string word);
    bool alternatingVowelsConsonants(string word);
    bool alphabeticalOrder(string word);
    bool reverseAlphabeticalOrder(string word);
    bool startEndSameLetter(string word);
    bool containsRarityWord(string word);
    bool isRarityWord(string word);
    int rareLetters(string word); // Returns Q, X, Z
    int calculateScrabbleScore(string word);
    int consecutiveLetters(string word);

    //helper functions
    bool contains(string word, char letter);
};

#endif  // CHARACTERISTICS_H