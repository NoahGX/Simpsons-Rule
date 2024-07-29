#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include "timer.h"

# define M_PI 3.1415926535897931

// Define function to be integrated
double f(double x) {
    return (4.0 / (1.0 + (x * x)));
}

// Function to implement Simpsons Method
double simpsons_pi(int N) {
    // Lower limit of integral
    double a = 0.0;
    // Upper limit of integral
    double b = 1.0;
    // Declare equation for delta x
    double h = (b - a) / N;

    double sum = f(a) + f(b);

    // Apply Simpsons Rule
    for (int i = 1; i < N; i++) {
        double x = a + (i * h);
        if (i % 2 == 0) {
            sum += 2.0 * f(x);
        } else {
            sum += + 4.0 * f(x);
        }
    }
    sum *= (h / 3.0);
    return sum;
}

// Main function
int main(int arg, char* argv[]) {
    // Check if number of input parameters is valid
    if (arg != 2) {
        if (arg > 2) {
            fprintf(stderr, "ERROR: Incorrect Usage. Input cannot be more than one number. \n\n");
            exit(EXIT_FAILURE);
        }
        fprintf(stderr, "ERROR: Incorrect Usage. Run as ./serial1 <number>. \n\n");
        exit(EXIT_FAILURE);
    }
    
    // If paramter is valid, ensure it is within valid range
    int n = atoi(argv[1]);
    if (n < 1 || n > 10) {
        fprintf(stderr, "ERROR: Incorrect Usage. Input must be a number between 1 and 10. \n\n");
        exit(EXIT_FAILURE);
    }
    
    // Calculate number of N intervals
    double N = pow(10, n);
    
    // Get and print true value of PI from Math.h
    double exact = M_PI;
    printf("Exact value of PI: %.16lf \n", exact);
    
    // Calculate and print our estimated value of PI using Simpsons Method
    double estimate = simpsons_pi(N);
    printf("Estimated value of PI: %.16lf \n", estimate);
    
    // Calculate and print computation error
    double error = fabs(exact - estimate);
    printf("The Computation Error is: %.16lf \n", error);

    printf("\n");
    return 0;
}
