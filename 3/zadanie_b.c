#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
 int main(int argc, char* argv[]){
 int pdesk[2], pid1,pid2;
 pipe(pdesk);
 if (fork() == 0){ // potomek 1
 pid1 = getpid();
 close(pdesk[0]);
 for (int i=0; i<=30; i+=3){
 write(pdesk[1], &i, sizeof(int));
 printf("%d umiescil %d\n", pid1, i);
 sleep (1);}
close(pdesk[1]);
 exit(0);
 }
 else
 if (fork () == 0){ // potomek 2
 int j;
 pid2 = getpid();
 close(pdesk[1]);
 for (int i=0; i<=30; i+=3){
 read(pdesk[0], &j, sizeof(int));
 printf("%d pobral %d\n", pid2, j);
 sleep (2);}
close(pdesk[0]);
 exit(0);
 }
 else {
 waitpid(-1, NULL, 0); //czekanie na dowolnego potomka; równowa¿ne wait(NULL);
 waitpid(-1, NULL,0); //czekanie na dowolnego potomka; równowa¿ne wait(NULL);
 }
 exit (0);
 }
