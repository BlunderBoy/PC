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


int main()
{
	char buffer[100];

	int fisier;
	fisier = open("a.txt", O_RDONLY);

    read(fisier, buffer, 5);
	

	for (int i = 0; i < strlen(buffer); ++i)
	{
		printf("%c\n", buffer[i]);
	}

}