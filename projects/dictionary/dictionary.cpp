#include <iostream>
#include "lab_compat.h"
#include "View.h"

int main()
{
    lab::init_console();
    for (;;) {
        std::cout << "1 - Пошук\n0 - ВИХІД\nВведiть > ";
        int choice = 0;
        if (!(std::cin >> choice)) break;
        if (choice == 0) break;
        if (choice == 1) searchWord();
        else std::cout << "Неправильна операція\n";
        if (!std::cin) break;
    }
    lab::pause();
    return 0;
}
