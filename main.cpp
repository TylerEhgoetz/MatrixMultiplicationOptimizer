#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<double>>;

Matrix naiveMultiply(const Matrix& A, const Matrix& B)
{
    size_t n = A.size();
    Matrix C(n, std::vector<double>(n, 0.0));
    for (size_t i{ 0 }; i < n; ++i)
    {
        for (size_t j{ 0 }; j < n; ++j)
        {
            for (size_t k{ 0 }; k < n; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

Matrix tiledMultiply(const Matrix& A, const Matrix& B, size_t blockSize)
{
    size_t n = A.size();
    Matrix C(n, std::vector<double>(n, 0.0));

    for (size_t i{ 0 }; i < n; i += blockSize)
    {
        for (size_t j{ 0 }; j < n; j += blockSize)
        {
            for (size_t k{ 0 }; k < n; k += blockSize)
            {
                // Perform the multiplication for the block
                for (size_t i2{ i }; i2 < std::min(i + blockSize, n); ++i2)
                {
                    for (size_t j2{ j }; j2 < std::min(j + blockSize, n); ++j2)
                    {
                        for (size_t k2{ k }; k2 < std::min(k + blockSize, n);
                             ++k2)
                        {
                            C[i2][j2] += A[i2][k2] * B[k2][j2];
                        }
                    }
                }
            }
        }
    }
    return C;
}

void benchmarkMatrixMultiplication();

int main()
{
    benchmarkMatrixMultiplication();
    return 0;
}
