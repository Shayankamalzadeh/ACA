#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mpi.h>

void gaussJordanInversion(std::vector<std::vector<double>>& matrix, int rank, int size) {
    int N = matrix.size();
    for (int i = 0; i < N; ++i) {
        // Broadcast the pivot row
        if (i % size == rank) {
            for (int j = 0; j < N; ++j) {
                matrix[i % size][j] /= matrix[i % size][i];
            }
        }
        MPI_Bcast(matrix[i % size].data(), N, MPI_DOUBLE, i % size, MPI_COMM_WORLD);

        // Update rows
        for (int k = 0; k < N / size; ++k) {
            if (i % size != rank) {
                double factor = matrix[k][i];
                for (int j = 0; j < N; ++j) {
                    matrix[k][j] -= factor * matrix[i % size][j];
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Parse input
    if (argc != 2) {
        if (rank == 0) std::cerr << "Usage: " << argv[0] << " <matrix_size>\n";
        MPI_Finalize();
        return 1;
    }

    int N = std::atoi(argv[1]);
    if (N % size != 0) {
        if (rank == 0) std::cerr << "Matrix size must be divisible by the number of processes.\n";
        MPI_Finalize();
        return 1;
    }

    std::vector<double> local_matrix(N * N / size);
    std::vector<double> full_matrix;

    if (rank == 0) {
        full_matrix.resize(N * N);
        srand(time(NULL));
        for (int i = 0; i < N * N; ++i) full_matrix[i] = static_cast<double>(rand()) / RAND_MAX;
    }

    MPI_Scatter(full_matrix.data(), N * N / size, MPI_DOUBLE, local_matrix.data(), N * N / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    std::vector<std::vector<double>> local_matrix_2d(N / size, std::vector<double>(N));
    for (int i = 0; i < N / size; ++i) {
        for (int j = 0; j < N; ++j) {
            local_matrix_2d[i][j] = local_matrix[i * N + j];
        }
    }

    double start_time = MPI_Wtime();
    gaussJordanInversion(local_matrix_2d, rank, size);
    double end_time = MPI_Wtime();

    for (int i = 0; i < N / size; ++i) {
        for (int j = 0; j < N; ++j) {
            local_matrix[i * N + j] = local_matrix_2d[i][j];
        }
    }

    MPI_Gather(local_matrix.data(), N * N / size, MPI_DOUBLE, full_matrix.data(), N * N / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        
        std::cout << "Time taken: " << (end_time - start_time) << " seconds.\n";
    }

    MPI_Finalize();
    return 0;
}
