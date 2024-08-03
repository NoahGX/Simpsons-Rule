#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

printf ("Hello from Prog2 -  Process_ID = %d \n", getpid());

char *args[] = { NULL};

execv("./prog_fork",args);

printf ("Bye from Prog 2 - Process_ID = %d \n", getpid());


return 0;

}
