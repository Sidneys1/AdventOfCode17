#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace aoc {
struct Program {
    std::string name;
    int weight, computed_weight, usual_weight;
    std::unordered_set<std::string> children_names;
    std::vector<std::shared_ptr<Program>> children;
    std::pair<std::shared_ptr<Program>, int> unbalanced;

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

    int compute_weight() {
        std::unordered_map<int, int> frequency;
        computed_weight =
            weight +
            std::accumulate(children.begin(), children.end(), 0,
                            [&frequency](int i, std::shared_ptr<Program> item) {
                                int w = item->compute_weight();
                                frequency[w]++;
                                return i + w;
                            });

        if (frequency.size() > 1) {
            std::cout << "Found imbalance: " << name << ": ";
            std::pair<int, int> min, max;
            min = *std::min_element(
                frequency.begin(), frequency.end(),
                [](std::pair<int, int> i, std::pair<int, int> j) {
                    return i.second < j.second;
                });
            max = *std::max_element(
                frequency.begin(), frequency.end(),
                [](std::pair<int, int> i, std::pair<int, int> j) {
                    return i.second < j.second;
                });
            usual_weight = max.first;
            auto unbal =
                std::find_if(children.begin(), children.end(),
                             [&min](std::shared_ptr<Program> p) {
                                 return p->computed_weight == min.first;
                             });
            unbalanced = std::make_pair(*unbal, min.first);
            std::cout << *(*unbal) << " should be " << usual_weight
                      << std::endl;
        }

        return computed_weight;
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

    friend std::ostream &operator<<(std::ostream &stream, const Program &data) {
        stream << data.name << " (" << data.weight << ':'
               << data.computed_weight << ") ";
        for (auto x : data.children) {
            stream << x->name << ", ";
        }
        return stream;
    }
};
} // namespace aoc
