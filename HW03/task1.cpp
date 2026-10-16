// task1.cpp
#include "matmul.h"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <omp.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "usage: " << argv[0] << " n t\n";
        return 1;
    }
    const std::size_t n = std::strtoull(argv[1], nullptr, 10);
    const unsigned int t = std::strtoull(argv[2], nullptr, 10);
    if (n < 1 || t < 1 || t > 20) {
        std::cerr << "need n > 0 and t in range [1, 20]\n";
        return 1;
    }

    omp_set_num_threads(t);
    const std::size_t size = static_cast<std::size_t>(n) * n;

    std::vector<float> A(size);
    std::vector<float> B(size);
    std::vector<float> C(size);

    std::mt19937 generator(0);
    std::uniform_real_distribution<float> distribution(0.0, 1.0);

    for (std::size_t i = 0; i < size; ++i) {
        A[i] = distribution(generator);
        B[i] = distribution(generator);
    }

    auto start = std::chrono::high_resolution_clock::now();

    mmul(A.data(), B.data(), C.data(), n);

    auto end = std::chrono::high_resolution_clock::now();

    double time =
        std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << C[0] << '\n';
    std::cout << C[size - 1] << '\n';
    std::cout << time << '\n';

    return 0;
}

// g++ task1.cpp matmul.cpp -Wall -O3 -std=c++17 -o task1 -fopenmp