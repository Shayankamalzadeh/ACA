#include <iostream>
#include <vector>
#include <ctime>

std::vector<std::vector<int>> multiplyMatrices(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) {
    int n = matrix1.size();
    std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <matrix_size>\n";
        return 1;
    }
     int n = std::atoi(argv[1]);
    // Create two n x n matrices with rectangular patterns
    std::vector<std::vector<int>> matrix1(n, std::vector<int>(n, 1));
    std::vector<std::vector<int>> matrix2(n, std::vector<int>(n, 1));

    // Measure the time taken to multiply the matrices
    clock_t start = clock();
    std::vector<std::vector<int>> resultMatrix = multiplyMatrices(matrix1, matrix2);
    clock_t end = clock();

    double time_taken = double(end - start) / CLOCKS_PER_SEC;

   std::cout << "Time taken: " << (time_taken) << " seconds.\n";

    return 0;
}
