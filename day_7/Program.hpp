#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace aoc {
struct Program {
    std::string name;
    int weight;
    std::unordered_set<std::string> children_names;
    std::vector<std::shared_ptr<Program>> children;

    Program() = default;

    Program(std::istream &&line_stream) {
        std::string temp;
        std::getline(line_stream, name, ' ');
        line_stream.ignore(); // Skips '('
        std::getline(line_stream, temp, ')');
        weight = std::stoi(temp);
        line_stream.ignore(4); // Skips ' -> '
        while (std::getline(line_stream, temp, ',')) {
            children_names.insert(temp);
            line_stream.ignore();
        }
    }

    Program(std::istream &line_stream) {
        std::string temp;
        std::getline(line_stream, name, ' ');
        line_stream.ignore(); // Skips '('
        std::getline(line_stream, temp, ')');
        weight = std::stoi(temp);
        line_stream.ignore(4); // Skips ' -> '
        while (std::getline(line_stream, temp, ',')) {
            children_names.insert(temp);
            line_stream.ignore();
        }
    }

    friend std::istream &operator>>(std::istream &line_stream, Program &data) {
        std::string weight;
        std::getline(line_stream, data.name, ' ');
        line_stream.ignore(); // Skips '('
        std::getline(line_stream, weight, ')');
        data.weight = std::stoi(weight);
        line_stream.ignore(4); // Skips ' -> '
        while (std::getline(line_stream, weight, ',')) {
            data.children_names.insert(weight);
            line_stream.ignore();
        }
        return line_stream;
    }
};
} // namespace aoc
