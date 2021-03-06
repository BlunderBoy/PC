#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

void primesteMesaj(char nume[])
{
  strcat(nume, "Copie");
  msg primitInitial;
  int numarDePachete;
  if (recv_message(&primitInitial)<0){
    perror("[recv]nu am primit bine mesajul initial");
    
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
  int fisierPrimit = open (nume, O_WRONLY | O_CREAT, 0644);
  while (counter < numarDePachete)
  {
    counter++;
    msg primit;
    if (recv_message(&primit)<0){
      perror("nu am primit bine mesajul initial");
      
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
}

void trimiteAKC(int counter)
{
  msg AKC;
  sprintf(AKC.payload, "%d", counter);
  AKC.len = strlen(AKC.payload);
  send_message(&AKC);
  printf("[recv]am trimis AKC\n");
}

int main(int argc,char** argv){
  init(HOST,PORT);
  
  int numarFisiere = 0;
  msg preambool;
  if(recv_message(&preambool)<0)
  {
    perror("nu am primit bine\n");
    return -1;
  }
  
  numarFisiere = atoi(preambool.payload);
  printf("[recv]ma pregatesc sa primesc %d fisiere si trimit akc initial\n", atoi(preambool.payload));

  msg AKCintial;
  strcpy(AKCintial.payload, preambool.payload);
  AKCintial.len = preambool.len;
  send_message(&AKCintial);
  printf("[recv]am trimis AKC initial\n");

  for (int count = 0; count < numarFisiere; count++)
  {
    char nume[100];
    msg numeFisier;
    recv_message(&numeFisier);
    strcpy(nume, numeFisier.payload);
    printf("[recv]am primit numele fisierului trimit AKC\n");
    trimiteAKC(count);
    primesteMesaj(nume);
  }
  
  return 0;
}
