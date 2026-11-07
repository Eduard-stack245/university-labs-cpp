// File table laboratory: text files and binary FILE* records.
#include "lab_compat.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
using namespace std;

struct dress
{
    string type;
    string color;
    double size = 0;
    double price = 0;
};


// Read the text records without creating or modifying the source file.
vector<dress> loadData(const string& filePath) {
    vector<dress> table;
    ifstream file(filePath);
    if (!file) {
        cout << "Can't open file: " << filePath << endl;
        return table;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string type, color, sizeText, priceText;
        if (!getline(ss, type, ';') || !getline(ss, color, ';') ||
            !getline(ss, sizeText, ';') || !getline(ss, priceText, ';')) {
            cerr << "Invalid record in " << filePath << '\n';
            continue;
        }
        try {
            const double size = stod(sizeText);
            const double price = stod(priceText);
            table.push_back({type, color, size, price});
        } catch (const std::exception&) {
            cerr << "Invalid numeric value in " << filePath << '\n';
        }
    }
    return table;
}

void add(ostream& file, const dress& item) {
    file << item.type << ';' << item.color << ';'
         << item.size << ';' << item.price << '\n';
}

void log(ostream& file, const string& line) {
    file << line << '\n';
}

void save(const string& filePath, const vector<dress>& table) {
    ofstream file(filePath, ios::trunc);
    if (!file) {
        cout << "Can't open file: " << filePath << endl;
        return;
    }
    for (const auto& item : table) add(file, item);
}

// FILE* binary exercises must serialize string characters, not the internal
// pointers and allocation state of std::string objects.
bool writeBinaryString(FILE* file, const string& value) {
    if (value.size() > 1024 * 1024) return false;
    const uint32_t size = static_cast<uint32_t>(value.size());
    return fwrite(&size, sizeof(size), 1, file) == 1 &&
           fwrite(value.data(), 1, size, file) == size;
}

bool readBinaryString(FILE* file, string& value) {
    uint32_t size = 0;
    if (fread(&size, sizeof(size), 1, file) != 1 || size > 1024 * 1024)
        return false;
    value.resize(size);
    return fread(value.data(), 1, size, file) == size;
}

bool addF(FILE* file, const dress& item) {
    return file && writeBinaryString(file, item.type) &&
           writeBinaryString(file, item.color) &&
           fwrite(&item.size, sizeof(item.size), 1, file) == 1 &&
           fwrite(&item.price, sizeof(item.price), 1, file) == 1;
}

// Read one binary record: the same layout that addF writes.
bool readF(FILE* file, dress& item) {
    return file && readBinaryString(file, item.type) &&
           readBinaryString(file, item.color) &&
           fread(&item.size, sizeof(item.size), 1, file) == 1 &&
           fread(&item.price, sizeof(item.price), 1, file) == 1;
}

void saveF(const string& filePath, const vector<dress>& table) {
    FILE* file = fopen(filePath.c_str(), "wb");
    if (!file) {
        cout << "Can't open file: " << filePath << endl;
        return;
    }
    for (const auto& item : table) {
        if (!addF(file, item)) {
            cerr << "Can't write binary file: " << filePath << '\n';
            break;
        }
    }
    fclose(file);
}

void showBinaryFile(const string& filePath) {
    FILE* file = fopen(filePath.c_str(), "rb");
    if (!file) {
        cout << "Can't open file: " << filePath << endl;
        return;
    }
    cout << "Тип\t\tЦвет\t\tРазмер\t\tЦена\n";
    dress item;
    while (readF(file, item)) {
        cout << item.type << "\t\t" << item.color << "\t\t"
             << item.size << "\t\t" << item.price << '\n';
    }
    fclose(file);
}

dress write() {
    dress myDress = { "","",0.0,0.0 };
    cout << "Ведите данные про одежду:" << endl;
    cout << "Ведите тип одежды:" << endl;
    cin >> myDress.type;
    cout << "Ведите цвет одежды:" << endl;
    cin >> myDress.color;
    cout << "Ведите размер одежды:" << endl;
    cin >> myDress.size;
    cout << "Ведите цену одежды:" << endl;
    cin >> myDress.price;
    return myDress;
}

void writeKeyboard(string path) {
    int push = 0;
    string fileName = "newData.txt";
    vector<dress> vector;
    while (push == 0)
    {
        const dress item = write();
        if (!cin) return;
        vector.push_back(item);
        cout << "Продолжить?" << endl;
        cin >> push;
    }
    cout << "Ведите имя файла:" << endl;
    if (!(cin >> fileName)) return;
    save(path + fileName, vector);
    saveF(path + fileName + "F", vector);
    cout << "Збережено у файлi:" << path + fileName << endl;
}

void writeAddFile(const string& path) {
    int push = 0;
    string fileName;
    cout << "Ведите имя файла:" << endl;
    if (!(cin >> fileName)) return;
    ofstream textFile(path + fileName, ios::app);
    FILE* binaryFile = fopen((path + fileName + "F").c_str(), "ab");
    if (!textFile || !binaryFile) {
        cout << "Can't open file: " << path + fileName << endl;
        if (binaryFile) fclose(binaryFile);
        return;
    }
    while (push == 0 && cin) {
        const dress item = write();
        if (!cin) break;
        add(textFile, item);
        if (!addF(binaryFile, item)) {
            cerr << "Can't append binary record\n";
            break;
        }
        cout << "Збережено у файлi:" << path + fileName << endl;
        cout << "Продолжить?" << endl;
        if (!(cin >> push)) break;
    }
    fclose(binaryFile);
}

void showFile(string path) {
    string fileName = "newData.txt";
    cout << "Ведите имя файла:" << endl;
    if (!(cin >> fileName)) return;
    vector<dress> vector = loadData(path + fileName);
    cout << "Тип\t\t" << "Цвет\t\t" << "Размер\t\t" << "Цена\t\t" << endl;
    for (size_t i = 0; i < vector.size(); i++) {
        cout << vector[i].type << "\t\t" << vector[i].color << "\t\t" << "\t\t" << vector[i].size << "\t\t" << vector[i].price << "\t\t" << endl;
    }
}

void operaziya(string path) {
    int out = 0, exit = 0;
    string fileName = "newData.txt", search = "";
    cout << "Ведите имя файла:" << endl;
    if (!(cin >> fileName)) return;
    vector<dress> vector = loadData(path + fileName);
    ofstream file(path + "log.txt", ios::trunc);
    while (exit == 0) {
        cout << "search user?" << endl;
        if (!(cin >> search)) break;
        if (search.size() > 0)
            for (size_t i = 0; i < vector.size(); i++) {
                if (vector[i].type == search || vector[i].color == search) {
                    string line = "Тип\t\tЦвет\t\tРазмер\t\tЦена\t\t\n";
                    cout << line;
                    log(file, line);
                    line = vector[i].type + "\t\t" + vector[i].color + "\t\t" + "\t\t" + to_string(vector[i].size) + "\t\t" + to_string(vector[i].price) + "\t\t\n";
                    cout << line;
                    log(file, line);
                }
            }
        cout << "Выводить таблицу?" << endl;
        if (!(cin >> out)) break;
        if (out == 0) {
            string line = "Вся таблица:\n";
            cout << line;
            log(file, line);
            line = "№\t\tТип\t\tЦвет\t\tРазмер\t\tЦена\t\t\n";
            cout << line;
            log(file, line);
            for (size_t i = 0; i < vector.size(); i++) {
                line = to_string(i + 1) + "\t\t" + vector[i].type + "\t\t" + vector[i].color + "\t\t\t\t" + to_string(vector[i].size) + "\t\t" + to_string(vector[i].price) + "\t\t\n";
                cout << line;
                log(file, line);
            }
        }
        cout << "Выводить info?" << endl;
        if (!(cin >> exit)) break;
    }
}

int main()
{
    lab::init_console();
    lab::clear_screen();
    int in = 0;
    string path = "";
    for (int exit = 0; exit == 0;) {
        /* print the menu */
        cout << ("1 - Вводить данные из клавиатуры\n");
        cout << ("2 - Дописать данные в файл\n");
        cout << ("3 - Показать данные из файла на экран\n");
        cout << ("4 - Результат задания №2\n");
        cout << ("5 - Показать бинарную версию файла\n");
        cout << ("0 - ВИХІД\n");
        cout << ("Введiть > ");
        if (!(cin >> in)) break; /* menu choice */
        switch (in) {
        case 0: exit = 1; break; /* exit */
        case 1: writeKeyboard(path); break;
        case 2: writeAddFile(path); break;
        case 3: showFile(path); break;
        case 4: operaziya(path); break;
        case 5: {
            string fileName;
            cout << "Ведите имя файла:" << endl;
            if (cin >> fileName) showBinaryFile(path + fileName + "F");
            break;
        }
        default: cout << ("Неправильна операція^");
            break;
        } /* switch */
    } /* for */
    lab::pause();
    return 0;
}
