#include <stdio.h>
#include <unistd.h> /* pentru open(), exit() */
#include <fcntl.h> /* O_RDWR */
#include <errno.h> /* perror() */
#include <stdlib.h>
#include <string.h>
 
void fatal(char * mesaj_eroare)
{
    perror(mesaj_eroare);
    exit(1);
}


int main(int argc, char *argv[])
{

	if(argc != 2)
	{
		fatal("foloseste cu un fisier");
	}

	char buffer[2];

	int fisier;
	fisier = open("a.txt", O_RDONLY); //deschid fisierul

    while(read(fisier, buffer, 1))
	{
		printf("%c", buffer[0]);
	}
}