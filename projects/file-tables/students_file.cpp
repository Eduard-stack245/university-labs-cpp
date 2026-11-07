#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "lab_compat.h"

struct Student {
    std::string name;
    std::string gender;
    int birthYear = 0;
    float weight = 0;
};

namespace {
std::vector<Student> loadStudents(const std::string& filename)
{
    std::ifstream input(filename);
    std::vector<Student> students;
    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) continue;
        std::istringstream record(line);
        Student student;
        std::string year, weight;
        if (!std::getline(record, student.name, ';') ||
            !std::getline(record, student.gender, ';') ||
            !std::getline(record, year, ';') ||
            !std::getline(record, weight)) {
            std::cerr << "Skipping invalid record: " << line << '\n';
            continue;
        }
        try {
            std::size_t yearEnd = 0, weightEnd = 0;
            student.birthYear = std::stoi(year, &yearEnd);
            student.weight = std::stof(weight, &weightEnd);
            if (yearEnd != year.size() || weightEnd != weight.size()) continue;
            students.push_back(student);
        } catch (const std::exception&) {
            std::cerr << "Skipping invalid record: " << line << '\n';
        }
    }
    return students;
}

bool saveStudents(const std::string& filename, const std::vector<Student>& students)
{
    std::ofstream output(filename, std::ios::trunc);
    if (!output) return false;
    for (const Student& student : students)
        output << student.name << ';' << student.gender << ';'
               << student.birthYear << ';' << student.weight << '\n';
    return static_cast<bool>(output);
}

void printStudent(const Student& student)
{
    std::cout << student.name << "\t" << student.gender << "\t"
              << student.birthYear << "\t" << student.weight << '\n';
}

void printAll(const std::vector<Student>& students)
{
    std::cout << "Ім'я\tСтать\tРік народження\tВага\n";
    for (const Student& student : students) printStudent(student);
}

void printOne(const std::vector<Student>& students)
{
    std::size_t index = 0;
    std::cout << "Введiть порядковий номер студента > ";
    if (!(std::cin >> index)) return;
    if (index < 1 || index > students.size()) {
        std::cout << "Невірний номер студента\n";
        return;
    }
    printStudent(students[index - 1]);
}

bool removeStudent(std::vector<Student>& students)
{
    std::size_t index = 0;
    std::cout << "Введiть порядковий номер студента > ";
    if (!(std::cin >> index)) return false;
    if (index < 1 || index > students.size()) {
        std::cout << "Невірний номер студента\n";
        return false;
    }
    students.erase(students.begin() + static_cast<std::ptrdiff_t>(index - 1));
    return true;
}
} // namespace

int main()
{
    lab::init_console();
    const std::string filename = "lb2_9_1.txt";
    std::vector<Student> students = loadStudents(filename);
    bool modified = false;
    for (;;) {
        std::cout << "1 - Додати eлeмeнт\n2 - Видалити eлeмeнт\n"
                  << "3 - Показать елемент за номeром\n4 - Показати всe\n"
                  << "0 - ВИХІД\nВведiть > ";
        int choice = -1;
        if (!(std::cin >> choice)) break;
        if (choice == 0) break;
        switch (choice) {
        case 1: {
            Student student;
            std::cout << "Введите имя, пол, год рождения, вес:\n";
            if (!(std::cin >> student.name >> student.gender >> student.birthYear >> student.weight))
                return 1;
            students.push_back(student);
            modified = true;
            break;
        }
        case 2: modified = removeStudent(students) || modified; break;
        case 3: printOne(students); break;
        case 4: printAll(students); break;
        default: std::cout << "Неправильна операція\n";
        }
        if (!std::cin) return 1;
    }
    if (modified && !saveStudents(filename, students)) {
        std::cerr << "Can't write file: " << filename << '\n';
        return 1;
    }
    lab::pause();
    return 0;
}
