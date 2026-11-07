// Compares the lab generators with std::mt19937_64 using the chi-square test.
//   random_toolkit_demo [samples] [bins]      (defaults: 100000 and 10)
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

#include "ChiSquare.hpp"
#include "Generators.hpp"

template <class Engine>
void report(const std::string& name, Engine eng, std::size_t samples, int bins)
{
    Engine preview = eng;                 // copy: show the first numbers without disturbing the test
    std::cout << std::left << std::setw(22) << name << " first: ";
    for (int i = 0; i < 4; i++) std::cout << preview() << " ";

    const rtk::ChiSquareResult r = rtk::chi_square_uniform(eng, samples, bins);
    std::cout << "\n" << std::setw(22) << "" << " chi2 = " << std::fixed << std::setprecision(2) << r.statistic
              << "  (critical " << r.critical << ")  " << (r.passed ? "PASS" : "FAIL") << "\n";
}

int main(int argc, char** argv)
{
    std::size_t samples = argc > 1 ? static_cast<std::size_t>(std::atoll(argv[1])) : 100000;
    int bins = argc > 2 ? std::atoi(argv[2]) : 10;
    if (samples < 100 || bins < 2) { std::cerr << "usage: random_toolkit_demo [samples>=100] [bins>=2]\n"; return 1; }

    std::cout << "Chi-square test of uniformity: " << samples << " numbers, " << bins << " bins, significance 5%\n\n";
    report("Park-Miller",        rtk::ParkMiller(42), samples, bins);
    report("L'Ecuyer (lab name)", rtk::LEcuyer(2),     samples, bins);
    report("LCG m=100 a=8 c=65", rtk::LinearCongruential<100, 8, 65>(2), samples, bins);
    report("Blum-Blum-Shub 16b", rtk::BlumBlumShub<2111, 16>(56), samples, bins);
    report("std::mt19937_64",    std::mt19937_64(42),  samples, bins);

    // The engines work with the standard distributions and algorithms:
    std::cout << "\n10 dice rolls from Park-Miller via std::uniform_int_distribution: ";
    rtk::ParkMiller pm(7);
    std::uniform_int_distribution<int> dice(1, 6);
    for (int i = 0; i < 10; i++) std::cout << dice(pm) << " ";
    std::cout << "\n";
    return 0;
}
