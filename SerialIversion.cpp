#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Function to perform Gauss-Jordan elimination for matrix inversion
void gaussJordanInversion(std::vector<std::vector<double>>& matrix) {
    int N = matrix.size();
    std::vector<std::vector<double>> identity(N, std::vector<double>(N, 0.0));

    // Initialize the identity matrix
    for (int i = 0; i < N; i++) {
        identity[i][i] = 1.0;
    }

    // Gaussian elimination
    for (int i = 0; i < N; i++) {
        double pivot = matrix[i][i];
        if (pivot == 0.0) {
            std::cerr << "Matrix is singular or near singular." << std::endl;
            return;
        }

        // Divide the row by the pivot
        for (int j = 0; j < N; j++) {
            matrix[i][j] /= pivot;
            identity[i][j] /= pivot;
        }

        // Eliminate other rows
        for (int k = 0; k < N; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = 0; j < N; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                    identity[k][j] -= factor * identity[i][j];
                }
            }
        }
    }

    // Copy the inverted matrix (identity matrix) back to 'matrix'
    matrix = identity;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <matrix_size>\n";
        return 1;
    }

    // Convert the argument to an integer
    int N = std::atoi(argv[1]);

    std::vector<std::vector<double>> matrix(N, std::vector<double>(N));

    // Generate a random matrix
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = static_cast<double>(rand()) / RAND_MAX;
        }
    }

    // Start measuring time
    clock_t start_time = clock();

    // Perform matrix inversion
    gaussJordanInversion(matrix);

    // Stop measuring time
    clock_t end_time = clock();

    // Calculate time taken
    double time_taken = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    // Print the inverted matrix and time taken
    std::cout << "Inverted Matrix:" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Time taken for matrix inversion: " << time_taken << " seconds." << std::endl;

    return 0;
}
