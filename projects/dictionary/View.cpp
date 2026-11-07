#include "View.h"

#include <iostream>
#include <string>

namespace {
void printLine() { std::cout << '\n' << std::string(60, '-') << '\n'; }
}

void showAll(const std::vector<Row>& rows)
{
    printLine();
    for (const Row& row : rows)
        std::cout << row.word << " --> " << row.description << '\n';
    if (rows.empty()) std::cout << "Слово не знайдено\n";
    printLine();
}

void searchWord()
{
    std::string word;
    std::cout << "Введiть слово:\n";
    if (std::cin >> word) showAll(search(word));
}
