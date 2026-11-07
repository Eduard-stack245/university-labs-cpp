#include <cstdio>
#include <ctime>
#include "lab_compat.h"

const char* getSeason(const tm& date) {
    if (date.tm_mon >= 2 && date.tm_mon <= 4) return "Весна";
    if (date.tm_mon >= 5 && date.tm_mon <= 7) return "Лето";
    if (date.tm_mon >= 8 && date.tm_mon <= 10) return "Осень";
    return "Зима";
}

int main() {
    lab::init_console();
    const char* days[] = {
        "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"
    };
    const char* months[] = {
        "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль",
        "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"
    };

    char input[32] = {};
    int day = 0, month = 0, year = 0;
    char extra = '\0';
    std::printf("Введите дату в формате (dd.mm.yyyy), чтобы узнать сезон, название дня и месяца:\n");
    if (std::scanf("%31s", input) != 1 ||
        std::sscanf(input, "%d.%d.%d%c", &day, &month, &year, &extra) != 3 ||
        day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 9999) {
        std::fprintf(stderr, "Неверный формат даты.\n");
        return 1;
    }
    tm date = {};
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;
    date.tm_hour = 12;
    date.tm_isdst = -1;
    if (std::mktime(&date) == static_cast<time_t>(-1) ||
        date.tm_year != year - 1900 || date.tm_mon != month - 1 || date.tm_mday != day) {
        std::fprintf(stderr, "Некорректная календарная дата.\n");
        return 1;
    }
    std::printf("%s, %s - %s\n", days[(date.tm_wday + 6) % 7], months[date.tm_mon], getSeason(date));
    return 0;
}
