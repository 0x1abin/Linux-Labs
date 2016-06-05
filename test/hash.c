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
    
    printf("hash=%d\r\n",BKDRHash(argv[1]));

}