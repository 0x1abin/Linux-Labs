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

uint32_t aaa = 1;
uint8_t bbb = 2;
uint8_t hahha;
bit a = 0;

int main(int argc, char **argv)
{
    printf("argc=%d\r\n",argc);
    printf("%s  ",argv[0]);
    printf("%s  ",argv[1]);
    printf("%s  ",argv[2]);
    printf("%s  ",argv[3]);
    printf("\r\n");
    
    fa_ptint();
    fb_ptint();
}