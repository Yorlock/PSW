#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int* silnia (int* arg)
{
    printf("arg_watku=%d \n", *arg);
    int *wynik = malloc(sizeof(int));
    *wynik = 1;
    for(int i=1; i<= *arg; i++)
        *wynik = (*wynik)*i;
    return (int*) wynik;
}
int main (int argc, char* argv[])
{
    int wart_arg = atoi(argv[1]);
    int *wyn_silni;
    pthread_t watek;
    pthread_create (&watek, NULL, &silnia, &wart_arg);
    pthread_join (watek, (int**) &wyn_silni);
    printf("silnia(%d)=%d\n", wart_arg, *wyn_silni);
    free(wyn_silni);
    return 0;
}
