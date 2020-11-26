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

int main(int argc, char* argv[])
{
    if (argv < 3) {
        printf("Za malo argumentow.");
        exit(0);
    }
    pthread_t pisarzWatek[argv[1]];
    pthread_t czytelnikWatek[argv[2]];
    int id[argv[2]];
    for (int i = 0; i < argv[1]; i++){
        pthread_create(&pisarzWatek[i], NULL, pisarz, NULL);
    }
    for (int i = 0; i < argv[1]; i++){
        id[i] = i + 1;
        pthread_create(&czytelnikWatek[i], NULL, czytelnik, &id[i]);
    }
    for (int i = 0; i < argv[1]; i++){
        pthread_join(pisarzWatek[i], NULL);
        // pthread_create(&pisarzWatek[i], NULL, pisarz, NULL);
    }
    for (int i = 0; i < argv[1]; i++){
        pthread_join(czytelnikWatek[i], NULL);
        // id[i] = i + 1;
        // pthread_create(&czytelnikWatek[i], NULL, czytelnik, &id[i]);
    }
}
