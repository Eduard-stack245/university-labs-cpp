// Console front-end for the generic Table: one program instead of the four lab programs
// (clothes table, students table, dictionary, student database).
//   records_cli [clothes | students | dictionary]        (default: clothes)
// The data lives in <name>.csv in the working directory; if the file is missing the table starts empty.
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "Index.hpp"
#include "Table.hpp"
#include "lab_compat.h"

using namespace rdb;

static Table makeTable(const std::string& dataset)
{
    if (dataset == "clothes")
        return Table({{"type", ColumnType::Text}, {"color", ColumnType::Text}, {"size", ColumnType::Integer}, {"price", ColumnType::Real}});
    if (dataset == "students")
        return Table({{"surname", ColumnType::Text}, {"name", ColumnType::Text}, {"patronymic", ColumnType::Text}, {"math", ColumnType::Integer}, {"physics", ColumnType::Integer}});
    if (dataset == "dictionary")
        return Table({{"word", ColumnType::Text}, {"description", ColumnType::Text}});
    throw std::invalid_argument("unknown dataset '" + dataset + "' (use clothes, students or dictionary)");
}

static bool ask(const std::string& prompt, std::string& answer)
{
    std::cout << prompt << std::flush;
    return static_cast<bool>(std::getline(std::cin, answer));
}

// Asks for a column number (1..n); returns false if the input ended or the number is wrong.
static bool askColumn(const Table& t, std::size_t& col)
{
    for (std::size_t i = 0; i < t.columns().size(); i++) std::cout << "  " << i + 1 << ") " << t.columns()[i].name << "\n";
    std::string a;
    if (!ask("Column: ", a)) return false;
    const int n = std::atoi(a.c_str());
    if (n < 1 || static_cast<std::size_t>(n) > t.columns().size()) { std::cout << "No such column.\n"; return false; }
    col = static_cast<std::size_t>(n - 1);
    return true;
}

int main(int argc, char** argv)
{
    lab::init_console();
    const std::string dataset = argc > 1 ? argv[1] : "clothes";
    const std::string file = dataset + ".csv";

    try {
        Table table = makeTable(dataset);
        {
            std::ifstream in(file);
            if (in) { table.loadCsv(in); std::cout << "Loaded " << table.rowCount() << " rows from " << file << "\n"; }
            else std::cout << file << " not found - starting with an empty table\n";
        }

        for (;;) {
            std::cout << "\n1 add   2 show all   3 search   4 sort   5 delete   6 statistics   7 save   8 indexed search   0 exit\n";
            std::string choice;
            if (!ask("> ", choice)) break;                       // end of input
            const int cmd = std::atoi(choice.c_str());
            try {
                if (cmd == 0) break;
                else if (cmd == 1) {
                    Table::Row r;
                    for (const Column& c : table.columns()) { std::string v; if (!ask(c.name + ": ", v)) return 0; r.push_back(v); }
                    table.add(r);
                    std::cout << "Added.\n";
                }
                else if (cmd == 2) table.print(std::cout);
                else if (cmd == 3) {
                    std::size_t col; std::string text;
                    if (!askColumn(table, col) || !ask("Text to find: ", text)) continue;
                    const std::vector<std::size_t> found = table.find(col, text);
                    table.print(std::cout, &found);
                }
                else if (cmd == 4) {
                    std::size_t col; std::string asc;
                    if (!askColumn(table, col) || !ask("Ascending? (y/n): ", asc)) continue;
                    table.sortBy(col, !(asc == "n" || asc == "N"));
                    table.print(std::cout);
                }
                else if (cmd == 5) {
                    std::string n;
                    if (!ask("Row number: ", n)) continue;
                    const int k = std::atoi(n.c_str());
                    if (k < 1) { std::cout << "No such row.\n"; continue; }
                    table.removeAt(static_cast<std::size_t>(k - 1));
                    std::cout << "Deleted.\n";
                }
                else if (cmd == 6) {
                    std::size_t col;
                    if (!askColumn(table, col)) continue;
                    const Table::Stats s = table.stats(col);
                    std::cout << "count " << s.count << ", min " << s.min << ", max " << s.max << ", average " << s.average << "\n";
                }
                else if (cmd == 7) {
                    std::ofstream out(file);
                    if (!out) { std::cout << "Cannot write " << file << "\n"; continue; }
                    table.saveCsv(out);
                    std::cout << "Saved " << table.rowCount() << " rows to " << file << "\n";
                }
                else if (cmd == 8) {
                    // text column: prefix search; number column: range search - both through a sorted index
                    std::size_t col;
                    if (!askColumn(table, col)) continue;
                    const rdb::Index index(table, col);
                    std::vector<std::size_t> found;
                    if (table.columns()[col].type == ColumnType::Text) {
                        std::string prefix;
                        if (!ask("Starts with: ", prefix)) continue;
                        found = index.findPrefix(prefix);
                    } else {
                        std::string from, to;
                        if (!ask("From: ", from) || !ask("To: ", to)) continue;
                        if (!isReal(from) || !isReal(to)) { std::cout << "Please enter numbers.\n"; continue; }
                        found = index.findRange(std::strtod(from.c_str(), nullptr), std::strtod(to.c_str(), nullptr));
                    }
                    table.print(std::cout, &found);
                }
                else std::cout << "Unknown command.\n";
            }
            catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
