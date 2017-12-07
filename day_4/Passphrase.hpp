#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

class Passphrase {
  public:
    std::string const &operator[](std::size_t index) const {
        return m_data[index];
    }
    std::size_t size() const { return m_data.size(); }

    std::vector<std::string>::const_iterator begin() const {
        return m_data.begin();
    }

    std::vector<std::string>::const_iterator end() const {
        return m_data.end();
    }

    void read(std::istream &str) {
        std::string line, cell;
        std::getline(str, line);
        std::stringstream lineStream(line);
        while (std::getline(lineStream, cell, ' ')) {
            m_data.push_back(cell);
        }
    }

    bool valid() const {
        std::unordered_set<std::string> set(m_data.begin(), m_data.end());
        return set.size() == m_data.size();
    }

    /**
     * Checks that there are no words in this passphrase that are anagrams of
     * each other.
     *
     * There is a better way to do this, but it didn't compile...
     * Basically you create a std::unordered_set<std::unordered_multiset<char>>
     * and check that its `.size() == m_data.size()`
     */
    bool valid_no_anagrams() const {
        std::vector<std::unordered_multiset<char>> list;

        for (const std::string &str : m_data) {
            list.emplace_back(
                std::unordered_multiset<char>(str.begin(), str.end()));
        }

        for (size_t i = 0; i < list.size(); i++) {
            for (size_t j = 0; j < list.size(); j++) {
                if (i == j) {
                    continue;
                }
                if (list[i] == list[j]) {
                    return false;
                }
            }
        }

        return true;
    }

    friend std::istream &operator>>(std::istream &str, Passphrase &data) {
        data.read(str);
        return str;
    }

  private:
    std::vector<std::string> m_data;
};