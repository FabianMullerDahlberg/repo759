// task2.cpp
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>

#include "convolution.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "usage: " << argv[0] << " n m\n";
        return 1;
    }
    const std::size_t n = std::strtoull(argv[1], nullptr, 10);
    const std::size_t m = std::strtoull(argv[2], nullptr, 10);
    if (n == 0 || m == 0 || m % 2 == 0) {
        std::cerr << "need n >= 1 and odd m >= 1\n";
        return 1;
    }

    std::mt19937 prng(std::random_device{}());
    std::uniform_real_distribution<float> imgDist(-10.0f, 10.0f);
    std::uniform_real_distribution<float> maskDist(-1.0f, 1.0f);

    float *image = new float[n * n];
    for (std::size_t i = 0; i < n * n; ++i) image[i] = imgDist(prng);

    float *mask = new float[m * m];
    for (std::size_t i = 0; i < m * m; ++i) mask[i] = maskDist(prng);

    float *output = new float[n * n];

    auto start = std::chrono::steady_clock::now();
    convolve(image, output, n, mask, m);
    auto stop = std::chrono::steady_clock::now();
    const double ms = std::chrono::duration<double, std::milli>(stop - start).count();

    std::cout << ms << '\n';            
    std::cout << output[0] << '\n';          
    std::cout << output[n * n - 1] << '\n';  

    delete[] image;
    delete[] mask;
    delete[] output;
    return 0;
}
//g++ convolution.cpp task2.cpp -Wall -O3 -std=c++17 -o task2