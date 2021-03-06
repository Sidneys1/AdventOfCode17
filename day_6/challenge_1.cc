#include <array>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

#define BANKS 16

int main(int /* argc */, char * /* argv */ []) {
    std::array<uint32_t, BANKS> banks = {};
    std::unordered_set<std::string> history;
    {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream line_stream(line);
        for (int i = 0; i < BANKS; i++) {
            std::string tok;
            std::getline(line_stream, tok, '\t');
            banks.at(i) = std::stoul(tok);
        }
    }

    std::cout << "Initial bank values are:\n\t";
    for (auto x : banks) {
        std::cout << x << '\t';
    }
    std::cout << std::endl;

    int cycles = 0;
    do {
        uint32_t max = 0, max_index = 0;
        for (int i = 0; i < BANKS; i++) {
            if (banks.at(i) > max) {
                max_index = i;
                max = banks.at(i);
            }
        }
        uint64_t distribute = banks.at(max_index);
        banks.at(max_index) = 0;
        max = max_index + 1;
        do {
            if (max == BANKS) {
                max = 0;
            }
            banks.at(max++)++;
        } while (--distribute > 0);
        std::stringstream ss;
        for (auto x : banks) {
            ss << x << ' ';
        }
        cycles++;
        if (history.find(ss.str()) != history.end()) {
            break;
        }
        history.insert(ss.str());
    } while (true);

    std::cout << "Took " << cycles << " cycles." << std::endl;

    return 0;
}