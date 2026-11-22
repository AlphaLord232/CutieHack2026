#include "../header/Characteristics.h"

void Characteristics::calculateCounts() {
    words = vector<string>();
    countPalindromes = 0;
    countNoRepeatedLetters = 0;
    countNoVowels = 0;
    countNoConsonants = 0;
    countAlternatingVowelsConsonants = 0;
    countAlphabeticalOrder = 0;
    countReverseAlphabeticalOrder = 0;
    countStartEndSameLetter = 0;
    countScrabbleScore20 = 0;
    countScrabbleScore30 = 0;
    countScrabbleScore40 = 0;
    countDoubleConsecutiveLetters = 0;
    countTripleConsecutiveLetters = 0;
    countContainsRarityWord = 0;
    countIsRarityWord = 0;
    countLengths = vector<int>(50, 0);

    ifstream fin("words.txt");
    if (!fin.is_open()) {
        cerr << "Error opening file for reading." << endl;
        return; // Exit the function if the file can't be opened
    }

    string word;
    while (fin >> word) {
        words.push_back(word);
        if (isPalindrome(word)) countPalindromes++;
        if (noRepeatedLetters(word)) countNoRepeatedLetters++;
        if (containsNoVowels(word)) countNoVowels++;
        if (containsNoConsonants(word)) countNoConsonants++;
        if (alternatingVowelsConsonants(word)) countAlternatingVowelsConsonants++;
        if (alphabeticalOrder(word)) countAlphabeticalOrder++;
        if (reverseAlphabeticalOrder(word)) countReverseAlphabeticalOrder++;
        if (startEndSameLetter(word)) countStartEndSameLetter++;
        if (calculateScrabbleScore(word) >= 20) countScrabbleScore20++;
        if (calculateScrabbleScore(word) >= 30) countScrabbleScore30++;
        if (calculateScrabbleScore(word) >= 40) countScrabbleScore40++;
        if (consecutiveLetters(word) >= 2) countDoubleConsecutiveLetters++;
        if (consecutiveLetters(word) >= 3) countTripleConsecutiveLetters++;
        if (containsRarityWord(word)) countContainsRarityWord++;
        if (isRarityWord(word)) countIsRarityWord++;
        countLengths.at(word.length())++;
    }

    fin.close();
}

void Characteristics::printCounts() {

    cout << endl << "--- Word Characteristics Summary ---" << endl;
    cout << "Total Words: " << words.size() << endl;
    cout << "Palindromes: " << countPalindromes << endl;
    cout << "No Repeated Letters: " << countNoRepeatedLetters << endl;
    cout << "No Vowels: " << countNoVowels << endl;
    cout << "No Consonants: " << countNoConsonants << endl;
    cout << "Alternating Vowels and Consonants: " << countAlternatingVowelsConsonants << endl;
    cout << "Alphabetical Order: " << countAlphabeticalOrder << endl;
    cout << "Reverse Alphabetical Order: " << countReverseAlphabeticalOrder << endl;
    cout << "Start and End with Same Letter: " << countStartEndSameLetter << endl;
    cout << "Scrabble Score >= 20: " << countScrabbleScore20 << endl;
    cout << "Scrabble Score >= 30: " << countScrabbleScore30 << endl;
    cout << "Scrabble Score >= 40: " << countScrabbleScore40 << endl;
    cout << "Double Consecutive Letters: " << countDoubleConsecutiveLetters << endl;
    cout << "Triple Consecutive Letters: " << countTripleConsecutiveLetters << endl;
    cout << "Contains Rarity Word: " << countContainsRarityWord << endl;
    cout << "Is Rarity Word: " << countIsRarityWord << endl;

    for (int i = 1; i < countLengths.size(); i++) {
        cout << "Length of " << i << ": " << countLengths.at(i) << endl;
    }
}

void Characteristics::addPoints(string rule, int frequency) {
    double odds = (double)frequency / words.size();
    int increment = 100 / odds;
    cout << "   " << rule << ": +" << increment;
    score += increment;
    
    if (odds > 0.1) {
        cout << " (Common)";
    } else if (odds > 0.02) {
        cout << " (Uncommon)";
    } else if (odds > 0.005) {
        cout << " (Rare)";
    } else if (odds > 0.001) {
        cout << " (Epic)";
    } else if (odds > 0.0001) {
        cout << " (Legendary)";
    } else {
        cout << " (Mythical)";
    }
    cout << endl;
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
    if (calculateScrabbleScore(word) >= 20) addPoints("Scrabble Score >= 20", countScrabbleScore20);  // SCRABBLE SCORE >= 20
    if (calculateScrabbleScore(word) >= 30) addPoints("Scrabble Score >= 30", countScrabbleScore30);  // SCRABBLE SCORE >= 30
    if (calculateScrabbleScore(word) >= 40) addPoints("Scrabble Score >= 40", countScrabbleScore40);  // SCRABBLE SCORE >= 40
    if (consecutiveLetters(word) >= 2)      addPoints("Double Consecutive Letters", countDoubleConsecutiveLetters);  // DOUBLE CONSECUTIVE LETTERS
    if (consecutiveLetters(word) >= 3)      addPoints("Triple Consecutive Letters", countTripleConsecutiveLetters);  // TRIPLE CONSECUTIVE LETTERS
    if (containsRarityWord(word))           addPoints("Contains Rarity Word", countContainsRarityWord);  // CONTAINS RARITY WORD
    if (isRarityWord(word))                 addPoints("Is Rarity Word", countIsRarityWord);  // IS RARITY WORD
    addPoints("Length of " + to_string(word.length()), countLengths.at(word.length()));  // LENGTH OF WORD

    cout << "-> SCORE: " << score << endl;
}

string Characteristics::randomWord() {
    if (words.empty()) return "";
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

void Characteristics::createJSONFile() {
    ofstream fout("file.json");

    fout << "{" << endl;
    fout << "  \"words\": [\"" << words.at(0) << "\"";
    for (int i = 1; i < words.size(); i++) {
        fout << ", \"" << words.at(i) << "\"";
    }
    fout << "  ]," << endl << "  \"counts\": {" << endl;
    fout << "    \"palindromes\": " << countPalindromes << "," << endl;
    fout << "    \"noRepeatedLetters\": " << countNoRepeatedLetters << "," << endl;
    fout << "    \"noVowels\": " << countNoVowels << "," << endl;
    fout << "    \"noConsonants\": " << countNoConsonants << "," << endl;
    fout << "    \"alternatingVowelsConsonants\": " << countAlternatingVowelsConsonants << "," << endl;
    fout << "    \"alphabeticalOrder\": " << countAlphabeticalOrder << "," << endl;
    fout << "    \"reverseAlphabeticalOrder\": " << countReverseAlphabeticalOrder << "," << endl;
    fout << "    \"startEndSameLetter\": " << countStartEndSameLetter << "," << endl;
    fout << "    \"scrabbleScore20\": " << countScrabbleScore20 << "," << endl;
    fout << "    \"scrabbleScore30\": " << countScrabbleScore30 << "," << endl;
    fout << "    \"scrabbleScore40\": " << countScrabbleScore40 << "," << endl;
    fout << "    \"doubleConsecutiveLetters\": " << countDoubleConsecutiveLetters << "," << endl;
    fout << "    \"tripleConsecutiveLetters\": " << countTripleConsecutiveLetters << "," << endl;
    fout << "    \"containsRarityWord\": " << countContainsRarityWord << "," << endl;
    fout << "    \"isRarityWord\": " << countIsRarityWord << "," << endl;
    fout << "    \"countLengths\": [" << countLengths.at(0);
    for (int i = 1; i < countLengths.size(); i++) {
        fout << ", " << countLengths.at(i);
    }
    fout << "    ]" << endl;
    fout << "  }" << endl;
    fout << "}" << endl;
}

// PRIVATE FUNCTIONS
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

bool Characteristics::containsNoVowels(string word) {
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    for (unsigned int i = 0; i < 5; i++) {
        if (contains(word, vowels[i])) {
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

bool Characteristics::containsRarityWord(string word) {
    string rarityWords[] = {"common", "uncommon", "rare", "epic", "legendary", "mythical"};
    for (string rarityWord : rarityWords) {
        if (word.find(rarityWord) != string::npos) return true;
    }
    return false;
}

bool Characteristics::isRarityWord(string word) {
    string rarityWords[] = {"common", "uncommon", "rare", "epic", "legendary", "mythical"};
    for (string rarityWord : rarityWords) {
        if (word == rarityWord) return true;
    }
    return false;
}

bool Characteristics::contains(string word, char letter) {
    for (unsigned int i = 0; i < word.size(); i++) {
        if (word.at(i) == letter) {
            return true;
        }
    }
    return false;
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

int Characteristics::rareLetters(string word) {
    auto isRare = [](char c) {
        return (c=='q' || c=='x' || c=='z');
    };

    int count = 0;
    for (char ch : word) if (isRare(ch)) count++;
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