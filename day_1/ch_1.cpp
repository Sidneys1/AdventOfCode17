#include <iomanip>
#include <iostream>
#include <string>

int main(int /* argc */, char * /* argv */ []) {
    std::string input;
    std::cin >> input;
    std::cout << "Input is: " << std::quoted(input) << std::endl;
    auto len = input.size();
    input += input[0];
    int i = 0;
    int sum = 0;
    std::cout << "0";
    for (auto it = input.begin(); i < len; i++, it++) {
        if (*it != *(it + 1)) {
            continue;
        }
        sum += (*it) - 448;
        std::cout << " + " << (*it) - 48 << " = " << sum;
    }

    std::cout << std::endl << "Sum is: " << sum << std::endl;
}
