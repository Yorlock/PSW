#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
    int pdesk[2], pid1,pid2;
    pipe(pdesk);
    if (fork() == 0)  // proces potomny
    {
        pid1 = getpid();
        close(pdesk[0]);
        for (int i=0; i<=30; i+=3)
        {
            write(pdesk[1], &i, sizeof(int));
            printf("%d umiescil %d\n", pid1, i);
            sleep (1);
        }
        exit(0);
    }
    else if (fork () == 0) // proces macierzysty
    {
        int j;
        pid2 = getpid();
        close(pdesk[1]);
        for (int i=0; i<=30; i+=3)
        {
            read(pdesk[0], &j, sizeof(int));
            printf("%d pobral %d\n", pid2, j);
            sleep (2);
        }
        exit(0);
    }
    else
    {
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL,0);
    }
    exit (0);
}
