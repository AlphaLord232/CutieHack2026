#ifndef CHARACTERISTICS_H
#define CHARACTERISTICS_H

#include <iostream>
using namespace std;

class Characteristics {
  private:
    int score;
    int wordLength;
    int syllables;
    int definitions;
    
  public:
    int getScore(string word);
    string getRarity(); 
    
    bool isPalindrome(string word);
    bool noRepeatedLetters(string word); //done
    int consecutiveLetters(string word); //done
    bool containsNoVowels(string word); //done
    bool containsNoConsonants(string word); //done
    bool alphabeticalOrder(string word); //done
    bool reverseAlphabeticalOrder(string word);
    bool startEndSameLetter(string word); //done
    int rareLetters(string word); //done returns number of Q,X,Z
    int calculateScrabbleScore(string word);

    //helper functions
    bool contains(string word, char letter);
};

#endif  // CHARACTERISTICS_H