#include "uv.h"

uv_loop_t loop;

int uv_loop_init() 
{
  // int err;

//  memset(&loop, 0, sizeof(loop));

	loop.timer = NULL;
	loop.timer_counter = 0;
	loop.time_base = 0;

  return 0;
}

void uv__update_time()
{
  static uint16_t count;
  
//  if(++count >= 100)
  {
    count = 0;
	  loop.time_base++;
	  usleep(1000);
  }

}

int uv_run() {
	
  while (1) {
    uv__update_time();
    uv__run_timers();
//    uv__run_idle(loop);
//    uv__run_prepare(loop);
  }
}
