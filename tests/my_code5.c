// code demonstrates usage of semaphores to handle critical section

// compile as gcc -g -Wall -o my_code5 my_code5.c -lm -lpthread

// run as ./my_code5 <number_of_threads>

//---------------------------------Header section-------------------------------------//
#include <stdio.h>            // header file for built-in standard i/p & o/p functions
#include <stdlib.h>           // header file for standard library functions
#include <unistd.h>
#include <pthread.h>          // header file for pthread function
#include <sys/time.h>

#include <semaphore.h>        // header file for semaphore functions


int answer = 0;

sem_t sem;                    // semaphore declaration



//---------------------------------Main section-------------------------------------//

void* printing(void* X){
    long number = (long) X;
    printf("Hello from thread %ld \n", number);
    
    sem_wait(&sem);          // lock the following section for one thread
    
    int temp = answer;
    usleep (1000* (rand()%100));
    answer = temp + number;

    sem_post(&sem);          // unlock the section for other threads 
    
    printf("Bye from thread %ld \n", number);
    return NULL;
}

int main(int arg, char* argv[]){

    int thread_count = strtol(argv[1], NULL, 10);  
    pthread_t* thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t)); 
    
    sem_init(&sem, 0, 1);      
    
    long i;
 
    for (i = 1; i <= thread_count; i++)  
       pthread_create(&thread_handles[i], NULL, printing, (void*)i);
  
    for (i = 1; i <= thread_count; i++)            
       pthread_join(thread_handles[i], NULL);  
 
    sem_destroy(&sem);         // destroy semaphore

    free(thread_handles);      // free thread handle 


    printf("Final answer = %d \n",answer);

    return 0; 
}




