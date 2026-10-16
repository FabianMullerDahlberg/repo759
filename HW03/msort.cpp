
#include "msort.h"
#include <vector>
#include <algorithm>

void merge(int* arr, int* temp, std::size_t mid, std::size_t n) {
    std::size_t i = 0, j = mid, k = 0;

    while (i < mid && j < n)
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];

    while (i < mid) temp[k++] = arr[i++];
    while (j < n) temp[k++] = arr[j++];

    std::copy(temp, temp + n, arr);
}

void mergesort(int* arr, int* temp, std::size_t n, std::size_t threshold) {
    if (n <= 1) return;

    if (n < threshold) {
        std::sort(arr, arr + n);
        return;
    }

    const std::size_t mid = n / 2;

    #pragma omp task
    mergesort(arr, temp, mid, threshold);

    #pragma omp task
    mergesort(arr + mid, temp + mid, n - mid, threshold);

    #pragma omp taskwait
    merge(arr, temp, mid, n);
}

void msort(int* arr, const std::size_t n, const std::size_t threshold) {
    std::vector<int> temp(n);

    #pragma omp parallel
    {
        #pragma omp single
        mergesort(arr, temp.data(), n, threshold);
    }
}
