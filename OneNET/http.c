#include <stdio.h>
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

//#define IPSTR "115.29.230.113"
#define URLADDR "api.ikair.com"
#define PORT 80
#define BUFSIZE 4096

int main()
{
    int sockfd, ret, i, h;
	char str1[4096], recvbuf[BUFSIZE], ipstr[16];
    struct sockaddr_in servaddr;
	struct hostent *answer;
    
	//DNS地址解析
	answer = gethostbyname(URLADDR);
	if (answer == NULL)
	{
		herror("gethostbyname"); //由gethostbyname自带的错误处理函数
		exit(1);
	}
	for (i = 0; (answer->h_addr_list)[i] != NULL; i++)
	{
		inet_ntop(AF_INET, (answer->h_addr_list)[i], ipstr, 16);
		printf("%s\n", answer->h_name);
		printf("地址解析成功: %s\n", ipstr);
	}
	
	//创建套接字
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ipstr);
    servaddr.sin_port = htons(PORT);
    if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))
    {
        printf("连接失败！");
        exit(0);
    }
    printf("服务器连接成功！\n\n");
	printf("================Send Http Header:===============\n");
	
    //准备发送数据
    memset(str1, 0, 4096);
    strcat(str1, "GET /v1.0/Devices/2/Sensors/5 HTTP/1.1\n");
    strcat(str1, "Host: api.ikair.com\n");
	strcat(str1, "token: 57cfdf7972776aca\n");
	strcat(str1, "clientid: e064ea6dafa8cb0a\n");
	strcat(str1, "\n");

    printf("%s\n",str1);//显示发送数据
	printf("------------------------------------------------\n");

	ret = write(sockfd,str1,strlen(str1));
    if (ret < 0) 
	{
		printf("发送失败！错误代码是%d，错误信息是'%s'\n",errno, strerror(errno));
		exit(0);
    }
	else
	{
		printf("消息发送成功，共发送了%d个字节！\n\n", ret);
    }

	// 第五步 接收HTTP响应
	memset(recvbuf, 0, BUFSIZE);
    i = read(sockfd, recvbuf, BUFSIZE);
    recvbuf[i] = '\0';
    printf("================Receive Message:================\r\n%s\r\n",recvbuf);

    close(sockfd);// 关闭套接字
	getchar();
}
