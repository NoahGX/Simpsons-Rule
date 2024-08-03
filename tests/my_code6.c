// sample error handling code

// compile : gcc -o my_code6 my_code6.c

// Run as : ./my_code6 <number>


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Incorrect Usage. Run as ./pi_serial <number>\n");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);

    // atoi will return 0 if n isn't a number
    if (n == 0) {
        fprintf(stderr, "The entered argument is not a valid number.\n");
        exit(EXIT_FAILURE);
    }

    printf("The entered number is: %d\n", n);

    return 0;
}





