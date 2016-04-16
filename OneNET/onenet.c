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
#include <wiringPi.h>

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

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;

char *out;

char jsonBuf[200];

int create_json(char *jbuf, int val_1, int val_2)
{
	cJSON *root,*fmt,*img,*thm,*fld,*kld;
	cJSON *datastreams_arr;
	cJSON *dtms_oj1, *dtms_oj1_arr, *dtms_oj1_arr_val;
	cJSON *dtms_oj2, *dtms_oj2_arr, *dtms_oj2_arr_val;
//	cJSON *dtms_oj2, *dtms_oj3;
	int lenth;
	char *jout;
	int i;

	root=cJSON_CreateObject();
	cJSON_AddItemToObject(root, "datastreams", datastreams_arr=cJSON_CreateArray());
	cJSON_AddItemToArray(datastreams_arr, dtms_oj1=cJSON_CreateObject());
	cJSON_AddItemToArray(datastreams_arr, dtms_oj2=cJSON_CreateObject());
	
	cJSON_AddStringToObject(dtms_oj1,"id","温度");
	cJSON_AddItemToObject(dtms_oj1,"datapoints",dtms_oj1_arr = cJSON_CreateArray());
	cJSON_AddItemToArray(dtms_oj1_arr, dtms_oj1_arr_val=cJSON_CreateObject());
	cJSON_AddNumberToObject(dtms_oj1_arr_val,"value",val_1);
	
	cJSON_AddStringToObject(dtms_oj2,"id","湿度");
	cJSON_AddItemToObject(dtms_oj2,"datapoints",dtms_oj2_arr = cJSON_CreateArray());
	cJSON_AddItemToArray(dtms_oj2_arr, dtms_oj2_arr_val=cJSON_CreateObject());
	cJSON_AddNumberToObject(dtms_oj2_arr_val,"value",val_2);
	

	jout = cJSON_PrintUnformatted(root);
//	out=cJSON_Print(root);
	lenth = strlen(jout);
	
	memcpy(jbuf, jout, lenth);
	
	cJSON_Delete(root);
	free(jout);
	
	return lenth;
}


int http_post(char *postData, int n)
{
	#define URLADDR "api.heclouds.com"
	#define PORT 80
	#define BUFSIZE 1024
	
	int sockfd, ret, i, h;
	char str1[512], recvbuf[BUFSIZE], ipstr[16];
    struct sockaddr_in servaddr;
	struct hostent *answer;
	
	char jsonLensStr;
    
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
		printf("解析域名：%s....\n", answer->h_name);
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
    printf("服务器连接成功！\r\n\r\n");
	printf("================Send Http Header:================\n");

    //准备发送数据
    memset(str1, 0, 4096);
    strcat(str1, "POST /devices/157219/datapoints HTTP/1.1\r\n");
    strcat(str1, "Host:api.heclouds.com\r\n");
	strcat(str1, "api-key:NPTqEwe3ZjP8styXh0gKaN6IgpsA\r\n");
	strcat(str1, "Content-Type:application/json\r\n");
	strcat(str1, "content-length:");
	
	sprintf(&jsonLensStr, "%d", n);
	strcat(str1, &jsonLensStr);
	strcat(str1, "\r\n\r\n");
	
	strncat(str1, postData, n);
	strcat(str1, "\r\n");
	
	
    printf("%s\r\n",str1);//显示发送数据
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
//	memset(recvbuf, 0, BUFSIZE);
//    i = read(sockfd, recvbuf, BUFSIZE);
//    recvbuf[i] = '\0';
//    printf("================Receive Message:================\r\n%s\r\n",recvbuf);

    close(sockfd);// 关闭套接字
}


#define HIGH_TIME 32

int pinNumber =1; //use gpio1 to read data

uint8 readSensorData(int *tmp, int *rh)
{
	uint32 databuf;
	uint8 crc;
	uint8 i;

	pinMode(pinNumber,OUTPUT); // set mode to output
	digitalWrite(pinNumber, 1); // output a high level
	delay(3000);

	pinMode(pinNumber,OUTPUT); // set mode to output
	digitalWrite(pinNumber, 0); // output a high level
	delay(25);
	digitalWrite(pinNumber, 1); // output a low level
	pinMode(pinNumber, INPUT); // set mode to input
	pullUpDnControl(pinNumber,PUD_UP);

	delayMicroseconds(27);
	if(digitalRead(pinNumber)==0) //SENSOR ANS
	{
		while(!digitalRead(pinNumber)); //wait to high

		for(i=0; i<32; i++)
		{
			while(digitalRead(pinNumber)); //data clock start
			while(!digitalRead(pinNumber)); //data start
			delayMicroseconds(HIGH_TIME);
			databuf*=2;
			if(digitalRead(pinNumber)==1) //1

			{
				databuf++;
			}
		}

		for(i=0; i<8; i++)
		{
			while(digitalRead(pinNumber)); //data clock start
			while(!digitalRead(pinNumber)); //data start
			delayMicroseconds(HIGH_TIME);
			crc*=2;
			if(digitalRead(pinNumber)==1) //1
			{
				crc++;
			}
		}
		
		*tmp = (databuf>>8)&0xff;
		*rh  = (databuf>>24)&0xff;
		
		if(*tmp > 40)
			return 0;
		else
			return 1;
	}
	else
	{
		return 0;
	}
}

int Init_DHT11()
{
	printf("Use GPIO1 to read data!\n");

	if (-1 == wiringPiSetup())
	{
		printf("Setup wiringPi failed!");
		return 1;
	}

	pinMode(pinNumber, OUTPUT); // set mode to output
	digitalWrite(pinNumber, 1); // output a high level
	printf("Init_DHT11_Over!\n");
}

int main()
{
	size_t lenths;
	int temperature, humidity, res;

    //srandom(66);
    Init_DHT11();
	
	while(1)
	{
		res = readSensorData(&temperature, &humidity);
		
		printf("temperature:%d. humidity:%d \r\n", temperature, humidity);
		
		if(res == 1)
		{
		    lenths = create_json(jsonBuf, temperature, humidity);
		    
		    http_post(jsonBuf, lenths);
		}
		    
	    sleep(1);
	}
	
}
