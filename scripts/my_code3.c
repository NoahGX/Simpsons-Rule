// code prints helloi and bye using multiple threads

// compile as gcc -g -Wall -o my_code3 my_code3.c -lm -lpthread

// run as ./my_code3 <number_of_threads>

//---------------------------------Header section-------------------------------------//
#include <stdio.h>            // header file for built-in standard i/p & o/p functions
#include <stdlib.h>           // header file for standard library functions
#include <unistd.h>
#include <pthread.h>          // header file for pthread function
#include <sys/time.h>
int answer = 0;

pthread_mutex_t mutex;        // Mutex declaration


//---------------------------------Main section-------------------------------------//

void* printing(void* X){
    int number = (int) X;
    printf("Hello from thread %d \n", number);
    

    pthread_mutex_lock(&mutex);   
    int temp = answer;
    usleep (1000* (rand()%100));
    answer = temp + number;
    pthread_mutex_unlock(&mutex);   
    
    printf("Bye from thread %d \n", number);
}

int main(int arg, char* argv[]){

    int thread_count = strtol(argv[1], NULL, 10);  
    pthread_t* thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t)); 
    
    pthread_mutex_init(&mutex, NULL);    // Mutex initialization 
   
 
    for (int i = 1; i <= thread_count; i++)  
       pthread_create(&thread_handles[i], NULL, printing, (void*)i);
  
    for (int i = 1; i <= thread_count; i++)            
       pthread_join(thread_handles[i], NULL);  
 


    pthread_mutex_destroy(&mutex);    

    free(thread_handles);      // free thread handle 


    printf("Final answer = %d \n",answer);

    return 0; 
}




