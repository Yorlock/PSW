#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[]){
 int par, liczba, wynik=1;
 int desc_cel;
 par=atoi(argv[1]);
 for(int i=1; i<=par; i++)
 wynik=wynik*i;
 printf("wartosc silni=%d\n",wynik);
 desc_cel = creat(argv[2], 0640);
 if (desc_cel == -1){
 perror("Blad utworzenia pliku docelowego");
 exit(1);
 }
 if (write(desc_cel, &wynik, sizeof(int)) == -1){
 perror("Blad zapisu pliku docelowego");
 exit(1);
 }
 if (close(desc_cel) == -1){
 perror("Blad zamkniecia pliku docelowego");
 exit(1);
 }
 exit(0);
}
