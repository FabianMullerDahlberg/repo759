#include <cuda_runtime.h>
#include <iostream>
#include <random>
#include <cstdlib>

#include "vscale.cuh"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " n\n";
        return 1;
    }
    const unsigned int n = std::strtoul(argv[1], nullptr, 10);

    std::mt19937 prng(std::random_device{}());
    std::uniform_real_distribution<float> aDist(-10.0f, 10.0f);
    std::uniform_real_distribution<float> bDist(0.0f, 1.0f);

    float *hA = new float[n], *hB = new float[n];
    float *dA, *dB;

    for (unsigned int i = 0; i < n; ++i) {
        hA[i] = aDist(prng);
        hB[i] = bDist(prng);
    }

    cudaMalloc((void**)&dA, sizeof(float) * n);
    cudaMalloc((void**)&dB, sizeof(float) * n);

    cudaMemcpy(dA, hA, sizeof(float) * n, cudaMemcpyHostToDevice);
    cudaMemcpy(dB, hB, sizeof(float) * n, cudaMemcpyHostToDevice);

    const unsigned int threads = 16;
    const unsigned int blocks = (n + threads - 1) / threads;

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    vscale<<<blocks, threads>>>(dA, dB, n);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float ms = 0.0f;
    cudaEventElapsedTime(&ms, start, stop);

    cudaMemcpy(hB, dB, sizeof(float) * n, cudaMemcpyDeviceToHost);

    std::cout << ms << "\n";
    std::cout << hB[0] << "\n";
    std::cout << hB[n - 1] << "\n";

    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaFree(dA);
    cudaFree(dB);
    delete[] hA;
    delete[] hB;

    return 0;
}
// nvcc task3.cu vscale.cu -Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17 -o task3