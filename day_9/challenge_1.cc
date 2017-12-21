#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stack>
#include <vector>

enum Mode { GROUP, GARBAGE };

int main(int /* argc */, char * /* argv */ []) {
    std::string input;
    std::cin >> input;

    Mode state = Mode::GROUP;
    std::vector<int> group_values = {1};
    std::stack<int> stack;
    stack.push(1);
    for (size_t pos = 1; (pos + 1) < input.size(); pos++) {
        switch (state) {
        case Mode::GROUP: {
            switch (input[pos]) {
            case '{': {
                int value = stack.top() + 1;
                stack.push(value);
            } break;
            case '}': {
                group_values.push_back(stack.top());
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
                state = Mode::GROUP;
            } break;
            default: { } break; }
        } break;
        }
    }
    if (!group_values.empty()) {
        std::cout << "Sum of all groups: "
                  << std::accumulate(group_values.begin(), group_values.end(),
                                     0)
                  << std::endl;
    }
    return 0;
}