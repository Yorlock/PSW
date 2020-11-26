#include <stdio.h>
#include <stdlib.h>

main(){
	printf("-----POCZATEK LISTY----\n");
	switch (fork()){
	case -1:
		perror("Blad utworzenia procesu potomnego");
		break;
	case 0:
		execlp("ps", "ps", NULL);
		perror("Blad uruchmienia programu");
		exit(1);
	default:
		if (wait(NULL) == -1)
		perror("Blad w oczekiwaniu na zakonczenie potomka");
	}
	printf("----KONIEC LISTY----\n");
}
