#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <string>

int get_value_at(const std::map<std::pair<int, int>, int> &value_map,
                 const std::pair<int, int> &pos) {
    const auto found = value_map.find(pos);

    if (found != value_map.end()) {
        return found->second;
    }

    return 0;
}

int get_sum(const std::map<std::pair<int, int>, int> &value_map,
            const std::pair<int, int> &pos) {
    int sum = 0;
    // North
    sum += get_value_at(value_map, {pos.first, pos.second + 1});

    // North-East
    sum += get_value_at(value_map, {pos.first + 1, pos.second + 1});

    // East
    sum += get_value_at(value_map, {pos.first + 1, pos.second});

    // South-East
    sum += get_value_at(value_map, {pos.first + 1, pos.second - 1});

    // South
    sum += get_value_at(value_map, {pos.first, pos.second - 1});

    // South-West
    sum += get_value_at(value_map, {pos.first - 1, pos.second - 1});

    // West
    sum += get_value_at(value_map, {pos.first - 1, pos.second});

    // North-West
    sum += get_value_at(value_map, {pos.first - 1, pos.second + 1});

    return sum;
}

int main(int /* argc */, char * /* argv */ []) {
    int width = 1, height = 1, x = 0, y = 0, target = 1;
    std::string target_string;
    std::cout << "Please enter threshold value: ";
    std::cin >> target_string;

    try {
        target = std::stoi(target_string);
    } catch (const std::invalid_argument &ex) {
        std::cerr << "Could not convert input: " << std::quoted(target_string)
                  << " (" << ex.what() << ")" << std::endl;
        return 1;
    } catch (const std::out_of_range &ex) {
        std::cerr << "Input was out of range of an int ("
                  << std::numeric_limits<int>::min() << " - "
                  << std::numeric_limits<int>::max()
                  << "): " << std::quoted(target_string) << " (" << ex.what()
                  << ")" << std::endl;
        return 1;
    }

    std::map<std::pair<int, int>, int> value_map{{{0, 0}, 1}};

    int value = 1;
    while (value <= target) {
        // Go right
        int togo = width++;
        while (togo-- > 0) {
            ++x;

            std::pair<int, int> coord = {x, y};

            value = get_sum(value_map, coord);

            // Add to map
            value_map.insert({{x, y}, value});

            if (value > target) {
                std::cout << "Hit target of " << value << " at " << x << ","
                          << y << std::endl;
                return 0;
            }
        }

        // Go up
        togo = height++;
        while (togo-- > 0) {
            ++y;
            std::pair<int, int> coord = {x, y};

            value = get_sum(value_map, coord);

            // Add to map
            value_map.insert({{x, y}, value});

            if (value > target) {
                std::cout << "Hit target of " << value << " at " << x << ","
                          << y << std::endl;
                return 0;
            }
        }

        // Go left
        togo = width++;
        while (togo-- > 0) {
            --x;
            std::pair<int, int> coord = {x, y};

            value = get_sum(value_map, coord);

            // Add to map
            value_map.insert({{x, y}, value});

            if (value > target) {
                std::cout << "Hit target of " << value << " at " << x << ","
                          << y << std::endl;
                return 0;
            }
        }

        // Go down
        togo = height++;
        while (togo-- > 0) {
            --y;
            std::pair<int, int> coord = {x, y};

            value = get_sum(value_map, coord);

            // Add to map
            value_map.insert({{x, y}, value});

            if (value > target) {
                std::cout << "Hit target of " << value << " at " << x << ","
                          << y << std::endl;
                return 0;
            }
        }
    }

    std::cerr << "You should not get here." << std::endl;

    return 1;
}