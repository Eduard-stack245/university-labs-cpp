#include "SortingLab.hpp"
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <vector>

void require(bool ok) {
    if (!ok) throw std::runtime_error("Sorting or binary search result is incorrect");
}

void check(const std::vector<int>& source) {
    std::vector<int> expected = source;
    std::sort(expected.begin(), expected.end(), std::greater<int>());
    std::vector<int> selection = source;
    std::vector<int> quick = source;
    if (!source.empty()) {
        choiceSort(selection.data(), 0, static_cast<int>(source.size()) - 1);
        quickSort(quick.data(), 0, static_cast<int>(source.size()) - 1);
    }
    require(selection == expected);
    require(quick == expected);
    for (int value : source) {
        const int index = binarySearch(quick.data(), value, 0, static_cast<int>(quick.size()) - 1);
        require(index >= 0 && quick[static_cast<std::size_t>(index)] == value);
    }
    require(binarySearch(quick.data(), 999999, 0, static_cast<int>(quick.size()) - 1) == -1);
    require(binarySearch(quick.data(), -999999, 0, static_cast<int>(quick.size()) - 1) == -1);
}

int main() {
    check({});
    check({1});
    check({4, 1, 3, 5, 4, 2, 0, -1, 8, 8});
    check({5, 4, 3, 2, 1, 0, -1});
    check({1, 2, 3, 4, 5});
    check({7, 7, 7, 7});
    return 0;
}
