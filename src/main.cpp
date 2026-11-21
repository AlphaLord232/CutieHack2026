#include "../header/Characteristics.h"

int main() {

    Characteristics characteristics;
    characteristics.calculateCounts();
    characteristics.printScore("example");
    characteristics.printScore("meow");
    characteristics.printScore("noon");
    characteristics.printScore("racecar");
    characteristics.printScore("strengths");
    characteristics.printScore("queue");
    characteristics.printScore("rhythm");
    characteristics.printScore("a");
    characteristics.printScore("I");

    cout << endl;

    return 0;
}