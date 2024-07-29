#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int arg, char *argv[]){

fork();
printf ("Hello from Prog1 -  Process_ID = %d \n", getpid());

return 0;

}
