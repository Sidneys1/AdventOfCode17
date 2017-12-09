#include <iostream>
#include <string>
#include <vector>

int main(int /* argc */, char * /* argv */ []) {
    std::vector<int> trampoline;
    {
        std::string line;
        do {
            std::getline(std::cin, line);
            if (line.empty()) {
                break;
            }
            trampoline.push_back(std::stoi(line));
        } while (true);
    }

    std::cout << "There are " << trampoline.size() << " trampoline entries."
              << std::endl;

    int position = 0, moves = 0, max = trampoline.size();

    do {
        int dist = trampoline[position];
        trampoline[position] += dist >= 3 ? -1 : 1;
        position += dist;
        moves++;
    } while (position >= 0 && position < max);

    std::cout << "Completed in " << moves << " moves." << std::endl;

    return 0;
}