#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "Passphrase.hpp"

int main(int /* argc */, char * /* argv */ []) {
    std::vector<Passphrase> rows;
    do {
        Passphrase row;
        std::cin >> row;
        if (row.size() == 0) {
            break;
        }
        rows.push_back(row);
    } while (true);

    std::cout << "There are " << rows.size() << " passphrases, of which "
              << std::count_if(rows.begin(), rows.end(),
                               [](Passphrase &p) { return p.valid(); })
              << " are valid." << std::endl;

    return 0;
}