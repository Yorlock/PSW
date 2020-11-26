#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
    int pdesk, pid1;
    if (mkfifo("buf", 0666) == -1)
    {
        perror("Tworzenie kolejki FIFO");
        exit(1);
    }
    else // zapisywanie
    {
        pid1 = getpid();
        pdesk = open("buf", O_WRONLY);
        for (int i=0; i<=30; i+=2)
        {
            write(pdesk, &i, sizeof(int));
            printf("%d umiescil %d\n", pid1, i);
            sleep (1);
        }
        close(pdesk);
        exit(0);
    }
}
