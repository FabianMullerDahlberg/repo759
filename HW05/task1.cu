#include<cuda.h>
#include<iostream>


__global__ void factorial_kernel(const int *input, int n) {
    
    int factorial, idx;
    factorial = 1; 
    idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        int val = input[idx];
        for (int i = 2; i <= val; i++) {
            factorial *= i;
        }
        printf("%d!=%d \n",val,factorial);
    }
}


int main() {

    const int numElems = 8;
    int hostArray[numElems], *intArray;

    for (int i = 0 ; i < numElems ; ++i) {
        hostArray[i] = i + 1;
    }
    //allocate memory on the device (GPU); zero out all entries in this device array 
    cudaMalloc((void**)&intArray, sizeof(int) * numElems);
    cudaMemcpy(intArray, hostArray, numElems * sizeof(int), cudaMemcpyHostToDevice);

    //invoke GPU kernel, with one block that has four threads
    factorial_kernel<<<1,numElems>>>(intArray, numElems);
    cudaDeviceSynchronize(); 
    
    //release the memory allocated on the GPU 
    cudaFree(intArray);
    return 0;
}// nvcc task1.cu -Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17 -o task1