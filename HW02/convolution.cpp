// convolution.cpp

#include "convolution.h"
#include <vector>

void convolve(const float* image, float* output, std::size_t n, const float* mask, std::size_t m) {
    const std::size_t radius = (m - 1) / 2;
    const std::size_t padded_size = n + 2 * radius;

    std::vector<float> padded(padded_size * padded_size);

    // Add padded
    for (std::size_t row = 0; row < padded_size; ++row) {
        for (std::size_t col = 0; col < padded_size; ++col) {

            bool inside_rows =
                row >= radius && row < radius + n;

            bool inside_cols =
                col >= radius && col < radius + n;

            if (inside_rows && inside_cols) {
                padded[row * padded_size + col] =
                    image[(row - radius) * n + (col - radius)];
            }
            else if (inside_rows || inside_cols) {
                padded[row * padded_size + col] = 1.0f;
            }
            else {
                padded[row * padded_size + col] = 0.0f;
            }
        }
    }

    // Convolution
    for (std::size_t row = 0; row < n; ++row) {
        for (std::size_t col = 0; col < n; ++col) {

            float sum = 0.0f;

            for (std::size_t mask_row = 0; mask_row < m; ++mask_row) {
                for (std::size_t mask_col = 0; mask_col < m; ++mask_col) {

                    std::size_t image_index =
                        (row + mask_row) * padded_size
                        + (col + mask_col);

                    std::size_t mask_index =
                        mask_row * m + mask_col;

                    sum += padded[image_index] * mask[mask_index];
                }
            }

            output[row * n + col] = sum;
        }
    }
}