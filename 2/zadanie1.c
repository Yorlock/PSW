#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pid = getpid();
    int child_pid = fork();
    if(child_pid == 0)
    {
        int child_getpid = getpid();
printf("child p: %d,c: %d\n",pid, child_getpid);
        int grand_child_pid = fork();
        if(grand_child_pid == 0)
        {
            int grand_child_getpid = getpid();
            printf("grand_child p: %d,c: %d\n",child_getpid, grand_child_getpid);
            exit(0);
        }
        exit(0);
    }
    int child2_pid = fork();
    if(child2_pid == 0)
    {
        int child2_getpid = getpid();
        printf("child2 p: %d, c: %d\n", pid, child2_getpid);
        int grand_child2_pid = fork();
        if(grand_child2_pid == 0)
        {
            int grand_child2_getpid = getpid();
            printf("grand_child2 p: %d, c: %d\n", child2_getpid, grand_child2_getpid);
            exit(0);
        }
        exit(0);
    }
    wait();
}
