#include<cuda.h>
#include<iostream>
#include <random>

__global__ void simpleKernel(int* data, int a) {
    //this adds a value to a variable stored in global memory
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    data[idx] = a*threadIdx.x + blockIdx.x;
}

int main() {
    const int numElems = 16;
    int hA[numElems], *dA;

    int some_seed = 759;
    std::mt19937 generator(some_seed);
    std::uniform_int_distribution<int> distribution(1, 10);
    int a = distribution(generator);

    //allocate memory on the device (GPU); zero out all entries in this device array 
    cudaMalloc((void**)&dA, sizeof(int) * numElems);
    //invoke GPU kernel, with one block that has four threads
    simpleKernel<<<2,8>>>(dA, a);
    //bring the result back from the GPU into the host array 
    cudaMemcpy(hA, dA, sizeof(int) * numElems, cudaMemcpyDeviceToHost);
    //print out the result to confirm that things are looking good 
    for (int i = 0; i < numElems; i++)
        std::cout << hA[i] << " ";
    std::cout << std::endl; 
    //release the memory allocated on the GPU 
    cudaFree(dA);
    return 0;
}// nvcc task2.cu -Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17 -o task2