#pragma once
#include <string>
#include <vector>

struct Row {
    std::string word;
    std::string description;
};

std::vector<Row> search(const std::string& word);
