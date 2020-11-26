#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define rozm 512
pthread_mutex_t mx;
int buf[rozm], poz_zap=0, poz_odcz=0;
void* prod(void* info)
{
    int i;
    while(1)
    {
        sleep(2);
        pthread_mutex_lock(&mx);
        buf[poz_zap] = i;
        printf("prod umiescil %d na pozycji %d\n", i, poz_zap);
        poz_zap = (poz_zap+1)%rozm;
        i++;
        pthread_mutex_unlock(&mx);
    }
    return NULL;
}
void* kons(void* info)
{
    int i;
    while(1)
    {
        pthread_mutex_lock(&mx);
        i = buf[poz_odcz];
        printf("kons pobral %d z pozycji %d\n", i, poz_odcz);
        poz_odcz = (poz_odcz+1)%rozm;
        pthread_mutex_unlock(&mx);
        sleep(3);
    }
    return NULL;
}
int main()
{
    pthread_t th1, th2;
    pthread_mutex_init(&mx, NULL);
    pthread_create(&th1, NULL, prod, NULL);
    sleep(5);
    pthread_create(&th2, NULL, kons, NULL);
    pthread_create(&th2, NULL, kons, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return 0;
}
