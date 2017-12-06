#include <climits>
#include <iostream>
#include <string>
#include <vector>

#include "SpreadSheet.h"

int main(int /* argc */, char * /* argv */ []) {
    std::vector<SpreadSheetRow> rows;
    do {
        SpreadSheetRow row;
        std::cin >> row;
        if (row.size() == 0) {
            break;
        }
        rows.push_back(row);
    } while (true);

    std::cout << "There are " << rows.size() << " rows." << std::endl;

    int i = 0, checksum = 0;
    for (auto &row : rows) {
        int min = INT_MAX;
        int max = INT_MIN;
        for (auto &entry : row) {
            int val = std::stoi(entry);
            if (val < min) {
                min = val;
            }
            if (val > max) {
                max = val;
            }
        }
        int diff = max - min;
        std::cout << "The Min/Max/Diff is " << min << "/" << max << "/" << diff
                  << std::endl;
        checksum += diff;
        i++;
    }

    std::cout << "The checksum is " << checksum << std::endl;

    int multiples_checksum = 0;
    i = 0;
    for (auto &row : rows) {
        bool broken = false;
        for (auto &outer_str : row) {
            int outer = std::stoi(outer_str);
            std::cout << outer;
            for (auto &inner_str : row) {
                int inner = std::stoi(inner_str);
                std::cout << " " << inner << std::endl;
                if (outer >= inner) {
                    continue;
                }
                if ((inner % outer) == 0) {
                    std::cout << "The multiples of row " << i << " are "
                              << inner << " into " << outer << ", "
                              << inner / outer << " times." << std::endl;
                    multiples_checksum += inner / outer;
                    broken = true;
                    break;
                }
            }
            if (broken) {
                break;
            }
            i++;
        }
    }

    std::cout << "The checksum of multiples is " << multiples_checksum
              << std::endl;

    return 0;
}
