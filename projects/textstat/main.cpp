// textstat - statistics of a text file (or of standard input).
//   textstat [--top N] [file ...]        no file or "-" = read standard input
//   textstat --help
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "TextStat.hpp"
#include "lab_compat.h"

static void usage()
{
    std::cout << "textstat - statistics of UTF-8 text\n\n"
                 "usage: textstat [--top N] [file ...]\n"
                 "  --top N   how many words / letters to list (default 10)\n"
                 "  no file or '-' reads standard input\n";
}

static void print(const std::string& name, const ts::Report& r, std::size_t top)
{
    std::cout << "== " << name << " ==\n";
    std::cout << "bytes " << r.bytes << ", characters " << r.characters << ", lines " << r.lines << "\n";
    std::cout << "words " << r.words << ", letters " << r.letters << ", digits " << r.digits << "\n";
    std::cout << "words of odd length " << r.oddLengthWords << ", average word length " << std::fixed << std::setprecision(2) << r.averageWordLength;
    if (!r.longestWord.empty()) std::cout << ", longest word: " << r.longestWord;
    std::cout << "\n";

    std::cout << "\nmost frequent words:\n";
    for (std::size_t i = 0; i < r.wordFrequency.size() && i < top; i++)
        std::cout << "  " << std::setw(5) << r.wordFrequency[i].second << "  " << r.wordFrequency[i].first << "\n";

    std::cout << "\nletter frequency (case-insensitive):\n";
    std::size_t maxCount = r.letterFrequency.empty() ? 1 : r.letterFrequency[0].second;
    for (std::size_t i = 0; i < r.letterFrequency.size() && i < top; i++) {
        const auto& lf = r.letterFrequency[i];
        const double percent = 100.0 * static_cast<double>(lf.second) / static_cast<double>(r.letters);
        std::cout << "  " << lf.first << "  " << std::setw(5) << lf.second << "  " << std::setw(5) << std::setprecision(1) << percent << "%  "
                  << std::string(lf.second * 30 / maxCount, '#') << "\n";
    }

    if (!r.parenthesized.empty() || r.unclosedParentheses || r.unmatchedClosing) {
        std::cout << "\ntext in parentheses:\n";
        for (const std::string& p : r.parenthesized) std::cout << "  (" << p << ")\n";
        if (r.unclosedParentheses) std::cout << "  warning: " << r.unclosedParentheses << " unclosed '('\n";
        if (r.unmatchedClosing) std::cout << "  warning: " << r.unmatchedClosing << " ')' without a matching '('\n";
    }
    std::cout << "\n";
}

int main(int argc, char** argv)
{
    lab::init_console();
    std::size_t top = 10;
    std::vector<std::string> files;
    for (int i = 1; i < argc; i++) {
        const std::string a = argv[i];
        if (a == "--help" || a == "-h") { usage(); return 0; }
        if (a == "--top" && i + 1 < argc) { const int n = std::atoi(argv[++i]); if (n < 1) { std::cerr << "--top needs a positive number\n"; return 1; } top = static_cast<std::size_t>(n); }
        else if (a.size() > 1 && a[0] == '-') { std::cerr << "unknown option " << a << "\n"; usage(); return 1; }
        else files.push_back(a);
    }
    if (files.empty()) files.push_back("-");

    int status = 0;
    for (const std::string& f : files) {
        std::string text;
        if (f == "-") text.assign(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());
        else {
            std::ifstream in(f, std::ios::binary);
            if (!in) { std::cerr << "cannot open " << f << "\n"; status = 1; continue; }
            text.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
        }
        print(f == "-" ? "standard input" : f, ts::analyze(text), top);
    }
    return status;
}
