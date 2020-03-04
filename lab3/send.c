#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10000
#define BANDWITH 10
#define DELAY 10

int main(int argc, char *argv[])
{
	
	printf("[SENDER] Starting.\n");	
	init(HOST, PORT);

	int ariaWindow = (BANDWITH * DELAY * 1000) / (sizeof(msg) * 8);
	printf("[SENDER] se trimit %d pachete in window\n", ariaWindow);

	char mesaj[] = "salut acesta este un mesaj!\n";
	
	msg mesajDeTrimis;
	memset(&mesajDeTrimis.payload, 0, sizeof(mesaj));
	mesajDeTrimis.len = sizeof(mesaj);

	int counter = 0;

	for (int i = 0; i < ariaWindow; i++)
	{
		counter++;
		printf("[SENDER] se trimite pachetul cu numarul %d\n",counter);
		send_message(&mesajDeTrimis);
	}

	msg dePrimit;

	for (int i = 0; i < COUNT - ariaWindow; i++)
	{
		recv_message(&dePrimit);
		send_message(&mesajDeTrimis);
		counter++;
		printf("[SENDER] se trimite pachetul cu numarul %d\n",counter);
	}
	
	for (int i = 0; i < ariaWindow; i++)
	{
		recv_message(&dePrimit);
	}

	printf("[SENDER] Job done, all sent.\n");
		
	return 0;
}
