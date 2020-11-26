#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int readers = 0;
pthread_mutex_t mutex_r = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_w = PTHREAD_MUTEX_INITIALIZER;

void *czytelnik(int *arg)
{
    printf("czytelnik id %d\n", *arg);
    fflush(stdout);

    while (1)
    {
        pthread_mutex_lock(&mutex_r);
        readers++;
        if (readers == 1)
            pthread_mutex_lock(&mutex_w);
        pthread_mutex_unlock(&mutex_r);

        printf("czytelnik %d czyta\n", *arg);
        fflush(stdout);
        sleep(1);

        pthread_mutex_lock(&mutex_r);
        readers--;
        if (readers == 0)
            pthread_mutex_unlock(&mutex_w);
        pthread_mutex_unlock(&mutex_r);
    }
    return NULL;
}

void *pisarz(void *arg)
{
    printf("pisarz dobija siê do drzwi\n");
    fflush(stdout);

    while (1)
    {
        pthread_mutex_lock(&mutex_w);

        sleep(1);
        printf("pisze prosze nie przeszkadzac :)\n");
        fflush(stdout);

        pthread_mutex_unlock(&mutex_w);
    }
    return NULL;
}

int main()
{
    pthread_t pisarzWatek;
    pthread_t czytelnikWatek1;
    pthread_t czytelnikWatek2;
    int id1 = 1;
    int id2 = 2;
    pthread_create(&pisarzWatek, NULL, pisarz, NULL);
    pthread_create(&czytelnikWatek1, NULL, czytelnik, &id1);
    pthread_create(&czytelnikWatek2, NULL, czytelnik, &id2);
    pthread_join(pisarzWatek, NULL);
    pthread_join(czytelnikWatek1, NULL);
    pthread_join(czytelnikWatek2, NULL);
}
