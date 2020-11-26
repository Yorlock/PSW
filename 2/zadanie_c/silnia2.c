#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int var = atoi(argv[1]);
	int result = 1;
	for(var; var > 0; var-- ){
		result = var*result;
		}
	close(1);
	int desc_cel = creat(argv[2],0640);
	write(desc_cel, &result, sizeof(result));
	return 0;
	}
