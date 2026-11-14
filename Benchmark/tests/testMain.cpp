#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <functional>
#include "../src/Sorting.h"



std::vector<int> GenerateRandomVector(size_t size, int minVal, int maxVal)
{
    std::vector<int> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(minVal, maxVal);
    for (size_t i = 0; i < size; ++i)
    {
        vec[i] = dis(gen);
    }
    return vec;
}

std::vector<int> GenerateSortedVector(size_t size)
{
    std::vector<int> vec(size);
    for (size_t i = 0; i < size; ++i)
    {
        vec[i] = static_cast<int>(i);
    }
    return vec;
}

std::vector<int> GenerateReverseSortedVector(size_t size)
{
    std::vector<int> vec(size);
    for (size_t i = 0; i < size; ++i)
    {
        vec[i] = static_cast<int>(size - i);
    }
    return vec;
}

std::vector<int> GenerateAlmostSortedVector(size_t size)
{
    auto vec = GenerateSortedVector(size);
    if (size < 2) return vec;

    size_t swapsCount = std::max(size_t(1), size / 100);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, size - 1);

    for (size_t i = 0; i < swapsCount; ++i)
    {
        size_t idx1 = dis(gen);
        size_t idx2 = dis(gen);
        std::swap(vec[idx1], vec[idx2]);
    }
    return vec;
}


void RunBenchmarkTest(const std::string& algoName, 
                      const std::string& dataType, 
                      size_t size, 
                      const std::vector<int>& originalVec,
                      std::function<bool(std::vector<int>&, NBenchmark::SSortStats&)> sortingFunc)
{
    auto vecCopy = originalVec;
    NBenchmark::SSortStats stats;

    
    auto start = std::chrono::high_resolution_clock::now();
    sortingFunc(vecCopy, stats);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "| " << std::left << std::setw(21) << algoName 
              << " | " << std::setw(13) << dataType 
              << " | " << std::setw(8) << size 
              << " | " << std::right << std::setw(10) << duration << " us"
              << " | " << std::setw(11) << stats.comparisons 
              << " | " << std::setw(10) << stats.swaps << " |\n";
}


int main()
{
    std::cout << "=== VARIANT 1: Quadratic Sorts & Input Data Types Benchmark ===\n\n";

    // Шапка таблицы
    std::cout << "| Algorithm             | Data Type     | Size     | Time       | Comparisons | Swaps      |\n";
    std::cout << "|-----------------------|---------------|----------|------------|-------------|------------|\n";

    std::vector<size_t> sizes = {1000, 2000, 4000, 8000};

    for (size_t size : sizes)
    {
        auto dataRandom  = GenerateRandomVector(size, 0, 100000);
        auto dataSorted  = GenerateSortedVector(size);
        auto dataReverse = GenerateReverseSortedVector(size);
        auto dataAlmost  = GenerateAlmostSortedVector(size);

        std::vector<std::pair<std::string, std::vector<int>>> datasets = {
            {"Random", dataRandom},
            {"Sorted", dataSorted},
            {"Reverse", dataReverse},
            {"AlmostSorted", dataAlmost}
        };

        for (const auto& [dataType, data] : datasets)
        {
            RunBenchmarkTest("BubbleSortClassic",   dataType, size, data, NBenchmark::BubbleSortClassic<int>);
            RunBenchmarkTest("BubbleSortOptimized", dataType, size, data, NBenchmark::BubbleSortOptimized<int>);
            RunBenchmarkTest("InsertionSort",       dataType, size, data, NBenchmark::InsertionSort<int>);
            RunBenchmarkTest("SelectionSort",       dataType, size, data, NBenchmark::SelectionSort<int>);
            RunBenchmarkTest("StdSort",             dataType, size, data, NBenchmark::StdSort<int>);
        }
    }

    std::cout << "\nAll benchmarks completed successfully!\n";
    return 0;
}