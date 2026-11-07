#include <iostream>
#include <string>
#include <vector>

#include "lab_compat.h"

struct Clothing {
    std::string type;
    std::string color;
    double size = 0;
    double price = 0;
};

namespace {
void printClothing(const Clothing& item)
{
    std::cout << item.type << "\t" << item.color << "\t"
              << item.size << "\t" << item.price << '\n';
}

bool readClothing(Clothing& item)
{
    std::cout << "Ведите тип одежды:\n";
    if (!(std::cin >> item.type)) return false;
    std::cout << "Ведите цвет одежды:\n";
    if (!(std::cin >> item.color)) return false;
    std::cout << "Ведите размер одежды:\n";
    if (!(std::cin >> item.size)) return false;
    std::cout << "Ведите цену одежды:\n";
    return static_cast<bool>(std::cin >> item.price);
}

void printAll(const std::vector<Clothing>& clothes)
{
    std::cout << "Вся таблица:\n№\tТип\tЦвет\tРазмер\tЦена\n";
    for (std::size_t i = 0; i < clothes.size(); ++i) {
        std::cout << i + 1 << "\t";
        printClothing(clothes[i]);
    }
}
} // namespace

int main()
{
    lab::init_console();
    std::vector<Clothing> clothes;
    int keepAdding = 0;
    while (keepAdding == 0) {
        Clothing item;
        std::cout << "Ведите данные про одежду:\n";
        if (!readClothing(item)) return 1;
        clothes.push_back(item);
        std::cout << "Продолжить?\n";
        if (!(std::cin >> keepAdding)) return 1;
    }

    int leave = 0;
    while (leave == 0) {
        std::string query;
        std::cout << "search user?\n";
        if (!(std::cin >> query)) return 1;
        for (const Clothing& item : clothes) {
            if (item.type == query || item.color == query) {
                std::cout << "Тип\tЦвет\tРазмер\tЦена\n";
                printClothing(item);
            }
        }
        std::cout << "Выводить таблицу?\n";
        int showTable = 0;
        if (!(std::cin >> showTable)) return 1;
        if (showTable == 0) printAll(clothes);
        std::cout << "Выводить info?\n";
        if (!(std::cin >> leave)) return 1;
    }
    lab::pause();
    return 0;
}
