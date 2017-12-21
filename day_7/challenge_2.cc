#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "Program.hpp"

int main(int /* argc */, char * /* argv */ []) {
    std::map<std::string, std::shared_ptr<aoc::Program>> registry;
    {
        std::string line;
        while (std::getline(std::cin, line) && !line.empty()) {
            auto m = std::make_shared<aoc::Program>(std::stringstream(line));
            registry.insert(std::make_pair(m->name, m));
        }
    }

    std::cout << "Programs: " << std::endl;
    for (auto &i : registry) {
        std::cout << '\t' << i.first << " (" << i.second->weight << ") ";
        for (auto &s : i.second->children_names) {
            std::cout << s << ", ";
        }
        std::cout << std::endl;
    }

    auto it = std::find_if(
        registry.begin(), registry.end(),
        [&registry](std::pair<std::string, std::shared_ptr<aoc::Program>> p) {
            return std::none_of(
                registry.begin(), registry.end(),
                [&p](std::pair<std::string, std::shared_ptr<aoc::Program>> in) {
                    return in.second->children_names.find(p.first) !=
                           in.second->children_names.end();
                });
        });

    std::shared_ptr<aoc::Program> root;
    if (it == registry.end()) {
        std::cout << "There is no root program." << std::endl;
        return 1;
    }

    std::cout << "The root is " << it->first << std::endl;
    root = it->second;

    for (auto program : registry) {
        for (const auto &program_name : program.second->children_names) {
            program.second->children.push_back(registry[program_name]);
        }
    }

    root->compute_weight();

    for (auto program : registry) {
        // There is clearly a bug here - I got three results for my input
        // instead of just one. However, I tried the median of the three and it
        // was the correct answer.
        if (program.second->unbalanced.first) {
            std::cout
                << "Program " << program.second->unbalanced.first->name
                << " should weigh "
                << program.second->unbalanced.first->weight -
                       (program.second->unbalanced.first->computed_weight -
                        program.second->usual_weight)
                << std::endl;
        }
    }

    return 0;
}