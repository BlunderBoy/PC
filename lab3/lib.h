#ifndef LIB
#define LIB

#define LUNGIMECADRU 1400
#define COUNT	100

typedef struct {
  int len;
  char payload[LUNGIMECADRU];
  char checksume[100];
} msg;

//returneaza matrice de checksums
inline char checksumi(char *mesaj, int bit)
{
    //verific 8 biti
    char checksum = 0;
    int catiBitiVerific = 8;
    char const1 = 1 << bit;
    for (int i = 0; i < catiBitiVerific; i++)
    {
       char caracter = *(mesaj + i);
       checksum ^= caracter & const1;
    }
    return checksum;
}
inline char* checksum(char mesaj[], int lungimeMesaj)
{
    char checksum[100];
    int counter = 0;
    for (int i = 0; i < lungimeMesaj; i+=8)
    {
      for(int j = 0; j < 8; j++)
      {
          checksum[counter] |= checksumi(mesaj + i, i/8);
          checksum[counter] <<= 1;
      }
      counter++;
    }
    return checksum;
}
void init(char* remote,int remote_port);
void set_local_port(int port);
void set_remote(char* ip, int port);
int send_message(const msg* m);
int recv_message(msg* r);

#endif

