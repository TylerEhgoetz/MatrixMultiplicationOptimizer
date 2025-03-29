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

void benchmarkMatrixMultiplication();

int main()
{
    benchmarkMatrixMultiplication();
    return 0;
}
