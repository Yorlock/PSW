#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define rozm 4
pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;
int buf[rozm], poz_zap=0, poz_odcz=0, ile_jest=0;
void* prod(void* info)
{
    int i;
    while(1)
    {
        sleep(2);
        pthread_mutex_lock(&mx);
        printf("prod zamknal zamek\n");
        if (ile_jest == rozm)
        {
            printf("prod musi czekac\n");
//pthread_mutex_unlock(&mx);
            pthread_cond_wait(&c, &mx);
            printf("prod skonczyl czekanie\n");
        }
        buf[poz_zap] = i;
        printf("prod umiescil %d na pozycji %d\n", i, poz_zap);
        poz_zap = (poz_zap+1)%rozm;
        i++;
        ile_jest++;
        if (ile_jest == 1)
            pthread_cond_signal(&c);
        pthread_mutex_unlock(&mx);
        printf("prod otworzyl zamek\n");
    }
    return NULL;
}
void* kons(void* info)
{
    int i;
    while(1)
    {
        pthread_mutex_lock(&mx);
        printf("kons zamknal zamek\n");
        if (ile_jest == 0)
        {
            printf("kons musi czekac\n");
            pthread_cond_wait(&c, &mx);
            printf("kons skonczyl czekanie\n");
        }
        i = buf[poz_odcz];
        printf("kons pobral %d z pozycji %d\n", i, poz_odcz);
        poz_odcz = (poz_odcz+1)%rozm;
        ile_jest--;
        if (ile_jest == rozm-1)
            pthread_cond_signal(&c);
        pthread_mutex_unlock(&mx);
        printf("kons otworzyl zamek\n");
        sleep(3);
    }
    return NULL;
}
int main()
{
    pthread_t th1, th2;
//pthread_mutex_init(&mx, NULL);
//pthread_cond_init(&c, NULL);
    pthread_create(&th1, NULL, prod, NULL);
//sleep(5);
    pthread_create(&th2, NULL, kons, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return 0;
}
