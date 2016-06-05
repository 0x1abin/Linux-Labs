#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "fa.h"
#include "fb.h"
//#include "typedef.h"

uint8_t arry[2][3] = {{1, 2, 3}, {4, 5, 6}};
uint8_t (*prt)[3];
uint8_t (*abc)(void);


unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131;
    unsigned int hash = 0;
     
    while (*str)
    {
      hash = hash * seed + (*str++);
    }
    
    return (hash & 0xff);
    //return (hash &amp; 0x7FFFFFFF);
}

int main(int argc, char **argv)
{
//    prt = arry;
    
//    printf("%d, %d, %d \r\n", prt[0][0], prt[0][1], prt[1][2]);
//    printf("size:%ld \r\n", sizeof(abc));
    
    printf("hash=%d\r\n",BKDRHash(argv[1]));


}