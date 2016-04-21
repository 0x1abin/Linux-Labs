/*
  Copyright (c) 2009 Dave Gamble
 
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
 
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
 
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

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

char *out;

void create_objects()
{
	cJSON *root,*fmt,*img,*thm,*fld,*kld;
	cJSON *datastreams_arr;
	cJSON *dtms_oj1, *dtms_oj1_arr, *dtms_oj1_arr_val;
//	cJSON *dtms_oj2, *dtms_oj3;
	
//	char *out;
	int i;	/* declare a few. */

	root=cJSON_CreateObject();
	cJSON_AddItemToObject(root, "datastreams", datastreams_arr=cJSON_CreateArray());
	cJSON_AddItemToArray(datastreams_arr, dtms_oj1=cJSON_CreateObject());
	cJSON_AddStringToObject(dtms_oj1,"id","testID1");

	cJSON_AddItemToObject(dtms_oj1,"datapoints",dtms_oj1_arr = cJSON_CreateArray());
	cJSON_AddItemToArray(dtms_oj1_arr, dtms_oj1_arr_val=cJSON_CreateObject());
	cJSON_AddNumberToObject(dtms_oj1_arr_val,"value",23);

	out=cJSON_PrintUnformatted(root);
//	out=cJSON_Print(root);
	
//	pOut = out;
	cJSON_Delete(root);
//	printf("%s\n",out);
//	free(out);

}

int __main (int argc, const char * argv[]) {

	/* Now some samplecode for building objects concisely: */
	create_objects();
	
	return 0;
}


//#define IPSTR "115.29.230.113"
#define URLADDR "api.yeelink.net"
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
	
/*	
	POST /devices/157219/datapoints HTTP/1.1
	Host: api.heclouds.com
	api-key: NPTqEwe3ZjP8styXh0gKaN6IgpsA
	Content-Type: application/json
*/	


    //准备发送数据
    memset(str1, 0, 4096);
    strcat(str1, "POST /v1.1/device/18607/sensor/32317/datapoints HTTP/1.1\r\n");
    strcat(str1, "Host:api.yeelink.net\r\n");
	strcat(str1, "U-ApiKey:e92dea44e2c4b29838fea13b9cf7ab59\r\n");
	strcat(str1, "\r\n");
//	create_objects();
//	strcat(str1, out);
	
//	{"datastreams":[{"id":"testID1","datapoints":[{"value":122}]}]}
	strcat(str1, "{\"value\":333}");
//	strcat(str1,"{\"datastreams\":[{\"id\":\"testID1\",\"datapoints\":[{\"value\":11}]},{\"id\":\"testID2\",\"datapoints\":[{\"value\":22}]},{\"id\":\"testID3\",\"datapoints\":[{\"value\":33}]}]}");
	strcat(str1, "\r\n\r\n");

    printf("%s",str1);//显示发送数据
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
