#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
    int pdesk[2], pidm,pidp;
    pipe(pdesk);
    if (fork() == 0)  // potomek
    {
        pidp = getpid();
        close(pdesk[0]);
        for (int i=0; i<=30; i+=3)
        {
            write(pdesk[1], &i, sizeof(int));
            printf("%d umiescil %d\n", pidp, i);
            sleep (1);
        }
        exit(0);
    }
    else   // macierzysty
    {
        int j;
        pidm = getpid();
        close(pdesk[1]);
        for (int i=0; i<=30; i+=3)
        {
            read(pdesk[0], &j, sizeof(int));
            printf("%d pobral %d\n", pidm, j);
            sleep (2);
        }
    }
}
