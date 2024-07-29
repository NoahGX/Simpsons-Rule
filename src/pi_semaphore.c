#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "timer.h"

# define M_PI 3.1415926535897931

// Total number of threads
double thread_count;
// Lower limit of integral
double low = 0.0;
// Upper limit of integral
double high = 1.0;
// Resulting answer from Simpsons Method
double final_result = 0.0;
// Fixed value of N intervals
const double N = 6400000.0;

// Declare semaphore to use in critical section
sem_t semaphore;

// Define function to be integrated
double f(double x) {
    return (4.0 / (1.0 + (x * x)));
}

// Function to implement Simpsons Method
void* simpsons_pi(void* X) {
    // Declare equation for delta x
    long thread_id = (long) X;
    double dx = (high - low) / N;

    // Number of intervals per thread
    double local_N = N / thread_count;
    double local_low = low + (local_N * thread_id * dx);
    double local_high = local_low + (local_N * dx);
    double local_result = f(local_low) + f(local_high);

    // Apply Simpsons Rule
    for (int i = 1; i < local_N; i++) {
        double x = local_low + (i * dx);
        if (i % 2 == 0) {
            local_result += 2.0 * f(x);
        } else {
            local_result += 4.0 * f(x);
        }
    }
    local_result *= (dx / 3.0);

    // Lock section with semaphore for one thread
    sem_wait(&semaphore);
    // Handle critical section
    final_result += local_result;
    // Unlock section with semaphore for other threads 
    sem_post(&semaphore);
    return NULL;
}

// Main function
int main(int arg, char* argv[]) {
    // Declare variables for timer
    double start, finish, elapsed;
    double runtime_1_thread;

    // Check if number of input arguments is valid
    if (arg != 2) {
        if (arg > 2) {
            fprintf(stderr, "ERROR: Incorrect Usage. Input cannot be more than one number. \n\n");
            exit(EXIT_FAILURE);
        }
        fprintf(stderr, "ERROR: Incorrect Usage. Run as ./p_thread <number>. \n\n");
        exit(EXIT_FAILURE);
    }
    
    // If input is valid, ensure it is within valid range
    int n = atoi(argv[1]);
    if (n < 1 || n > 16) {
        fprintf(stderr, "ERROR: Incorrect Usage. Input must be a number between 1 and 10. \n\n");
        exit(EXIT_FAILURE);
    }
    
    // Tabulate
    printf("\nPerformance Evaluation using SEMAPHORE method: \n");
    printf("\nNumber of iterations N = 6400000 \n");
    printf("\nNumber of Threads \t Runtime \t\t Efficiency \t\t Speed-Up \t\t Computation Error \n");
    printf("=================================================================================================================== \n");

    for (int thread = 1; thread <= n; thread++) {
        thread_count = thread;
        // Initialize number of threads
        pthread_t* thread_handles = (pthread_t*)malloc(thread_count*sizeof(pthread_t));
        final_result = 0.0;

        // Initialize semaphore
        sem_init(&semaphore, 0, 1);

        // Start timer
        GET_TIME(start);

        // Create threads
        for (long thread = 0; thread < thread_count; thread++) {
            // Using each thread, calculate estimated value of PI
            pthread_create(&thread_handles[thread], NULL, simpsons_pi, (void*)thread);
        }

        // Join threads
        for (long thread = 0; thread < thread_count; thread++) {
            pthread_join(thread_handles[thread], NULL);
        }

        // Stop timer and calculate total time
        GET_TIME(finish);
        elapsed = finish - start;

        // Capture time elapsed for single thread
        if (thread_count == 1) {
            runtime_1_thread = elapsed;
        }

        // Calculate speed-up and efficiency
        double speed_up = runtime_1_thread / elapsed;
        double efficiency = runtime_1_thread / (thread_count * elapsed);

        // Calculate computation error and print table
        double error = fabs(M_PI - final_result);
        printf("\t%-10d \t %-10.16lf \t %-10.16lf \t %.16lf \t %.16lf \n", thread, elapsed, efficiency, speed_up, error);

        // Destroy semaphore and free threads
        sem_destroy(&semaphore);
        free(thread_handles);
    }
    printf("\n");
    return 0;
}
