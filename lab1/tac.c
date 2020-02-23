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

	char *buffer;
	buffer = (char*)malloc(20*sizeof(char));
	if (buffer == NULL)
	{
		fatal("eroare la alocarea dinamica");	
	}

	int fisier;
	fisier = open("a.txt", O_RDONLY); //deschid fisierul

	int index = 0;
	int counter = 0;
	char matrice[30][30];

    while(read(fisier, buffer, 1))
	{
		matrice[counter][index] = buffer[0];
		index++;
		if(buffer[0] == '\n')
		{
			matrice[counter][index] = '\0';
			counter++;
			index = 0;
		}

	}


	for (int i = 0; i < counter; ++i)
	{
		for (int j = 0; j < strlen(matrice[i]); ++j)
		{
			printf("%c", matrice[i][j]);
		}
	
	}

	printf("-----------------------------\n");

	for (int i = counter - 1; i >= 0; --i)
	{
		printf("%s", matrice[i]);
	}
}