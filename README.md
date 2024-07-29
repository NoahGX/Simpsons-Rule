# Pi Calculation using Simpson's Rule

## Overview
This project implements three separate C programs that approximate the value of π (Pi) using Simpson's method. Each program uses a different parallel computing approach to perform the calculations: serial processing, mutex-based synchronization, and semaphore-based synchronization.

## Features
  - **pi_serial.c:** Approximates π using Simpson's method in a serial manner.
  - **pi_mutex.c:** Uses multiple threads with mutex for synchronization to compute the value of π.
  - **pi_semaphore.c:** Employs multiple threads and semaphore synchronization to calculate π.
  - **timer.h:** Header file that defines a macro for timing operations with microsecond accuracy.

## Usage
To compile and run all programs, use the provided Makefile:
  ```bash
  make all
  ```

## Prerequisites
  - GCC compiler
  - Standard C libraries
  - POSIX Threads library (`pthread`)
  - POSIX Semaphores (if available on the system)

## Input
Each program accepts a single command-line argument:
  - **pi_serial:** Number between 1 and 10, specifying the power of 10 for the number of intervals.
  - **pi_mutex and pi_semaphore:** Number between 1 and 16, indicating the number of threads to be used.

## Output
  - **pi_serial:** A table displaying the computation error for different numbers of intervals.
  - **pi_mutex and pi_semaphore:** Performance tables showing runtime, efficiency, speed-up, and computation error for various thread counts.

## Notes
  - Ensure that your system supports POSIX threads and semaphores if you intend to run `pi_mutex.c` and `pi_semaphore.c`.
  - The `timer.h` header is crucial for performance evaluation and must be included in the same directory as the source files.
  - The error calculation in each program measures the difference between the computed value of π and the exact value as defined by M_PI.