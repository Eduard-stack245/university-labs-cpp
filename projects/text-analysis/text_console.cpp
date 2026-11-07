#include <iostream>
#include <string>

#include "lab_compat.h"
#include "TextAnalysisLab.hpp"

int main()
{
    lab::init_console();
    std::cout << "Введите текст:\n";
    std::string text;
    if (!std::getline(std::cin, text)) return 1;
    std::cout << '\n' << text << '\n';
    text_lab::report(text, std::cout);
    lab::pause();
    return 0;
}
