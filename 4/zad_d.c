#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
pthread_mutex_t mojmuteks=PTHREAD_MUTEX_INITIALIZER;
int buf[512];
void *prod(void *arg)
{
    int i = 0;
    while(true)
    {
        pthread_mutex_lock(&mojmuteks);
        buf[i % 512] = i;
        printf("prod umiescil %d na pozycji %d\n",i, buf[i % 512]);
        fflush(stdout);
        i++;
        pthread_mutex_unlock(&mojmuteks);
        sleep(2);
    }
    return NULL;
}
int main(void)
{
    pthread_t mojwatek, mojwatek2;
    int j = 0;
    if ( pthread_create( &mojwatek, NULL, prod, NULL) )
    {
        printf("blad przy tworzeniu watka.");
        abort();
    }
    while(true)
    {
        pthread_mutex_lock(&mojmuteks);
        int pobranie = buf[j % 512];
        printf("kons pobral %d z pozycji %d",j, buf[j % 512]);
        fflush(stdout);
        j++;
        pthread_mutex_unlock(&mojmuteks);
        sleep(3);
    }
    if ( pthread_join ( mojwatek, NULL ) )
    {
        printf("blad przy koñczeniu watka.");
        abort();
    }
    exit(0);
}
