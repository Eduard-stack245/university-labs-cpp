#include <iostream>
#include <string>
#include <vector>

#include "lab_compat.h"

struct Student {
    std::string lastName;
    std::string firstName;
    std::string middleName;
    double mathGrade = 0;
    double physicsGrade = 0;
};

namespace {
void printStudent(const Student& student)
{
    std::cout << student.lastName << "\t" << student.firstName << "\t"
              << student.middleName << "\t" << student.mathGrade << "\t"
              << student.physicsGrade << '\n';
}

bool readStudent(Student& student)
{
    std::cout << "Введите фамилию студента:\n";
    if (!(std::cin >> student.lastName)) return false;
    std::cout << "Введите имя студента:\n";
    if (!(std::cin >> student.firstName)) return false;
    std::cout << "Введите отчество студента:\n";
    if (!(std::cin >> student.middleName)) return false;
    std::cout << "Введите оценку студента по Математики:\n";
    if (!(std::cin >> student.mathGrade)) return false;
    std::cout << "Введите оценку студента по Физике:\n";
    return static_cast<bool>(std::cin >> student.physicsGrade);
}

void printAll(const std::vector<Student>& students)
{
    std::cout << "Вся таблица:\n№\tФамилия\tИмя\tОтчество\tМатематика\tФизика\n";
    for (std::size_t i = 0; i < students.size(); ++i) {
        std::cout << i + 1 << "\t";
        printStudent(students[i]);
    }
}
} // namespace

int main()
{
    lab::init_console();
    std::vector<Student> students;
    int keepAdding = 0;
    while (keepAdding == 0) {
        Student student;
        std::cout << "Введите данные про студента:\n";
        if (!readStudent(student)) return 1;
        students.push_back(student);
        std::cout << "Продолжить?\n";
        if (!(std::cin >> keepAdding)) return 1;
    }

    int leave = 0;
    while (leave == 0) {
        std::string query;
        std::cout << "search user?\n";
        if (!(std::cin >> query)) return 1;
        for (const Student& student : students) {
            if (student.lastName == query || student.firstName == query ||
                student.middleName == query) {
                std::cout << "Фамилия\tИмя\tОтчество\tМатематика\tФизика\n";
                printStudent(student);
            }
        }
        std::cout << "Выводить таблицу?\n";
        int showTable = 0;
        if (!(std::cin >> showTable)) return 1;
        if (showTable == 0) printAll(students);
        std::cout << "Выводить info?\n";
        if (!(std::cin >> leave)) return 1;
    }
    lab::pause();
    return 0;
}
