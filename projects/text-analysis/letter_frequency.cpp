#include <iostream>
#include <string>
#include <vector>
#include "lab_compat.h"

int main() {
    std::string text;
    std::cout << "Введите предложение: ";
    std::getline(std::cin, text);
    if (text.empty()) {
        std::cout << "частота повторений: 0\n";
        return 0;
    }

    std::vector<int> frequency(text.size(), 0);
    for (std::size_t i = 0; i < text.size(); ++i) {
        for (std::size_t j = 0; j < text.size(); ++j)
            if (text[i] == text[j]) ++frequency[i];
    }
    // Count repeated characters once each, rather than counting the
    // same occurrences several times as the original implementation did.
    std::size_t repeated = 0;
    for (std::size_t i = 0; i < text.size(); ++i) {
        if (frequency[i] > 1) ++repeated;
        std::cout << text[i] << " - " << frequency[i] << '\n';
    }
    std::cout << "частота повторений: "
              << static_cast<double>(repeated) / text.size() << '\n';
    lab::pause();
    return 0;
}
