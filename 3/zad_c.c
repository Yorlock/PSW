#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
    int pdesk, pidm,pidp;
    if (mkfifo("kolejka", 0600) == -1){
    	exit(1);
    }
	
    if (fork() == 0)  // potomek 1
    {
        pidp = getpid();
	pdesk = open("kolejka", O_WRONLY);
        for (int i=0; i<=30; i+=2)
        {
            write(pdesk, &i, sizeof(int));
            printf("%d umiescil %d\n", pidp, i);
            sleep (1);
        }
        exit(0);
    }
    else if (fork() == 0)  // potomek 2
    {
        int buf;
        pidm = getpid();
	pdesk = open("kolejka", O_RDONLY);
        for (int i=0; i<=30; i+=2)
        {
            read(pdesk, &buf, sizeof(int));
            printf("%d pobral %d\n", pidm, buf);
            sleep (2);
        }
    }
    else {
    	waitpid(pidm,NULL,0);
	waitpid(pidp,NULL,0);
    }
    exit(0);
}
