#include "../header/Characteristics.h"
#include <cctype>

static string toLowerStr(const string& s) {
    string out = s;
    for (char& c : out) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return out;
}

void Characteristics::calculateCounts() {
    words.clear();
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
    countLengths.assign(50, 0);

    ifstream fin("words.txt");
    if (!fin.is_open()) {
        cerr << "Error opening words.txt for reading." << endl;
        return;
    }

    string rawWord;
    while (fin >> rawWord) {
        string word = toLowerStr(rawWord);
        if (word.empty()) continue;

        words.push_back(word);

        if (isPalindrome(word)) countPalindromes++;
        if (noRepeatedLetters(word)) countNoRepeatedLetters++;
        if (containsNoVowels(word)) countNoVowels++;
        if (containsNoConsonants(word)) countNoConsonants++;
        if (alternatingVowelsConsonants(word)) countAlternatingVowelsConsonants++;
        if (alphabeticalOrder(word)) countAlphabeticalOrder++;
        if (reverseAlphabeticalOrder(word)) countReverseAlphabeticalOrder++;
        if (startEndSameLetter(word)) countStartEndSameLetter++;

        int scrabble = calculateScrabbleScore(word);
        if (scrabble >= 20) countScrabbleScore20++;
        if (scrabble >= 30) countScrabbleScore30++;
        if (scrabble >= 40) countScrabbleScore40++;

        int consec = consecutiveLetters(word);
        if (consec >= 2) countDoubleConsecutiveLetters++;
        if (consec >= 3) countTripleConsecutiveLetters++;

        if (containsRarityWord(word)) countContainsRarityWord++;
        if (isRarityWord(word)) countIsRarityWord++;

        if (word.size() >= countLengths.size()) {
            countLengths.resize(word.size() + 1, 0);
        }
        countLengths[word.size()]++;
    }

    fin.close();
}

void Characteristics::printCounts() const {
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

    for (size_t i = 1; i < countLengths.size(); i++) {
        if (countLengths[i] > 0) {
            cout << "Length of " << i << ": " << countLengths[i] << endl;
        }
    }
}

void Characteristics::addPoints(const string& rule, int frequency) {
    if (words.empty()) return;

    int effectiveFreq = max(1, frequency);
    double odds = static_cast<double>(effectiveFreq) / static_cast<double>(words.size());
    int increment = static_cast<int>(100.0 / odds);

    score += increment;
    cout << "   " << rule << ": +" << increment;

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

void Characteristics::printScore(const string& rawWord) {
    string word = toLowerStr(rawWord);
    if (word.empty()) return;

    score = 0;
    cout << endl << "Word: " << word << endl;

    if (isPalindrome(word))                 addPoints("Palindrome", countPalindromes);
    if (noRepeatedLetters(word))            addPoints("No Repeated Letters", countNoRepeatedLetters);
    if (containsNoVowels(word))             addPoints("Contains No Vowels", countNoVowels);
    if (containsNoConsonants(word))         addPoints("Contains No Consonants", countNoConsonants);
    if (alternatingVowelsConsonants(word))  addPoints("Alternating Vowels and Consonants", countAlternatingVowelsConsonants);
    if (alphabeticalOrder(word))            addPoints("Alphabetical Order", countAlphabeticalOrder);
    if (reverseAlphabeticalOrder(word))     addPoints("Reverse Alphabetical Order", countReverseAlphabeticalOrder);
    if (startEndSameLetter(word))           addPoints("Start and End with Same Letter", countStartEndSameLetter);
    if (calculateScrabbleScore(word) >= 20) addPoints("Scrabble Score >= 20", countScrabbleScore20);
    if (calculateScrabbleScore(word) >= 30) addPoints("Scrabble Score >= 30", countScrabbleScore30);
    if (calculateScrabbleScore(word) >= 40) addPoints("Scrabble Score >= 40", countScrabbleScore40);
    if (consecutiveLetters(word) >= 2)      addPoints("Double Consecutive Letters", countDoubleConsecutiveLetters);
    if (consecutiveLetters(word) >= 3)      addPoints("Triple Consecutive Letters", countTripleConsecutiveLetters);
    if (containsRarityWord(word))           addPoints("Contains Rarity Word", countContainsRarityWord);
    if (isRarityWord(word))                 addPoints("Is Rarity Word", countIsRarityWord);

    int lenFreq = (word.size() < countLengths.size()) ? countLengths[word.size()] : 0;
    addPoints("Length of " + to_string(word.size()), lenFreq);

    cout << "-> SCORE: " << score << endl;
}

string Characteristics::randomWord() const {
    if (words.empty()) return "";
    size_t randomIndex = static_cast<size_t>(rand()) % words.size();
    return words[randomIndex];
}

void Characteristics::createJSONFile(const string& outputPath) const {
    ofstream fout(outputPath);
    if (!fout.is_open()) {
        cerr << "Warning: Could not write JSON to " << outputPath << " (falling back to file.json)" << endl;
        fout.open("file.json");
        if (!fout.is_open()) {
            cerr << "Error opening file.json for writing." << endl;
            return;
        }
    }

    fout << "{\n";
    fout << "  \"totalWords\": " << words.size() << ",\n";
    fout << "  \"counts\": {\n";
    fout << "    \"palindromes\": " << countPalindromes << ",\n";
    fout << "    \"noRepeatedLetters\": " << countNoRepeatedLetters << ",\n";
    fout << "    \"noVowels\": " << countNoVowels << ",\n";
    fout << "    \"noConsonants\": " << countNoConsonants << ",\n";
    fout << "    \"alternatingVowelsConsonants\": " << countAlternatingVowelsConsonants << ",\n";
    fout << "    \"alphabeticalOrder\": " << countAlphabeticalOrder << ",\n";
    fout << "    \"reverseAlphabeticalOrder\": " << countReverseAlphabeticalOrder << ",\n";
    fout << "    \"startEndSameLetter\": " << countStartEndSameLetter << ",\n";
    fout << "    \"scrabbleScore20\": " << countScrabbleScore20 << ",\n";
    fout << "    \"scrabbleScore30\": " << countScrabbleScore30 << ",\n";
    fout << "    \"scrabbleScore40\": " << countScrabbleScore40 << ",\n";
    fout << "    \"doubleConsecutiveLetters\": " << countDoubleConsecutiveLetters << ",\n";
    fout << "    \"tripleConsecutiveLetters\": " << countTripleConsecutiveLetters << ",\n";
    fout << "    \"containsRarityWord\": " << countContainsRarityWord << ",\n";
    fout << "    \"isRarityWord\": " << countIsRarityWord << ",\n";
    fout << "    \"countLengths\": [";
    for (size_t i = 0; i < countLengths.size(); i++) {
        fout << countLengths[i];
        if (i + 1 < countLengths.size()) fout << ", ";
    }
    fout << "]\n";
    fout << "  }\n";
    fout << "}\n";
    fout.close();
}

// PRIVATE FUNCTIONS
bool Characteristics::isPalindrome(const string& word) const {
    string tempWord = word;
    reverse(tempWord.begin(), tempWord.end());
    return word == tempWord;
}

bool Characteristics::noRepeatedLetters(const string& word) const {
    unordered_set<char> seen;
    for (char ch : word) {
        if (seen.count(ch)) return false;
        seen.insert(ch);
    }
    return true;
}

bool Characteristics::containsNoVowels(const string& word) const {
    const char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    for (char v : vowels) {
        if (contains(word, v)) return false;
    }
    return true;
}

bool Characteristics::containsNoConsonants(const string& word) const {
    for (char ch : word) {
        bool isVowel = (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
        if (!isVowel) return false;
    }
    return !word.empty();
}

bool Characteristics::alternatingVowelsConsonants(const string& word) const {
    auto isVowel = [](char c) {
        return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    };
    int prevKind = -1;
    for (char ch : word) {
        int currKind = isVowel(ch) ? 1 : 0;
        if (currKind == prevKind) return false;
        prevKind = currKind;
    }
    return (prevKind != -1);
}

bool Characteristics::alphabeticalOrder(const string& word) const {
    for (size_t i = 1; i < word.size(); ++i) {
        if (word[i] < word[i - 1]) return false;
    }
    return !word.empty();
}

bool Characteristics::reverseAlphabeticalOrder(const string& word) const {
    for (size_t i = 1; i < word.size(); ++i) {
        if (word[i] > word[i - 1]) return false;
    }
    return !word.empty();
}

bool Characteristics::startEndSameLetter(const string& word) const {
    if (word.empty()) return false;
    return word.front() == word.back();
}

bool Characteristics::containsRarityWord(const string& word) const {
    const string rarityWords[] = {"common", "uncommon", "rare", "epic", "legendary", "mythical"};
    for (const string& rarityWord : rarityWords) {
        if (word.find(rarityWord) != string::npos) return true;
    }
    return false;
}

bool Characteristics::isRarityWord(const string& word) const {
    const string rarityWords[] = {"common", "uncommon", "rare", "epic", "legendary", "mythical"};
    for (const string& rarityWord : rarityWords) {
        if (word == rarityWord) return true;
    }
    return false;
}

bool Characteristics::contains(const string& word, char letter) const {
    return word.find(letter) != string::npos;
}

int Characteristics::consecutiveLetters(const string& word) const {
    if (word.empty()) return 0;
    int currentRun = 1;
    int maxRun = 1;
    for (size_t i = 1; i < word.size(); ++i) {
        if (word[i - 1] == word[i]) {
            currentRun++;
            maxRun = max(currentRun, maxRun);
        } else {
            currentRun = 1;
        }
    }
    return maxRun;
}

int Characteristics::rareLetters(const string& word) const {
    int count = 0;
    for (char ch : word) {
        if (ch == 'q' || ch == 'x' || ch == 'z') count++;
    }
    return count;
}

int Characteristics::calculateScrabbleScore(const string& word) const {
    int score = 0;
    for (char ch : word) {
        switch (ch) {
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
            default:
                break;
        }
    }
    return score;
}