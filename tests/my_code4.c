// code illustrates how the job can be divided among multiple threads

// compile as gcc -g -Wall -o my_code4 my_code4.c -lm -lpthread

// run as ./my_code4 <number_of_threads>

//---------------------------------Header section-------------------------------------//
#include <stdio.h>            // header file for built-in standard i/p & o/p functions
#include <stdlib.h>           // header file for standard library functions
#include <unistd.h>
#include <pthread.h>          // header file for pthread function

double thread_count;
double low = 0.0;
double high = 100.0;

double N = 1000.0;


//---------------------------------Main section-------------------------------------//

void* printing(void* X){
    int thread_id = (int) X;

    double dx = (high - low) / 1000.0;
    double local_N = 1000.0/thread_count;

    double local_low = low + (local_N*thread_id*dx);

    double local_high = local_low + (local_N*dx);

    printf("Hello from thread %d. Local low = %f and Local high = %f  \n", thread_id, local_low, local_high);

    
}

int main(int arg, char* argv[]){

    thread_count = strtol(argv[1], NULL, 10);  
    pthread_t* thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t)); 
    
 
    for (int thread = 0; thread < thread_count; thread++)  
       pthread_create(&thread_handles[thread], NULL, printing, (void*)thread);
  
    for (int thread = 0; thread < thread_count; thread++)            
       pthread_join(thread_handles[thread], NULL);  
 

    free(thread_handles);      // free thread handle 


    return 0; 
}




