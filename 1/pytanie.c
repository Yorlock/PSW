#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 512
int main(int argc, char* argv[])
{
    char buf[MAX];
    int desc, desc_cel;
    long rozm;
    int lbajt;
    if (argc < 3)
    {
        fprintf(stderr, "Za malo argumentow. Uzyj:\n");
        fprintf(stderr, "%s <nazwa pliku>\n", argv[0]);
        exit(1);
    }

    desc = open(argv[1], O_RDONLY);
    if (desc == -1)
    {
        perror("Blad otwarcia pliku");
        exit(1);
    }

    rozm = lseek(desc, 0, SEEK_END);
    if (rozm == -1)
    {
        perror("Blad w pozycjonowaniu");
        exit(1);
    }
    lseek(desc, 0, SEEK_SET);

    desc_cel = creat(argv[2], 0640);
    rozm = rozm / 2;
    lbajt = read(desc, buf, rozm);
    if (write(desc_cel, buf, lbajt) == -1){
         exit(1);
    }

    if (close(desc) == -1)
    {
        perror("Blad zamkniecia pliku");
        exit(1);
    }
    if (close(desc_cel) == -1)
    {
        perror("Blad zamkniecia pliku");
        exit(1);
    }

    exit(0);
}
