
// compile as gcc -g -Wall -o my_code1 my_code1.c -lm -lpthread

// run as ./my_code1

//---------------------------------Header section-------------------------------------//
#include <stdio.h>            // header file for built-in standard i/p & o/p functions
#include <stdlib.h>           // header file for standard library functions
#include <unistd.h>
#include <pthread.h>

//---------------------------------Main section-------------------------------------//

void* printing(void* X){
    int number = (int) X;
    printf("Hello World. from %d \n", number);
    sleep(2);
    printf("bye. from %d \n", number);
}

int main(int arg, char* argv[]){

    pthread_t t1, t2;
    pthread_create(&t1, NULL, &printing,1);
    pthread_create(&t2, NULL, &printing,2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0; 
}




