#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

void resetCursor(int fisier)
{
  lseek(fisier, 0, SEEK_SET);
}

int getLungimeFisier(int fisier)
{
  char buferas[1];
  int lungime = 0;
  while(read(fisier, buferas, 1))
  {
    lungime++;
  }
  resetCursor(fisier);

  return lungime;
}

int verificareLungime(int lungimeFisier)
{
  return (lungimeFisier < MAX_LEN) ? lungimeFisier : MAX_LEN;
}

msg creareMesaj(char buffer[], int lungime)
{
  msg mesaj;
  memcpy(mesaj.payload, buffer, lungime);
  mesaj.len = lungime;
  return mesaj;
}

void trimiteFisier(int fisierDeTransmis)
{
  int fileLength = getLungimeFisier(fisierDeTransmis);
  int numarDePachete = fileLength/MAX_LEN + 1;
  printf("------se vor transmite %d pachete\n", numarDePachete);

  msg initial;
  sprintf(initial.payload, "%d", numarDePachete);
  initial.len = strlen(initial.payload);
  send_message(&initial);
  printf("[send]am trimis mesajul initial cu numarul de pachete\n");

  msg primulAKC;
  if (recv_message(&primulAKC) < 0)
  {
    perror("nu am primit bine primul akc");
    
  }
  else
  {
    printf("[send]am primit primul AKC, incep sa trimit mesajele\n");
    printf("--------------\n");
  }
  

  char buffer[MAX_LEN];
  int catTrebuieCitit = verificareLungime(fileLength);
  int counter = 0;
  while (counter != numarDePachete)
  {
    counter++;
    read(fisierDeTransmis, buffer, catTrebuieCitit); //citesc din fisier
    msg mesajDeTrimis = creareMesaj(buffer, catTrebuieCitit); //creare mesaj

    fileLength -= catTrebuieCitit; //actualizez lungimea fisierului
    catTrebuieCitit = verificareLungime(fileLength); //actualizez cat trebuie sa citesc

    send_message(&mesajDeTrimis);
    printf("[send]se transmite pachetul %d/%d. se asteapta raspunsul.\n", counter, numarDePachete);

    msg AKC;
    if (recv_message(&AKC)<0){
      perror("[send]nu am primit mesajul!");
      
    }
    else
    {
      printf("[send]am primit mesajul AKC%s\n", AKC.payload);
      printf("------------------------------------------\n");
      if(atoi(AKC.payload) != counter)
      {
        perror("[send] am primit un AKC prost\n");
        
      }
    }
  }
  
  close(fisierDeTransmis);
  
}

int main(int argc,char** argv){
  init(HOST,PORT);

  int cateFisiereSunt = 3;
  char fisiere[100][100];

  strcpy(fisiere[0], "send.txt");
  strcpy(fisiere[1], "send2.txt");
  strcpy(fisiere[2], "send3.txt");
  
  msg preambul;
  sprintf(preambul.payload, "%d", cateFisiereSunt);
  preambul.len = strlen(preambul.payload);
  printf("[send]stabilesc conexiunea initiala si trimit numarul de fisiere...astept akc initial\n");
  send_message(&preambul);

  msg AKCinitial;
  recv_message(&AKCinitial);
  printf("[send]am primit AKC initial incep sa trimit fisere\n");

  for (int counter = 0; counter < cateFisiereSunt; counter++)
  {
    msg numeFisier;
    strcpy(numeFisier.payload, fisiere[counter]);
    numeFisier.len = strlen(numeFisier.payload);
    send_message(&numeFisier);
    printf("[send]trimit mesaj cu numele fisierului astept AKC\n");
    msg AKC;
    recv_message(&AKC);
    printf("[send]am primit AKC trimit fisierul\n");

    int fisier = open(numeFisier.payload, O_RDONLY);
    trimiteFisier(fisier);
  }
  
  return 0;
}
