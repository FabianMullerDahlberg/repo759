// task3.cpp
#include "msort.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include <omp.h>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "usage: " << argv[0] << " n t ts\n";
        return 1;
    }

    const std::size_t n = std::strtoull(argv[1], nullptr, 10);
    const std::size_t t = std::atoi(argv[2]);
    const std::size_t ts = std::strtoull(argv[3], nullptr, 10);

    if (n < 1 || t < 1 || t > 20 || ts < 1) {
        std::cerr << "need n > 0, t in [1, 20], and ts > 0\n";
        return 1;
    }

    std::vector<int> arr(n);

    std::mt19937 generator(0);
    std::uniform_int_distribution<int> distribution(-1000, 1000);

    for (std::size_t i = 0; i < n; ++i)
        arr[i] = distribution(generator);

    omp_set_num_threads(t);

    auto start = std::chrono::steady_clock::now();
    msort(arr.data(), n, ts);
    auto stop = std::chrono::steady_clock::now();

    const double time = std::chrono::duration<double, std::milli>(stop - start).count();

    std::cout << arr[0] << '\n';
    std::cout << arr[n - 1] << '\n';
    std::cout << time << '\n';

    return 0;
}
//g++ task3.cpp msort.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp