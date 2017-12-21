#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

int main(int /* argc */, char * /* argv */ []) {
    int width = 1;
    int height = 1;
    int x = 0, y = 0;
    int pos = 1, target = 1;
    std::cout << "Please enter target position: ";
    std::string targetString;
    std::cin >> targetString;
    try {
        target = std::stoi(targetString);
    } catch (const std::invalid_argument &ex) {
        std::cerr << "Could not convert input: " << std::quoted(targetString)
                  << " (" << ex.what() << ")" << std::endl;
        return 1;
    } catch (const std::out_of_range &ex) {
        std::cerr << "Input was out of range of an int ("
                  << std::numeric_limits<int>::min() << " - "
                  << std::numeric_limits<int>::max()
                  << "): " << std::quoted(targetString) << " (" << ex.what()
                  << ")" << std::endl;
        return 1;
    }
    while (pos < target) {
        // Go right
        int togo = width++;
        while (togo-- > 0) {
            ++x;
            if (++pos == target) {
                std::cout << "Hit target of " << pos << " at " << x << "," << y
                          << ". Taxicab is " << (abs(x) + abs(y)) << std::endl;
                return 0;
            }
        }

        // Go up
        togo = height++;
        while (togo-- > 0) {
            ++y;
            if (++pos == target) {
                std::cout << "Hit target of " << pos << " at " << x << "," << y
                          << ". Taxicab is " << (abs(x) + abs(y)) << std::endl;
                return 0;
            }
        }

        // Go left
        togo = width++;
        while (togo-- > 0) {
            --x;
            if (++pos == target) {
                std::cout << "Hit target of " << pos << " at " << x << "," << y
                          << ". Taxicab is " << (abs(x) + abs(y)) << std::endl;
                return 0;
            }
        }

        // Go down
        togo = height++;
        while (togo-- > 0) {
            --y;
            if (++pos == target) {
                std::cout << "Hit target of " << pos << " at " << x << "," << y
                          << ". Taxicab is " << (abs(x) + abs(y)) << std::endl;
                return 0;
            }
        }
    }

    return 0;
}