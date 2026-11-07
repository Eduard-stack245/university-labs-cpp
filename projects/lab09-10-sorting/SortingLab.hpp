#pragma once

// Both algorithms and binary search use descending order.
inline int binarySearch(const int* arr, int value, int left, int right) {
    while (left <= right) {
        const int mid = left + (right - left) / 2;
        if (arr[mid] == value) return mid;
        if (arr[mid] < value) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}

inline void quickSort(int* arr, int first, int last) {
    if (first >= last) return;
    const int pivot = arr[last];
    int split = first;
    for (int i = first; i < last; ++i) {
        if (arr[i] >= pivot) {
            const int temp = arr[i];
            arr[i] = arr[split];
            arr[split] = temp;
            ++split;
        }
    }
    const int temp = arr[split];
    arr[split] = arr[last];
    arr[last] = temp;
    quickSort(arr, first, split - 1);
    quickSort(arr, split + 1, last);
}

inline void choiceSort(int* arr, int first, int last) {
    for (int i = first; i <= last; ++i) {
        int largest = i;
        for (int j = i + 1; j <= last; ++j)
            if (arr[j] > arr[largest]) largest = j;
        const int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
    }
}
