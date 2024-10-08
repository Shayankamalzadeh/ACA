# Optimized Matrix Multiplication and Inversion with MPI

This project focuses on optimized matrix multiplication and inversion using **MPI (Message Passing Interface)**. The goal is to perform these operations efficiently by leveraging parallel computing, especially for large matrices. The project demonstrates how to split matrix operations across multiple processors to improve performance and achieve significant speedup.

## Table of Contents
- [Introduction](#introduction)
- [Configuration](#configuration)
  - [MinGW-w64 Setup](#mingw-w64-setup)
  - [Microsoft MPI Setup](#microsoft-mpi-setup)
  - [Visual Studio Code (VS Code) Configuration](#visual-studio-code-vs-code-configuration)
- [Optimized Matrix Multiplication Algorithm](#optimized-matrix-multiplication-algorithm)
  - [How the Code Works](#how-the-code-works)
  - [Why MPI is Used](#why-mpi-is-used)
  - [Key MPI Functions Used](#key-mpi-functions-used)
- [Matrix Inversion with MPI](#matrix-inversion-with-mpi)
  - [How the Code Works](#how-the-code-works-1)
  - [Key MPI Functions Used](#key-mpi-functions-used-1)
- [Test Results and Sample Graph](#test-results-and-sample-graph)
- [Google Cloud Performance Report](#google-cloud-performance-report)

## Introduction

Matrix multiplication and inversion are computationally expensive tasks, especially when dealing with large matrices. This project uses **MPI** to parallelize these operations, making them faster by dividing the workload across multiple processors. By running tasks in parallel, we can significantly reduce execution time, particularly for large datasets.

## Configuration

### MinGW-w64 Setup

Before running the project, ensure you have MinGW-w64 installed. Follow these steps to configure it:

1. **Download MinGW-w64:**
   - Visit the [MinGW-w64 website](http://mingw-w64.org/doku.php) and download the appropriate installer for your system.

2. **Install MinGW-w64:**
   - Run the installer and follow the instructions.
   - Add the MinGW-w64 `bin` directory to your system’s PATH to ensure it’s accessible.

### Microsoft MPI Setup

For parallel processing, you will need to install Microsoft MPI:

1. **Download Microsoft MPI:**
   - Visit the [Microsoft MPI download page](https://www.microsoft.com/en-us/download/details.aspx?id=57467) and download the installer.

2. **Install Microsoft MPI:**
   - Run the installer and follow the installation instructions.

### Visual Studio Code (VS Code) Configuration

To work on this project in VS Code, follow these steps:

1. **Install VS Code:**
   - Download and install [Visual Studio Code](https://code.visualstudio.com/).

2. **Extensions:**
   - Install necessary extensions for C/C++ development in VS Code (e.g., the C/C++ extension from Microsoft).

3. **Configure MPI in VS Code:**
   - Set the path to the MPI executables in your VS Code configuration to ensure MPI commands are available.

## Optimized Matrix Multiplication Algorithm

This project implements matrix multiplication using MPI to distribute the workload across processors and speed up the process.

### How the Code Works

1. **MPI Initialization**: The program starts by initializing the MPI environment, which sets up communication between all participating processors.
2. **Matrix Setup**: Each processor generates its part of two matrices and is assigned a block of rows to work on.
3. **Parallel Matrix Multiplication**: The multiplication task is divided, with each processor working on its assigned rows.
4. **Gathering Results**: Once the multiplication is completed, each processor sends its results back to the root processor to assemble the final matrix.
5. **Timing**: The total execution time is measured and displayed by the root processor.

### Why MPI is Used

MPI enables matrix multiplication to be done in parallel. This significantly speeds up the process by using multiple processors to share the workload, especially for large matrices that would take a long time if done sequentially.

### Key MPI Functions Used:
- `MPI_Init`: Initializes the MPI environment.
- `MPI_Comm_rank`: Determines the rank (ID) of each processor.
- `MPI_Comm_size`: Determines the total number of processors involved.
- `MPI_Bcast`: Broadcasts data (e.g., matrix size) to all processors.
- `MPI_Gather`: Gathers computed results from all processors to the root processor.
- `MPI_Wtime`: Measures the time taken for execution.
- `MPI_Finalize`: Closes the MPI environment after computation is complete.

## Matrix Inversion with MPI

In addition to matrix multiplication, this project also implements **matrix inversion** using the **Gauss-Jordan elimination** algorithm. The inversion process is also parallelized with MPI to enhance performance.

### How the Code Works

1. **MPI Initialization**: The MPI environment is initialized to allow communication between processors.
2. **Matrix Setup**: The matrix is created on the root processor and distributed among all available processors.
3. **Parallel Gauss-Jordan Elimination**:
   - Each processor handles its assigned rows.
   - The pivot row is broadcast to all processors, and they use this row to update their own rows.
4. **Gathering Results**: The results from each processor are gathered at the root processor to reconstruct the final inverted matrix.
5. **Timing**: The total time taken for matrix inversion is measured and displayed at the end.

### Key MPI Functions Used:
- `MPI_Init`: Initializes the MPI environment.
- `MPI_Comm_rank`: Identifies each processor’s rank.
- `MPI_Comm_size`: Determines the total number of processors.
- `MPI_Scatter`: Distributes parts of the matrix to different processors.
- `MPI_Bcast`: Broadcasts the pivot row to all processors.
- `MPI_Gather`: Collects the partial results from each processor.
- `MPI_Wtime`: Measures the execution time of the matrix inversion process.
- `MPI_Finalize`: Finalizes and closes the MPI environment.

## Test Results and Sample Graph

All test results related to this project, including performance data for different matrix sizes and CPU counts, are located in the **Test-Result** folder. The results demonstrate how execution time changes with varying numbers of CPUs and matrix sizes.

To generate visual graphs from the test results, you can use the `GraphGenerate.py` script. This Python script reads the test data and generates graphs that show execution time vs matrix size for different CPU counts.

## Google Cloud Performance Report

I conducted comprehensive testing on Google Cloud for this project to measure the performance speedup of matrix multiplication and inversion. The full report on these tests, including details on setup, speedup, and results, is available in the `report.pdf` file.
