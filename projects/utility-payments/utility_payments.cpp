#include <array>
#include <fstream>
#include <iostream>
#include <string>

#include "lab_compat.h"

namespace {
struct Utility {
    std::string name;
    double price;
};

std::array<Utility, 6> loadRates(const std::string& filename)
{
    std::array<Utility, 6> rates{{
        {"Кварплата", 0.20}, {"Електроенергія", 0.09},
        {"Газ", 1.10}, {"Гаряче водопостачання", 1.79},
        {"Холодне водопостачання", 0.43}, {"Опалення", 0.42}
    }};
    const auto defaults = rates;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Файл " << filename << " не знайдено; використано типові тарифи.\n";
        return rates;
    }
    // The lab's configuration contains a label and a price on each line.
    // Keep the displayed Ukrainian labels, regardless of the label in the file.
    for (Utility& utility : rates) {
        std::string label;
        double price = 0;
        if (!(file >> label >> price) || price < 0) {
            std::cerr << "Невірні тарифи; використано типові тарифи.\n";
            return defaults;
        }
        utility.price = price;
    }
    return rates;
}
} // namespace

int main()
{
    lab::init_console();
    const auto rates = loadRates("config.txt");
    std::cout << "____Розрахунок комунальних платежів____\n";
    for (;;) {
        std::cout << "Виберіть форму розрахунку (1-6; 0 - вихід):\n";
        for (std::size_t i = 0; i < rates.size(); ++i)
            std::cout << i + 1 << ". " << rates[i].name << '\n';
        int choice = 0;
        if (!(std::cin >> choice)) break;
        if (choice == 0) break;
        if (choice < 1 || choice > static_cast<int>(rates.size())) {
            std::cout << "Невірний пункт меню\n";
            continue;
        }
        double amount = 0;
        if (choice == 1) {
            double area = 0;
            std::cout << "Площа: ";
            if (!(std::cin >> area) || area < 0) return 1;
            std::cout << "Кількість: ";
            if (!(std::cin >> amount) || amount < 0) return 1;
            amount *= area;
        } else {
            std::cout << "Кількість: ";
            if (!(std::cin >> amount) || amount < 0) return 1;
        }
        std::cout << rates[static_cast<std::size_t>(choice - 1)].name << ": "
                  << amount * rates[static_cast<std::size_t>(choice - 1)].price << '\n';
        std::cout << "Продовжити '1' - так '0' - ні\n";
        int again = 0;
        if (!(std::cin >> again) || again == 0) break;
    }
    return 0;
}
