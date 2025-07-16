#ifndef STRING_UTIL_HPP
#define STRING_UTIL_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::vector<std::string>> parseCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string value;

        while (std::getline(ss, value, ',')) {
            row.push_back(value);
        }
        data.push_back(row);
    }
    file.close();
    return data;
}


template<typename T, typename String>
T toNumeric(const String & str) {
    T val;
    std::stringstream ss(str);
    ss >> val;
    return val;
}


#endif
