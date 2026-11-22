#include "../header/Characteristics.h"

int main() {

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    Characteristics characteristics;
    // vector<string> words = {"racecar", "strengths", "queue", "rhythm", "a", "I", "xylophone", "example", "meow", "noon", "ultrauncommon", "legendary"};
    int numRandomWords;

    characteristics.calculateCounts();
    characteristics.createJSONFile();
    // for (const string& word : words) {
    //     characteristics.printScore(word);
    // }

    cout << endl << "--- Random Word Scores ---" << endl;
    cout << "Enter a number of random words to score (0 to exit): ";
    cin >> numRandomWords;
    for (int i = 0; i < numRandomWords; ++i) {
        characteristics.printScore(characteristics.randomWord());
    }
    // characteristics.printCounts();

    cout << endl;

    return 0;
}