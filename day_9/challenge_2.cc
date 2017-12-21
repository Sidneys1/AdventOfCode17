#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stack>
#include <string>
#include <vector>

enum Mode { GROUP, GARBAGE };

int main(int /* argc */, char * /* argv */ []) {
    std::string input;
    std::getline(std::cin, input);

    Mode state = Mode::GROUP;
    std::stack<int> stack;
    stack.push(1);
    int garbage = 0;
    for (size_t pos = 1; (pos + 1) < input.size(); pos++) {
        switch (state) {
        case Mode::GROUP: {
            switch (input[pos]) {
            case '{': {
                int value = stack.top() + 1;
                stack.push(value);
            } break;
            case '}': {
                stack.pop();
            } break;
            case '<': {
                state = Mode::GARBAGE;
            } break;
            case ',':
                break;
            default: { return 1; }
            }
        } break;
        case Mode::GARBAGE: {
            switch (input[pos]) {
            case '!': {
                pos++;
            } break;
            case '>': {
                std::cout << std::endl;
                state = Mode::GROUP;
            } break;
            default: {
                std::cout << input[pos];
                garbage++;
            } break;
            }
        } break;
        }
    }
    std::cout << "Garbage Characters: " << garbage << std::endl;
    return 0;
}