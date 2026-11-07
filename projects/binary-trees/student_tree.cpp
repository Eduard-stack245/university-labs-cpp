// Lb2_10_1.cpp : This file contains the "main" function.
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include "lab_compat.h"

using namespace std;

struct Node {
    int number = 0;
    int level = 0;
    string name = "";
    int year = 0, p1 = 0, p2 = 0, p3 = 0, p4 = 0;
    Node *left = NULL, *right = NULL;
};

Node* tree = NULL;

void createFile(string filePath);

void add(Node**node, Node** value) {
    if ((*node) == NULL) {
        (*node) = (*value);
        return;
    }
    (*value)->level = (*node)->level + 1;
    if ((*node)->number > (*value)->number) {
        add(&(*node)->left,value);
    }else {
        add(&(*node)->right, value);
    }
}

void update(Node** node, int level) {
    if ((*node) != NULL) {
        (*node)->level = level;
        update(&(*node)->left, level + 1);
        update(&(*node)->right, level + 1);
    }
}

double middle(Node* node) {
    return ((double)node->p1 + (double)node->p2 + (double)node->p3 + (double)node->p4) / 4.0;
}

Node* search(Node** node, string name, int year, int number) {
    Node* result = NULL;
    if ((*node) != NULL) {
        if (name.size() > 0 && (*node)->name == name) {
            return (*node);
        }
        if (year > 0 && (*node)->year == year) {
            return (*node);
        }
        if (number > -1 && (*node)->number == number) {
            return (*node);
        }
        result = search(&(*node)->left, name,year,number);
        if(result==NULL) result = search(&(*node)->right, name, year, number);
    }
    return result;
}

Node* remove(Node **node) {
    Node* result = NULL;
    if ((*node) != NULL) {
        result = (*node);
        (*node) = NULL;
        if (result->right != NULL)add(node, &result->right);
        if (result->left != NULL)add(node, &result->left);
    }
    return result;
}

void get(Node* node, string title, bool next, fstream *logfile) {
    if (node != NULL) {
        cout << title+to_string(node->level) << endl;
        cout << node->number << "\t" << node->name << "\t\t" << node->p1 << "\t\t" << node->p2 << "\t\t" << node->p3 << "\t\t" << node->p4 << endl;
        (*logfile) << title+to_string(node->level) << endl;
        (*logfile) << node->number << "\t" << node->name << "\t\t" << node->p1 << "\t\t" << node->p2 << "\t\t" << node->p3 << "\t\t" << node->p4 << endl;
        if (next) {
            get(node->left, "ЛЕВЫЙ: ", true, logfile);
            get(node->right, "ПРАВЫЙ: ", true, logfile);
        }
    }
}

void get(fstream* logfile) {
    if (tree != NULL) {
        cout << "№\t" << "Имя\t" << "1-ый екзамен\t" << "2-ой экзамен\t" << "3-ий экзамен\t" << "4-ый экзамен" << endl;
        (*logfile) << "№\t" << "Имя\t" << "1-ый екзамен\t" << "2-ой экзамен\t" << "3-ий экзамен\t" << "4-ый экзамен" << endl;
        get(tree, "ГЛАВНЫЙ узел: ",true,logfile);
    }
}

void searchMiddle(Node** node, double value, fstream* logfile) {
    if ((*node) != NULL) {
        searchMiddle(&(*node)->left, value, logfile);
        searchMiddle(&(*node)->right, value, logfile);
        if (value > -1 && middle((*node)) < value) {
            cout << "Среднее студента: " << middle((*node)) << endl;
            (*logfile) << "Среднее студента: " << middle((*node)) << endl;
            get((*node), "Уровень дерева - ", false, logfile);
            Node* detached = remove(node);
            delete detached;
        }
    }
}

Node* random(int number) {
    Node* node = new Node;
    node->number = number;
    node->name = "Студент "+ to_string(number);
    node->year = 2000 + (rand() % 11);
    node->p1 = 2 + (rand() % 4);
    node->p2 = 2 + (rand() % 4);
    node->p3 = 2 + (rand() % 4);
    node->p4 = 2 + (rand() % 4);
    node->left = NULL;
    node->right = NULL;
    return node;
}

void deleteTree(Node* node) {
    if (node == NULL) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main()
{
    lab::init_console();
    lab::clear_screen();
    int n = 10, num = 0;
    double midleGroup = 0;
    fstream logfile;
    string filePath = "Out_Sp.txt";
    createFile(filePath);
    logfile.open(filePath, std::ios::in | std::ios::out | std::ios::app);
    if (logfile.is_open()) {   //checking whether the file is open
        cout << "Ведите количество студентов" << endl;
        if (!(cin >> n) || n > 10000) return 1;
        if (n < 10) n = 10;
        for (int i = 0; i < n; ) {
            cout << "Введите номер узла" << endl;
            if (!(cin >> num)) {
                deleteTree(tree);
                return 1;
            }
            if (num > -1 && search(&tree,"",0,num)==NULL) {
                Node* node = random(num);
                midleGroup += middle(node);
                add(&tree, &node);
                i++;
            }
        }
        midleGroup /= (double)n;
        cout << "Средний бал группы: " << midleGroup << endl;
        logfile << "Средний бал группы: " << midleGroup << endl;
        cout << endl << "Результат поиска студентов ниже среднего бала группы: " << endl << endl;
        logfile << endl << "Результат поиска студентов ниже среднего бала группы: " << endl << endl;
        cout << "№\t" << "Имя\t" << "1-ый екзамен\t" << "2-ой экзамен\t" << "3-ий экзамен\t" << "4-ый экзамен" << endl;
        logfile << "№\t" << "Имя\t" << "1-ый екзамен\t" << "2-ой экзамен\t" << "3-ий экзамен\t" << "4-ый экзамен" << endl;
        searchMiddle(&tree, midleGroup, &logfile);
        update(&tree, 0);
        cout << endl << endl;
        logfile << endl << endl;
        get(&logfile);
        logfile.close();
    }
    else {
        cout << "Can't open file: " << filePath << endl;
    }
    deleteTree(tree);
    tree = NULL;
    lab::pause();
    return 0;
}

void createFile(string filePath) {
    fstream logfile;
    logfile.open(filePath, std::ios::out | ios_base::trunc);
    logfile << "";   //utf8
    logfile.close();
}