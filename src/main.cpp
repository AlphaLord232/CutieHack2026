#include "../header/Characteristics.h"

int main() {

    Characteristics characteristics;
    characteristics.calculateCounts();
    characteristics.printScore("racecar");
    characteristics.printScore("strengths");
    characteristics.printScore("queue");
    characteristics.printScore("rhythm");
    characteristics.printScore("a");
    characteristics.printScore("I");
    characteristics.printScore("xylophone");
    characteristics.printScore("example");
    characteristics.printScore("meow");
    characteristics.printScore("noon");
    characteristics.printScore("ultrauncommon");
    characteristics.printScore("legendary");
    characteristics.printCounts();

    cout << endl;

    return 0;
}