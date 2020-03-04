#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001


int main(void)
{
	printf("[RECEIVER] Starting.\n");	
	init(HOST, PORT);

	msg r;
	
	int counter = 0;
	for (i = 0; i < COUNT; i++) {
		/* wait for message */

		res = recv_message(&r);
		
		if (res < 0) {
			perror("[RECEIVER] Receive error. Exiting.\n");
			return -1;
		}
		counter++;

		/* send dummy ACK */
		res = send_message(&r);
		if (res < 0) {
			perror("[RECEIVER] Send ACK error. Exiting.\n");
			return -1;
		}
		printf("[RECIEVER] se trimite AKC cu numarul %d\n",counter);
	}

	printf("[RECEIVER] Finished receiving..\n");
	return 0;
}
