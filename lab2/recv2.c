#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001


int main(int argc,char** argv){
  msg primitInitial;
  int numarDePachete;
  init(HOST,PORT);
  if (recv_message(&primitInitial)<0){
    perror("[recv]nu am primit bine mesajul initial");
    return -1;
  }
  else
  {
    numarDePachete = atoi(primitInitial.payload);
    printf("[recv]am primit mesajul initial si astept %d pachete\n", numarDePachete);
    
    printf("[recv]trimit AKC initial\n");
    msg ACKinitial;
    sprintf(ACKinitial.payload, "%d", 1100);
    ACKinitial.len = strlen(ACKinitial.payload);
    send_message(&ACKinitial);
  }

  int counter = 0;
  int fisierPrimit = open ("primit.txt", O_WRONLY | O_CREAT, 0644);
  while (counter < numarDePachete)
  {
    counter++;
    msg primit;
    if (recv_message(&primit)<0){
      perror("nu am primit bine mesajul initial");
      return -1;
    }
    else
    {
      printf("[recv]am primit mesajul %d, trimit AKC%d\n", counter, counter);
      write(fisierPrimit, primit.payload, primit.len);
      printf("[recv]pachetul are lungimea: %d\n", primit.len);

      msg AKC;
      sprintf(AKC.payload, "%d", counter);
      AKC.len = strlen(AKC.payload);
      send_message(&AKC);
    }
    
  }
  close(fisierPrimit);
  return 0;
}
