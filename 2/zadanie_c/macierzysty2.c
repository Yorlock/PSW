#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int desc_zrod;
	close(1);
	if (fork() == 0){
		execl("./silnia2.exe", "silnia", "5", "plik_5", NULL);
		}
	wait(NULL);
	if (fork() == 0){
		execl("./silnia2.exe", "silnia", "3", "plik_3", NULL);
		}
	wait(NULL);
	if (fork() == 0){
		execl("./silnia2.exe", "silnia", "2", "plik_2", NULL);
		}
	wait(NULL);
	int buf_5, buf_3, buf_2;
	char buf_5s[80], buf_3s[80], buf_2s[80], results[80];
	desc_zrod = open("plik_5", O_RDONLY);
	read(desc_zrod, &buf_5, sizeof(int));
	sprintf(buf_5s, "wynik: %d", buf_5);
	perror(buf_5s);

	desc_zrod = open("plik_3", O_RDONLY);
	read(desc_zrod, &buf_3, sizeof(int));
	sprintf(buf_3s, "wynik: %d", buf_3);
	perror(buf_3s);

	desc_zrod = open("plik_2", O_RDONLY);
	read(desc_zrod, &buf_2, sizeof(int));
	sprintf(buf_2s, "wynik: %d", buf_2);
	perror(buf_2s);

	close(desc_zrod);
	int result = buf_5/(buf_2 * buf_3);
	sprintf(results, "ostateczny wynik: %d", result);
	perror(results);

	freopen("/dev/tty", "w", stdout);
	printf("wszystko wrocilo do normy!\n\n");
	return 0; 
	}

