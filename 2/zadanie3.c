#include <stdio.h>
#include <stdlib.h>

main(){
	printf("Poczatek\n");
	switch (fork()){
	case -1:
		perror("Blad utworzenia procesu potomnego");
		break;
	case 0:
		execlp("ls", "ls", NULL);
		perror("Blad uruchmienia programu");
		exit(1);
	default:
		if (wait(NULL) == -1)
		perror("Blad w oczekiwaniu na zakonczenie potomka");
	}
	printf("Koniec\n");
}
