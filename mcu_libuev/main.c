#include "stdio.h"
#include "uv.h"
#include <sys/wait.h>
#include <sys/time.h>

uv_loop_t* xloop;

uv_timer_t timer1;
uv_timer_t timer2;
uv_timer_t timer3;
uv_timer_t timer4;


void time1_func(uv_timer_t* handle)
{
	static uint16_t count;
	
	printf("timer1.count:%d\r\n", count++);
}

void time2_func(uv_timer_t* handle)
{
	static uint16_t count;
	
	printf("timer2.count:%d\r\n\r\n", count++);
} 

void time3_func(uv_timer_t* handle)
{
	static uint16_t count;
	
	printf("timer3.count:%d\r\n", count++);
}

void time4_func(uv_timer_t* handle)
{
	static uint16_t count;
	
	printf("timer4.count:%d\r\n", count++);
}


int main(int argc, char **argv)
{
    printf("libuev..\r\n");
    
    xloop = uv_default_loop();
//    uv_loop_init(&xloop);
    
	uv_timer_init(xloop, &timer1);
	uv_timer_start(&timer1, time1_func, 132, 645);
	
	uv_timer_init(xloop, &timer2);
	uv_timer_start(&timer2, time2_func, 0, 751);
	
 	uv_timer_init(xloop, &timer3);
 	uv_timer_start(&timer3, time3_func, 0, 5000);
	
 	uv_timer_init(xloop, &timer4);
 	uv_timer_start(&timer4, time4_func, 5000, 0);

    uv_run(xloop);

}