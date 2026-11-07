#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "lab_compat.h"
#include "TextAnalysisLab.hpp"

int main()
{
    lab::init_console();
    std::ifstream input("words.txt");
    if (!input) {
        std::cerr << "Could not open words.txt\n";
        return 1;
    }
    const std::string text = text_lab::readAll(input);
    std::ostringstream report;
    report << "--[ read file ]--\n" << text << "\n---------\n";
    text_lab::report(text, report);
    std::cout << report.str();
    std::ofstream log("log.txt", std::ios::trunc);
    if (!log) {
        std::cerr << "Could not create log.txt\n";
        return 1;
    }
    log << report.str();
    lab::pause();
    return log ? 0 : 1;
}
