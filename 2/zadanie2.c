#include <stdio.h>
#include <stdlib.h>

main(){
	if(!fork()) { // if(fork() == 0)
		sleep(30);
		printf("sierota1\n");
		exit(0);
	}
	if(!fork()) {
		sleep(30);
		printf("sierota2\n");
		exit(0);
	}
	if(!fork()) {
		sleep(30);
		printf("sierote3\n");
		exit(0);
	}
	exit(1);
}
