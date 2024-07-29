// code prints hello and bye using multiple threads

// compile as gcc -g -Wall -o my_code2 my_code2.c -lm -lpthread

// run as ./my_code2 <number_of_threads>

//---------------------------------Header section-------------------------------------//
#include <stdio.h>            // header file for built-in standard i/p & o/p functions
#include <stdlib.h>           // header file for standard library functions
#include <unistd.h>
#include <pthread.h>          // header file for pthread function


//---------------------------------Main section-------------------------------------//

void* printing(void* X){
    int number = (int) X;
    printf("Hello from thread %d \n", number);
    sleep(2);
    printf("Bye from thread %d \n", number);
}

int main(int arg, char* argv[]){

    int thread_count = strtol(argv[1], NULL, 10);  
    pthread_t* thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t)); 
    
    for (int i = 0; i < thread_count; i++)  
       pthread_create(&thread_handles[i], NULL, printing, (void*)i);
  
    for (int i = 0; i < thread_count; i++)            
       pthread_join(thread_handles[i], NULL);  


    free(thread_handles);      // free thread handle 

    return 0; 
}




