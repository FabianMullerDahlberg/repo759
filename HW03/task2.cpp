// task2.cpp
#include "convolution.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
#include <omp.h>


int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "usage: " << argv[0] << " n t\n";
        return 1;
    }
    const std::size_t n = std::strtoull(argv[1], nullptr, 10);
    const std::size_t t = std::strtoull(argv[2], nullptr, 10);
    if (n < 1 || t < 1 || t > 20) {
        std::cerr << "need n > 0 and t in range [1, 20]\n";
        return 1;
    }

    std::mt19937 prng(0);//std::random_device{}());
    std::uniform_real_distribution<float> imgDist(-10.0f, 10.0f);
    std::uniform_real_distribution<float> maskDist(-1.0f, 1.0f);

    float *image = new float[n * n];
    for (std::size_t i = 0; i < n * n; ++i) image[i] = imgDist(prng);

    const std::size_t m = 3;
    float *mask = new float[m * m];
    for (std::size_t i = 0; i < m * m; ++i) mask[i] = maskDist(prng);

    float *output = new float[n * n];

    omp_set_num_threads(t);
    auto start = std::chrono::steady_clock::now();
    convolve(image, output, n, mask, m);
    auto stop = std::chrono::steady_clock::now();
    const double time = std::chrono::duration<double, std::milli>(stop - start).count();
            
    std::cout << output[0] << '\n';          
    std::cout << output[n * n - 1] << '\n';  
    std::cout << time << '\n';

    delete[] image;
    delete[] mask;
    delete[] output;
    return 0;
}
//g++ task2.cpp convolution.cpp -Wall -O3 -std=c++17 -o task2 -fopenmp