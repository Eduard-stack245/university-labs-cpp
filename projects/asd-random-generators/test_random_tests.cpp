#include "test_random.h"

#include <stdexcept>

int main()
{
    test_random test;
    for (int i = 0; i < COUNT_NUMBERS; ++i)
        test.add(static_cast<float>((i % 5) * 0.2 + 0.1));
    if (test.size() != COUNT_NUMBERS) return 1;
    test.calculation();
    test.clear();
    if (test.size() != 0) return 1;
    bool rejected = false;
    try { test.add(1.0f); }
    catch (const std::invalid_argument&) { rejected = true; }
    return rejected ? 0 : 1;
}
