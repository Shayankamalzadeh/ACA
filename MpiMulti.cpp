#include <iostream>
#include <vector>
#include <mpi.h>

// Function to multiply a matrix block
std::vector<std::vector<int>> multiplyMatrixBlock(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B,
    int startRow, int endRow) {
    
    int N = A.size();
    std::vector<std::vector<int>> C(endRow - startRow, std::vector<int>(N, 0));
    
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i - startRow][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return C;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Check for proper usage and retrieve the matrix size
    if (argc != 2) {
        if (rank == 0) {
            std::cerr << "Usage: " << argv[0] << " <matrix_size>\n";
        }
        MPI_Finalize();
        return 1;
    }
    int n = std::atoi(argv[1]);
    
    // Broadcast the size of the matrix to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process creates its block of the matrix
    std::vector<std::vector<int>> matrix1(n, std::vector<int>(n, 1));
    std::vector<std::vector<int>> matrix2(n, std::vector<int>(n, 1));

    // Calculate the range of rows for each process
    int rows_per_process = n / size;
    int startRow = rank * rows_per_process;
    int endRow = (rank == size - 1) ? n : (rank + 1) * rows_per_process;

    // Start the timer
    MPI_Barrier(MPI_COMM_WORLD); // Wait for all processes to be ready
    double start_time = MPI_Wtime();

    // Perform matrix multiplication on the block
    auto local_result = multiplyMatrixBlock(matrix1, matrix2, startRow, endRow);

    // Gather the results from all processes
    std::vector<std::vector<int>> final_result(n, std::vector<int>(n, 0));
    for (int i = 0; i < rows_per_process; ++i) {
        MPI_Gather(local_result[i].data(), n, MPI_INT, final_result[startRow + i].data(), n, MPI_INT, 0, MPI_COMM_WORLD);
    }

    // Stop the timer
    double end_time = MPI_Wtime();

    if (rank == 0) {
       std::cout << "Time taken: " << (end_time - start_time) << " seconds.\n";
    }

    MPI_Finalize();
    return 0;
}
