// task3.cpp

#include "matmul.h"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main() {
    const unsigned int n = 1000;
    const std::size_t size = static_cast<std::size_t>(n) * n;

    std::vector<double> A(size);
    std::vector<double> B(size);
    std::vector<double> C(size);

    std::mt19937 generator(0);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (std::size_t i = 0; i < size; ++i) {
        A[i] = distribution(generator);
        B[i] = distribution(generator);
    }

    std::cout << n << '\n';

    auto start = std::chrono::high_resolution_clock::now();

    mmul1(A.data(), B.data(), C.data(), n);

    auto end = std::chrono::high_resolution_clock::now();

    double time1 =
        std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << time1 << '\n';
    std::cout << C[size - 1] << '\n';


    start = std::chrono::high_resolution_clock::now();

    mmul2(A.data(), B.data(), C.data(), n);

    end = std::chrono::high_resolution_clock::now();

    double time2 =
        std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << time2 << '\n';
    std::cout << C[size - 1] << '\n';


    start = std::chrono::high_resolution_clock::now();

    mmul3(A.data(), B.data(), C.data(), n);

    end = std::chrono::high_resolution_clock::now();

    double time3 =
        std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << time3 << '\n';
    std::cout << C[size - 1] << '\n';


    start = std::chrono::high_resolution_clock::now();

    mmul4(A, B, C.data(), n);

    end = std::chrono::high_resolution_clock::now();

    double time4 =
        std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << time4 << '\n';
    std::cout << C[size - 1] << '\n';

    return 0;
}

// g++ task3.cpp matmul.cpp -Wall -O3 -std=c++17 -o task3