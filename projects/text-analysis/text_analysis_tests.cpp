#include <iostream>
#include <sstream>
#include <string>

#include "TextAnalysisLab.hpp"

int main()
{
    int errors = 0;
    const auto check = [&](bool condition, const char* message) {
        if (!condition) {
            std::cerr << "FAIL: " << message << '\n';
            ++errors;
        }
    };

    check(text_lab::characters("Привіт").size() == 6, "UTF-8 character count");
    check(text_lab::countOddLengthWords("кіт дім") == 2, "odd Cyrillic word lengths");
    check(text_lab::countOddLengthWords("") == 0, "empty input");
    const auto frequency = text_lab::characterFrequency("ааб");
    check(frequency.at("а") == 2 && frequency.at("б") == 1, "Cyrillic frequency");
    const auto parts = text_lab::parenthesizedText("one (two three) four (п'ять)");
    check(parts.size() == 2 && parts[0] == "two three" && parts[1] == "п'ять",
          "parentheses spanning multiple words");
    std::istringstream lines("first\nsecond\nthird\n");
    check(text_lab::readAll(lines) == "first\nsecond\nthird\n", "all lines are read");
    std::ostringstream output;
    text_lab::report("", output);
    check(output.str().find("Количество слов") != std::string::npos, "empty report is safe");
    return errors == 0 ? 0 : 1;
}
