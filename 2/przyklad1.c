/* Program liczy silniê argv[1], zamyka deskryptor 1, zapisuje (binarnie) wynik w pliku arg[v2],
zamyka deskryptor 0, czyta zapisany wczeœniej w pliku wynik, odtwarza standardowe wyjœcie
i wypisuje na nie przeczytany wynik */
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
    int par, liczba, wynik=1;
    char str[10];
    int desc_cel, desc_zrod;
    par=atoi(argv[1]);
    for(int i=1; i<=par; i++)
        wynik=wynik*i;
    printf("wartosc silni=%d\n",wynik);
    close(1); //zamkniêcie standardowego wyjœcia
    desc_cel = creat(argv[2], 0640);
    if (desc_cel == -1)
    {
        perror("Blad utworzenia pliku docelowego");
        exit(1);
    }
    write(desc_cel, &wynik, sizeof(int)); //zapisanie wyniku z wykorzystaniem deskryptora nr 1
    if (write(desc_cel, &wynik, sizeof(int)) == -1)
    {
        perror("Blad zapisu pliku docelowego");
        exit(1);
    }
    if (close(desc_cel) == -1)
    {
        perror("Blad zamkniecia pliku docelowego");
        exit(1);
    }
    close(0); //zamkniêcie standardowego wejœcia
    desc_zrod = open(argv[2], O_RDONLY); //czytanie z wykorzystaniem deskryptora nr 0
    sprintf(str,"%d\n", desc_zrod);
    perror(str);
    if (desc_zrod == -1)
    {
        perror("Blad otwarcia pliku zrodlowego");
        exit(1);
    }
    if (read(desc_zrod, &wynik, sizeof(int)) == -1)
    {
        perror("Blad odczytu pliku zrodlowego");
        exit(1);
    }
    freopen("/dev/tty", "w", stdout); //odtworzenie standardowego wyjœcia
    /*if (desc_cel == -1){
    perror("Blad otwarcia tty");
    exit(1);
    }*/
    printf("wynik=%d\n",wynik); //zapisanie na standardowe wyjœcie
    if (close(desc_zrod) == -1)
    {
        perror("Blad zamkniecia pliku zrodlowego");
        exit(1);
    }
    sprintf(str, "%d\n", wynik);
    perror(str); //ponowne zapisanie w wykorzystaniem standardowego deskryptora nr 2
    exit(0);
}
