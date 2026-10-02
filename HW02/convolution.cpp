// convolution.cpp
#include "convolution.h"
#include <vector>

void convolve(const float *image, float *output, std::size_t n, const float *mask, std::size_t m) {
    const std::size_t r = (m - 1) / 2, pw = n + 2 * r;

    std::vector<float> p(pw * pw);
    for (std::size_t a = 0; a < pw; ++a) {
        const bool row_in = (a >= r && a < r + n);
        for (std::size_t b = 0; b < pw; ++b) {
            const bool col_in = (b >= r && b < r + n);
            p[a * pw + b] = (row_in && col_in) ? image[(a - r) * n + (b - r)]
                          : (row_in || col_in) ? 1.0f   
                                               : 0.0f;  
        }
    }

    for (std::size_t x = 0; x < n; ++x) {
        for (std::size_t y = 0; y < n; ++y) {
            float sum = 0.0f;
            for (std::size_t i = 0; i < m; ++i) {
                const float *row = &p[(x + i) * pw + y];
                const float *wr = &mask[i * m];
                for (std::size_t j = 0; j < m; ++j) sum += wr[j] * row[j];
            }
            output[x * n + y] = sum;
        }
    }
}