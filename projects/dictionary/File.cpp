#include "File.h"

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include "lab_utf8.hpp"

std::vector<Row> search(const std::string& word)
{
    std::ifstream file("dict.txt");
    if (!file) {
        std::cerr << "Can't open file: dict.txt\n";
        return {};
    }
    std::vector<Row> found;
    std::string line;
    while (std::getline(file, line)) {
        const auto separator = line.find('|');
        if (separator == std::string::npos) continue;
        Row entry{line.substr(0, separator), line.substr(separator + 1)};
        if (lab::text::containsIgnoreCase(entry.word, word))
            found.push_back(std::move(entry));
    }
    return found;
}
