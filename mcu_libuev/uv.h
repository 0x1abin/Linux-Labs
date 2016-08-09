#ifndef UV_H
#define UV_H

#include "typedef.h"
#include <string.h>
//#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include "list.h"


#define EINVAL      0x86

# define UV__HANDLE_INTERNAL  0x80
# define UV__HANDLE_ACTIVE    0x40
# define UV__HANDLE_REF       0x20
# define UV__HANDLE_CLOSING   0x01


/* Handle types. */
typedef struct uv_loop_s        uv_loop_t;
typedef struct uv_handle_s      uv_handle_t;
typedef struct uv_stream_s      uv_stream_t;
typedef struct uv_tcp_s         uv_tcp_t;
typedef struct uv_udp_s         uv_udp_t;
typedef struct uv_pipe_s        uv_pipe_t;
typedef struct uv_tty_s         uv_tty_t;
typedef struct uv_poll_s        uv_poll_t;
typedef struct uv_timer_s       uv_timer_t;
typedef struct uv_prepare_s     uv_prepare_t;
typedef struct uv_check_s       uv_check_t;
typedef struct uv_idle_s        uv_idle_t;
typedef struct uv_async_s       uv_async_t;
typedef struct uv_process_s     uv_process_t;
typedef struct uv_fs_event_s    uv_fs_event_t;
typedef struct uv_fs_poll_s     uv_fs_poll_t;
typedef struct uv_signal_s      uv_signal_t;


typedef void (*uv_timer_cb)(uv_timer_t* handle);

extern uv_loop_t loop;

struct uv_loop_s {
    uint8_t     flags;        
    
    uv_timer_t *timer;
    uint8_t     timer_counter;
    uint32_t    time_base;
};


struct uv_timer_s {
    /* public */                                                                
    void*    data;
    uint8_t  flags;
    
    //UV_TIMER_PRIVATE_FIELDS
    uv_timer_cb timer_cb;
    
    uint32_t timeout;
    uint32_t repeat;
    uint8_t start_id;
    
    struct list_head list;
    
    uv_timer_t *prev;
    uv_timer_t *next;
};


int uv_loop_init(void);
int uv_run(void);

void uv__update_time(void);

void uv_timer_init(uv_timer_t* handle);
int uv_timer_start(uv_timer_t* handle, uv_timer_cb cb, uint32_t timeout, uint32_t repeat);
int uv_timer_stop(uv_timer_t* handle);
int uv_timer_again(uv_timer_t* handle);
void uv_timer_set_repeat(uv_timer_t* handle, uint32_t repeat);
uint32_t uv_timer_get_repeat(const uv_timer_t* handle);
void uv__run_timers(void);
void uv__timer_close(uv_timer_t* handle);


#endif /* UV_H */
