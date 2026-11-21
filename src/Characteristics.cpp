#include "../header/Characteristics.h"

void Characteristics::calculateCounts() {
    numWords = 0;
    countPalindromes = 0;
    countNoRepeatedLetters = 0;
    countNoVowels = 0;
    countNoConsonants = 0;
    countAlternatingVowelsConsonants = 0;
    countAlphabeticalOrder = 0;
    countReverseAlphabeticalOrder = 0;
    countStartEndSameLetter = 0;

    ifstream fin("words.txt");
    if (!fin.is_open()) {
        cerr << "Error opening file for reading." << endl;
        return; // Exit the function if the file can't be opened
    }

    string word;
    while (fin >> word) {
        numWords++;
        if (isPalindrome(word)) countPalindromes++;
        if (noRepeatedLetters(word)) countNoRepeatedLetters++;
        if (containsNoVowels(word)) countNoVowels++;
        if (containsNoConsonants(word)) countNoConsonants++;
        if (alternatingVowelsConsonants(word)) countAlternatingVowelsConsonants++;
        if (alphabeticalOrder(word)) countAlphabeticalOrder++;
        if (reverseAlphabeticalOrder(word)) countReverseAlphabeticalOrder++;
        if (startEndSameLetter(word)) countStartEndSameLetter++;
    }

    fin.close();

    cout << endl << "--- Word Characteristics Summary ---" << endl;
    cout << "Total Words: " << numWords << endl;
    cout << "Palindromes: " << countPalindromes << endl;
    cout << "No Repeated Letters: " << countNoRepeatedLetters << endl;
    cout << "No Vowels: " << countNoVowels << endl;
    cout << "No Consonants: " << countNoConsonants << endl;
    cout << "Alternating Vowels and Consonants: " << countAlternatingVowelsConsonants << endl;
    cout << "Alphabetical Order: " << countAlphabeticalOrder << endl;
    cout << "Reverse Alphabetical Order: " << countReverseAlphabeticalOrder << endl;
    cout << "Start and End with Same Letter: " << countStartEndSameLetter << endl;
}

void Characteristics::addPoints(string rule, int frequency) {
    cout << "   " << rule << ": +" << frequency << endl;
    score += (double)numWords / frequency * 100;
}

void Characteristics::printScore(string word) {

    score = 0;

    cout << endl << "Word: " << word << endl;

    if (isPalindrome(word))                 addPoints("Palindrome", countPalindromes);  // PALINDROME
    if (noRepeatedLetters(word))            addPoints("No Repeated Letters", countNoRepeatedLetters);  // NO REPEATED LETTERS
    if (containsNoVowels(word))             addPoints("Contains No Vowels", countNoVowels);  // CONTAINS NO VOWELS
    if (containsNoConsonants(word))         addPoints("Contains No Consonants", countNoConsonants); // CONTAINS NO CONSONANTS
    if (alternatingVowelsConsonants(word))  addPoints("Alternating Vowels and Consonants", countAlternatingVowelsConsonants);  // ALTERNATING BETWEEN VOWELS AND CONSONANTS
    if (alphabeticalOrder(word))            addPoints("Alphabetical Order", countAlphabeticalOrder);  // ALPHABETICAL ORDER
    if (reverseAlphabeticalOrder(word))     addPoints("Reverse Alphabetical Order", countReverseAlphabeticalOrder);  // REVERSE ALPHABETICAL ORDER
    if (startEndSameLetter(word))           addPoints("Start and End with Same Letter", countStartEndSameLetter);  // START AND END WITH SAME LETTER

    cout << "-> SCORE: " << score << endl;

    // score += consecutiveLetters(word) * 150;  // CONSECUTIVE LETTERS
    // score += rareLetters(word) * 75;  // RARE LETTERS
    // score += wordLength * 10;  // WORD LENGTH
    // score += syllables * 20;  // SYLLABLES
    // score += definitions * 5;  // DEFINITIONS
    // score += calculateScrabbleScore(word) * 10;  // SCRABBLE SCORE
}

bool Characteristics::isPalindrome(string word) {
  string tempWord = word;
  reverse(tempWord.begin(), tempWord.end());
  return word == tempWord;
}

bool Characteristics::noRepeatedLetters(string word) {
    unordered_set<char> seen;
    for (char ch : word) {
        if (seen.count(ch)) return false;
        seen.insert(ch);
    }
    return true;
}

int Characteristics::consecutiveLetters(string word) {
    int currentRun = 1;
    int maxRun = 1;

    for (int i = 1; i < word.size(); ++i) {
        if (word[i-1] == word[i]) {
            currentRun++;
            maxRun = max(currentRun, maxRun);
        } else currentRun = 1;
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

bool Characteristics::alternatingVowelsConsonants(string word) {
    auto isVowel = [](char c) {
        return (c=='a'||c=='e'||c=='i'||c=='o'||c=='u');
    };
    int prevKind = -1; // -1 = none yet, 1 = vowel, 0 = consonant

    for (char ch : word) {
        int currKind = isVowel(ch) ? 1 : 0;
        if (currKind == prevKind)
            return false;
        prevKind = currKind;
    }
    return (prevKind != -1);
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

bool Characteristics::reverseAlphabeticalOrder(string word) {
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
    switch(word.at(i)) {
      case 'a': case 'e': case 'i': case 'o': case 'u':
      case 'l': case 'n': case 's': case 't': case 'r':
        score += 1; break;
      case 'd': case 'g':
        score += 2; break;
      case 'b': case 'c': case 'm': case 'p':
        score += 3; break;
      case 'f': case 'h': case 'v': case 'w': case 'y':
        score += 4; break;
      case 'k':
        score += 5; break;
      case 'j': case 'x':
        score += 8; break;
      case 'q': case 'z':
        score += 10; break;
    }
  }
  return score;
}
