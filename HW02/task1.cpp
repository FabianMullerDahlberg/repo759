#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>

#include "scan.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(int argc, char *argv[]) {
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point stop;
    duration<double, std::milli> duration_sec; 

    const std::size_t N = std::strtoull(argv[1], nullptr, 10);

    std::mt19937 prng(std::random_device{}());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);  // built once, outside the loop

    std::vector<float> in(N), out(N);
    for (auto &x : in) x = dist(prng);

    start = high_resolution_clock::now();
    scan(in.data(), out.data(), N);
    stop = high_resolution_clock::now();
    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(stop - start);

    std::cout << duration_sec.count() << '\n'<< out[0] << '\n' << out[N-1] << std::endl;

    
}
// g++ scan.cpp task1.cpp -Wall -O3 -std=c++17 -o task1

