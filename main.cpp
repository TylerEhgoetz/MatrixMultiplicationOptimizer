#include <chrono>
#include <iostream>
#include <random>
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

void benchmarkMatrixMultiplication(
    const Matrix& A, const Matrix& B, int iterations, size_t blockSize
)
{
    using namespace std::chrono;
    double totalTimeNaive = 0.0;
    double totalTimeTiled = 0.0;

    for (int iter{ 0 }; iter < iterations; ++iter)
    {
        auto   start = high_resolution_clock::now();
        Matrix C     = naiveMultiply(A, B);
        auto   end   = high_resolution_clock::now();
        totalTimeNaive += duration_cast<duration<double>>(end - start).count();
    }

    for (int iter{ 0 }; iter < iterations; ++iter)
    {
        auto   start = high_resolution_clock::now();
        Matrix C     = tiledMultiply(A, B, blockSize);
        auto   end   = high_resolution_clock::now();
        totalTimeTiled += duration_cast<duration<double>>(end - start).count();
    }

    std::cout << "Average time for naive multiplication: "
              << (totalTimeNaive / iterations) << " seconds over " << iterations
              << " iterations\n";
    std::cout << "Average time for tiled multiplication: "
              << (totalTimeTiled / iterations) << " seconds over " << iterations
              << " iterations with block size " << blockSize << "\n";
    std::cout << "Speedup: " << (totalTimeNaive / totalTimeTiled) << "x\n";
}

int main()
{
    const size_t n{ 1024 };         // Size of the matrix
    const size_t blockSize{ 64 };   // Block size for tiled multiplication
    const int    iterations{ 5 };   // Number of iterations for benchmarking

    // Initialize matrices A and B with random values
    Matrix                                 A(n, std::vector<double>(n));
    Matrix                                 B(n, std::vector<double>(n));
    std::random_device                     rd;
    std::mt19937                           gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    for (size_t i{ 0 }; i < n; ++i)
    {
        for (size_t j{ 0 }; j < n; ++j)
        {
            A[i][j] = dis(gen);
            B[i][j] = dis(gen);
        }
    }
    // Benchmark the matrix multiplication
    benchmarkMatrixMultiplication(A, B, iterations, blockSize);
    return 0;
}
