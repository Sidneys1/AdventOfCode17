#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class SpreadSheetRow {
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
      while (std::getline(lineStream, cell, '\t')) {
          m_data.push_back(cell);
      }
  }

  friend std::istream &operator>>(std::istream &str, SpreadSheetRow &data) {
      data.read(str);
      return str;
  }

private:
  std::vector<std::string> m_data;
};