#include "../header/Characteristics.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Characteristics characteristics;
    characteristics.calculateCounts();
    characteristics.createJSONFile();

    int numRandomWords = 0;
    cout << endl << "--- Random Word Scores ---" << endl;
    cout << "Enter a number of random words to score (0 to exit): ";
    if (cin >> numRandomWords && numRandomWords > 0) {
        for (int i = 0; i < numRandomWords; ++i) {
            characteristics.printScore(characteristics.randomWord());
        }
    }

    cout << endl;
    return 0;
}