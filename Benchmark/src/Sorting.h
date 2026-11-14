#pragma once

#include <vector>
#include <algorithm>

namespace NBenchmark
{

struct SSortStats
{
    unsigned long long comparisons = 0;
    unsigned long long swaps = 0;
};

// 1. Классическая пузырьковая сортировка
template<typename T>
bool BubbleSortClassic(std::vector<T>& arr, SSortStats& stats)
{
    stats = {0, 0};
    const size_t n = arr.size();
    if (n < 2) return std::is_sorted(arr.begin(), arr.end());

    for (size_t i = 0; i < n - 1; ++i)
    {
        for (size_t j = 0; j < n - 1; ++j)
        {
            stats.comparisons++;
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                stats.swaps++;
            }
        }
    }
    return std::is_sorted(arr.begin(), arr.end());
}

// 2. Оптимизированная пузырьковая сортировка
template<typename T>
bool BubbleSortOptimized(std::vector<T>& arr, SSortStats& stats)
{
    stats = {0, 0};
    const size_t n = arr.size();
    if (n < 2) return std::is_sorted(arr.begin(), arr.end());

    for (size_t i = 0; i < n - 1; ++i)
    {
        bool swapped = false;
        for (size_t j = 0; j < n - 1 - i; ++j)
        {
            stats.comparisons++;
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                stats.swaps++;
                swapped = true;
            }
        }
        if (!swapped) break; 
    }
    return std::is_sorted(arr.begin(), arr.end());
}

// 3. Сортировка вставками
template<typename T>
bool InsertionSort(std::vector<T>& arr, SSortStats& stats)
{
    stats = {0, 0};
    const size_t n = arr.size();
    if (n < 2) return std::is_sorted(arr.begin(), arr.end());

    for (size_t i = 1; i < n; ++i)
    {
        T key = arr[i];
        int j = static_cast<int>(i) - 1;

      
        while (j >= 0)
        {
            stats.comparisons++;
            if (arr[j] > key)
            {
                arr[j + 1] = arr[j];
                stats.swaps++;
                j--;
            }
            else
            {
                break;
            }
        }
        arr[j + 1] = key;
    }
    return std::is_sorted(arr.begin(), arr.end());
}

// 4. Сортировка выбором
template<typename T>
bool SelectionSort(std::vector<T>& arr, SSortStats& stats)
{
    stats = {0, 0};
    const size_t n = arr.size();
    if (n < 2) return std::is_sorted(arr.begin(), arr.end());

    for (size_t i = 0; i < n - 1; ++i)
    {
        size_t minIdx = i;
        for (size_t j = i + 1; j < n; ++j)
        {
            stats.comparisons++;
            if (arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
        }
        if (minIdx != i)
        {
            std::swap(arr[i], arr[minIdx]);
            stats.swaps++;
        }
    }
    return std::is_sorted(arr.begin(), arr.end());
}

// 5. Стандартная сортировка
template<typename T>
bool StdSort(std::vector<T>& arr, SSortStats& stats)
{
    stats = {0, 0};
    const size_t n = arr.size();
    if (n < 2) return std::is_sorted(arr.begin(), arr.end());

       std::sort(arr.begin(), arr.end());
    return std::is_sorted(arr.begin(), arr.end());
}

} // namespace NBenchmark