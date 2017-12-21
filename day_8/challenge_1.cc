#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct parsed_line {
    explicit parsed_line(const std::string &input) {
        std::stringstream sstream(input);
        std::getline(sstream, target, ' ');
        std::getline(sstream, instruction, ' ');
        std::string temp;
        std::getline(sstream, temp, ' ');
        value_1 = std::stoi(temp);
        sstream.ignore(3); // Consume 'if '
        std::getline(sstream, conditional, ' ');
        std::getline(sstream, op, ' ');
        std::getline(sstream, temp, ' ');
        value_2 = std::stoi(temp);
    }

    friend std::ostream &operator<<(std::ostream &stream,
                                    const parsed_line &item) {
        return stream << item.target << ' ' << item.instruction << ' '
                      << item.value_1 << " if " << item.conditional << ' '
                      << item.op << ' ' << item.value_2;
    }

    std::string target, instruction, conditional, op;
    int value_1, value_2;
};

int main(int /* argc */, char * /* argv */ []) {
    std::vector<std::unique_ptr<parsed_line>> input;
    {
        std::string line;
        do {
            std::getline(std::cin, line);
            if (line.empty()) {
                break;
            }
            input.push_back(std::make_unique<parsed_line>(line));
        } while (true);
    }

    std::unordered_map<std::string, int> registers;

    for (const auto &item : input) {
        std::cout << *item << std::endl;

        if (registers.find(item->conditional) == registers.end()) {
            registers.insert({item->conditional, 0});
        }

        int conditional = registers[item->conditional];
        bool success = false;
        success = (item->op == "==" && conditional == item->value_2) ||
                  (item->op == "!=" && conditional != item->value_2) ||
                  (item->op == ">=" && conditional >= item->value_2) ||
                  (item->op == "<=" && conditional <= item->value_2) ||
                  (item->op == ">" && conditional > item->value_2) ||
                  (item->op == "<" && conditional < item->value_2);
        if (success) {
            std::cout << "\t" << item->conditional << '[' << conditional << "] "
                      << item->op << ' ' << item->value_2 << std::endl;
            if (registers.find(item->target) == registers.end()) {
                registers.insert({item->target, 0});
            }
            if (item->instruction == "inc") {
                std::cout << "\t" << item->target << '['
                          << registers[item->target] << "] + " << item->value_1
                          << " = ";
                registers[item->target] += item->value_1;
                std::cout << registers[item->target] << std::endl;
            } else if (item->instruction == "dec") {
                std::cout << "\t" << item->target << '['
                          << registers[item->target] << "] - " << item->value_1
                          << " = ";
                registers[item->target] -= item->value_1;
                std::cout << registers[item->target] << std::endl;
            } else {
                std::cerr << "Invalid instruction " << item->instruction
                          << " encountered!" << std::endl;
                return 1;
            }
        }
    }

    int largest = std::numeric_limits<int>::min();
    for (const auto &reg : registers) {
        std::cout << reg.first << '[' << reg.second << ']' << std::endl;
        if (reg.second > largest) {
            largest = reg.second;
        }
    }
    std::cout << "Largest register value is " << largest << std::endl;

    return 0;
}