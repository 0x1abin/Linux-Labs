#include <stdio.h>
#include <linux/kernel.h>
#include <sys/types.h>
#include "list.h"
//#include <linux/jiffies.h>


// #define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
// #define container_of(ptr, type, member) ({                      \
//         const typeof ( ((type *)0)->member ) *__mptr = (ptr);    \
//         (type *)( ( char *)__mptr - offsetof(type,member) );})


// #define my_container_of(ptr, type, member) ({                      \
//           (type *)( (const char *)ptr - offsetof(type,member) );})

// struct list_head {
//     struct list_head *next;
//     struct list_head *prev;
// };


struct fox{
    char a;
    char b;
    char c;
    
    struct list_head list;
//    struct fox *prev;
//    struct fox *next;
};

struct fox s1 ,s2, s3, s4;
struct fox *ps1, *ps2, *ps3;

int main( int argc, char *argv[])
{
//    s1.list.next = &s2.list;
//    s2.list.next = &s3.list;
    
//    s2.list.prev = &s1.list;
//    s3.list.prev = &s2.list;

    INIT_LIST_HEAD(&(s1.list));
    list_add(&(s2.list), &(s1.list));
    list_add(&(s3.list), &(s2.list));
    
//    list_del(&(s2.list));
    
    list_replace(&(s2.list), &(s4.list));
    
    s1.a = 11;
    s2.a = 21;
    s3.a = 31;
    s4.a = 41;
    
//    printf("s1.a = %p \r\ns2.a = %p  \r\n", &s1, container_of(&(s1.b), struct fox, b));
    
    printf("s1:%p, s2:%p, s3:%p \r\n", &(s1.list), &(s1.list.next->next), &(s1.list.next->next->next));
    
    printf("s1:%d, s2:%d, s3:%d \r\n", \
    (container_of(&(s1.list), struct fox, list))->a, \
    (container_of((s1.list.next), struct fox, list))->a, \
    (container_of((s1.list.next->next), struct fox, list))->a);
    

    
//    p_c = &a_obj. c ;
//    p_a = container_of(p_c, struct a, c);
//    printf ("a_obj addr:%x\na_obj addr obtained by container_of: %x\n", ( unsigned int )&a_obj, ( unsigned int )p_a);
    
    return 0;
}
