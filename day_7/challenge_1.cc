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

    if (it == registry.end()) {
        std::cout << "There is no root" << std::endl;
    } else {
        std::cout << "The root is " << it->first << std::endl;
    }

    return 0;
}