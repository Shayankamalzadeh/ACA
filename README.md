# Optimized Matrix Multiplication and Inversion

This project focuses on optimized matrix multiplication and inversion, with an emphasis on rectangular matrices as a mandatory requirement for multiplication.

## Configuration

### MinGW-w64 Setup

Before diving into the project, ensure that you have MinGW-w64 installed. Follow these steps to configure it:

1. **Download MinGW-w64:**
   - Visit the [MinGW-w64 website](http://mingw-w64.org/doku.php) and download the installer suitable for your system.

2. **Install MinGW-w64:**
   - Run the installer and follow the installation instructions.
   - Make sure to add the MinGW-w64 bin directory to your system's PATH variable.

### Microsoft MPI Setup

For parallel computing, Microsoft MPI is required. Here's how you can set it up:

1. **Download Microsoft MPI:**
   - Visit the [Microsoft MPI download page](https://www.microsoft.com/en-us/download/details.aspx?id=57467) and download the installer.

2. **Install Microsoft MPI:**
   - Run the installer and follow the installation instructions.

### Visual Studio Code (VS Code) Configuration

To work with the project in Visual Studio Code, follow these steps:

1. **Install VS Code:**
   - Download and install [Visual Studio Code](https://code.visualstudio.com/).

2. **Extensions:**
   - Install the necessary extensions for C/C++ development.

3. **Configure Microsoft MPI in VS Code:**
   - Set the MPI executable path in your VS Code configuration.

Now, you are ready to work with the project in VS Code with MinGW-w64 and Microsoft MPI properly configured.

## Optimized Matrix Multiplication Algorithm

# Matrix Multiplication with MPI

This project demonstrates how to perform matrix multiplication in parallel using **MPI (Message Passing Interface)**. The code splits the multiplication task across multiple processors to speed up the operation, especially for large matrices.

## How the Code Works

1. **MPI Initialization**: The program starts by initializing the MPI environment, which sets up communication between processors.
2. **Matrix Setup**: Each processor creates two matrices and is assigned a block of rows to work on.
3. **Parallel Matrix Multiplication**: The matrix multiplication task is divided, and each processor works on its assigned rows.
4. **Gathering Results**: After each processor finishes, the results are gathered by the root processor to form the final matrix.
5. **Timing**: The time taken for the entire multiplication process is measured and displayed by the root processor.

## Why MPI is Used

MPI allows the matrix multiplication to be divided into parts and run in parallel. This significantly speeds up the process by using multiple processors to share the workload. Without MPI, the task would be done sequentially, taking much longer.

### Key MPI Functions Used:
- `MPI_Init`: Initializes the MPI environment.
- `MPI_Comm_rank`: Gets the unique ID (rank) of each processor.
- `MPI_Comm_size`: Determines the total number of processors.
- `MPI_Bcast`: Broadcasts data (like matrix size) to all processors.
- `MPI_Gather`: Gathers the computed results from all processors to the root processor.
- `MPI_Wtime`: Measures the time taken for execution.
- `MPI_Finalize`: Shuts down the MPI environment.




Briefly introduce the optimized algorithm you are implementing for matrix multiplication. Highlight the key optimizations that make your approach efficient, especially when dealing with rectangular matrices. Consider providing a high-level overview or pseudocode to help readers grasp the main concepts.

Remember to update and customize these instructions based on the specific details and nuances of your project. Additionally, include any relevant commands or code snippets that users may need during the configuration process.
