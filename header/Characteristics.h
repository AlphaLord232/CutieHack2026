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
    
  public:
    void calculateCounts();
    void printScore(string word);
    void addPoints(string rule, int frequency);
    string getRarity(); 
    
    bool isPalindrome(string word);
    bool noRepeatedLetters(string word); //done
    int consecutiveLetters(string word); //done
    bool containsNoVowels(string word); //done
    bool containsNoConsonants(string word); //done
    bool alternatingVowelsConsonants(string word); //done
    bool alphabeticalOrder(string word); //done
    bool reverseAlphabeticalOrder(string word); //done
    bool startEndSameLetter(string word); //done
    int rareLetters(string word); //done returns number of Q,X,Z
    int calculateScrabbleScore(string word);

    //helper functions
    bool contains(string word, char letter);
};

#endif  // CHARACTERISTICS_H