#include <stdio.h>
#include <stdlib.h>


const char a[] = {0x1a, 0x2a, 0x3a, 45, 0x11, 0};

void ptx(const char *buf)
{
    printf("%s\r\n", buf);
    printf("size:%d.\r\n", strlen(buf));
}

int main()
{
    ptx(a);
}