#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
    int pdesk, pid2;
    pdesk = open ("buf", O_RDONLY);
    if (pdesk == -1)
    {
        perror("Otwieranie kolejki FIFO");
        exit(1);
    }
    else // odczytywanie
    {
        pid2 = getpid();
        for (int i=0; i<=30; i+=2)
        {
            read(pdesk, &i, sizeof(int));
            printf("%d pobral %d\n", pid2, i);
            sleep (2);
        }
        close(pdesk);
        exit(0);
    }
}
