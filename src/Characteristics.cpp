#include "Characteristics.h"
#include <string>
#include <cctype>
#include <unordered_set>
#include <algorithm>

using namespace std;

int Characteristics::getScore(string word) {
    score = 0;

    if (isPalindrome(word)) score += 500;  // PALINDROME
    if (noRepeatedLetters(word)) score += 100;  // NO REPEATED LETTERS
    if (containsNoVowels(word)) score += 500; else score += 25;  // CONTAINS NO VOWELS
    if (containsNoConsonants(word)) score += 500; else score += 25;  // CONTAINS NO CONSONANTS
    if (alphabeticalOrder(word)) score += 150;  // ALPHABETICAL ORDER
    if (startEndSameLetter(word)) score += 250;  // START AND END WITH SAME LETTER

    score += consecutiveLetters(word) * 150;  // CONSECUTIVE LETTERS
    score += rareLetters(word) * 75;  // RARE LETTERS
    score += wordLength * 10;  // WORD LENGTH
    score += syllables * 20;  // SYLLABLES
    score += definitions * 5  // DEFINITIONS
    score += calculateScrabbleScore(word) * 10;  // SCRABBLE SCORE

    return score;
}

bool Characteristics::isPalindrome(string word) {
  string tempWord = word;

  reverse(tempWord.begin(), tempWord.end());
  if (word == tempWord) {
    return true;
  } else {
    return false;
  }
}

bool Characteristics::noRepeatedLetters(string word) {
    unordered_set<char> seen;

    for (char ch : word) {
        if (seen.count(ch))
            return false;
        seen.insert(ch);
    }
    return true;
}

int Characteristics::consecutiveLetters(string word) {
    int currentRun = 1;
    int maxRun = 1;

    for (int i = 1; i < word.size(); ++i) {
        char prev = word[i-1];
        char curr = word[i];

        if (prev == curr) {
            currentRun++;
            maxRun = max(currentRun, maxRun);
        } else {
            currentRun = 1;
        }
    }
    return maxRun;
}

bool Characteristics::containsNoVowels(string word) {
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};

    for(unsigned int i = 0; i < 5; i++) {
        if(contains(word, vowels[i])) {
            return false;
        } 
    }

    return true;
}

bool Characteristics::containsNoConsonants(string word) {
    for (char ch : word) {
        bool isVowel = (ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u');
        if (!isVowel) return false;
    }
    return true;
}

 bool Characteristics::contains(string word, char letter) {
    for(unsigned int i = 0; i < word.size(); i++) {
        if(word.at(i) == letter) {
            return true;
        }
    }

    return false;
    
 }

bool Characteristics::alphabeticalOrder(string word) {
    for (int i = 1; i < word.size(); ++i) {
        char prev = word[i-1];
        char curr = word[i];

        if (curr < prev)
            return false;
    }
    return true;
}

bool Characteristic::reverseAlphabeticalOrder(string word) {
    for (int i = 1; i < word.size(); ++i) {
        char prev = word[i-1];
        char curr = word[i];

        if (curr > prev)
            return false;
    }
    return true;
}

bool Characteristics::startEndSameLetter(string word) {
    return (word.front() == word.back());
}

int Characteristics::rareLetters(string word) {
    auto isRare = [](char c) {
        return (c=='q' || c=='x' || c=='z');
    };

    int count = 0;
    for (char ch : word) {
        if (isRare(ch))
            count++;
    }
    return count;
}

int Characteristics::calculateScrabbleScore(string word) {
  int score = 0;

  for (int i = 0; i < word.length(); i++) {
    if (word.at(i) == 'a' || word.at(i) == 'e' || word.at(i) == 'i' || word.at(i) == 'o' || word.at(i) == 'u' || word.at(i) == 'l' || word.at(i) == 'n' || word.at(i) == 's' || word.at(i) == 't' || word.at(i) == 'r') {
      score += 1;
    } else if (word.at(i) == 'd' || word.at(i) == 'g') {
      score += 2;
    } else if (word.at(i) == 'b' || word.at(i) == 'c' || word.at(i) == 'm' || word.at(i) == 'p') {
      score += 3;
    } else if (word.at(i) == 'f' || word.at(i) == 'h' || word.at(i) == 'v' || word.at(i) == 'w' || word.at(i) == 'y') {
      score += 4;
    } else if (word.at(i) == 'k') {
      score += 5;
    } else if (word.at(i) == 'j' || word.at(i) == 'x') {
      score += 8;
    } else if (word.at(i) == 'q' || word.at(i) == 'z') {
      score += 10;
    }
  }
  return score;
}
