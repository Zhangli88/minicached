#ifndef __ST_OTHERS_H
#define __ST_OTHERS_H

#ifndef DEBUG
#define DEBUG
#endif

#ifdef __cplusplus 
extern "C" {
#endif //__cplusplus 

#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#include <linux/kernel.h>

typedef unsigned long ulong;
typedef unsigned int  uint;
typedef unsigned char uchar;
typedef unsigned short ushort;


#ifndef NULL
#ifdef __cplusplus 
#define NULL 0
#else
#define NULL ((void *)0)
#endif //__cplusplus 
#endif

/**
 * 统一一下函数的返回类型，不要自己都搞晕了 
 *  
 * 如果函数的返回值只是表示成功或者失败，就用下面的类型 
 */
typedef enum RET_TYPE {
    RET_YES = 1,
    RET_NO  = 0,
} RET_T;

#ifdef DEBUG

#define st_d_print(...) \
    do{ fprintf( stderr, "DEBUG:%s|%s<%d>:",__FILE__, __FUNCTION__,__LINE__); \
        fprintf( stderr, __VA_ARGS__ ); \
        fprintf( stderr, "\n"); fflush(stderr);\
    }while(0)
#else
#define st_d_print(...) \
    do {} while(0)
#endif

#define st_print(...)  \
    do{ fprintf( stderr , __VA_ARGS__ ); \
        fflush(stderr);\
    }while(0)

#define st_d_error(...) \
    do{ perror("ERROR:"); \
        fprintf( stderr, "ERROR:%s|%s<%d>:",__FILE__, __FUNCTION__,__LINE__); \
        fprintf( stderr, __VA_ARGS__ ); \
        fprintf( stderr, "\n"); fflush(stderr);\
    }while(0)

typedef struct _st_small_obj {
    char    data[4096];
    size_t  len;
} ST_SMALL_OBJ, *P_ST_SMALL_OBJ;

typedef struct _st_small_pobj {
    char*   data;
    size_t  len;
} ST_SMALL_POBJ, *P_ST_SMALL_POBJ;

#define WAIT_FOR_ENTER  fprintf( stderr, "Press ENTER\n" );getchar()


#define EXIT_IF_TRUE(x) if (x)                                  \
    do {                                                        \
            fprintf(stderr, "!!!%s:%d ASSERT '%s' IS TRUE\n",   \
            __FILE__, __LINE__, #x);                            \
            SYS_ABORT(#x);                                      \
    }while(0)  

#define RET_NULL_IF_TRUE(x) if (x)                              \
    do {                                                        \
            fprintf(stderr, "!!!%s:%d ASSERT '%s' IS TRUE\n",   \
            __FILE__, __LINE__, #x);                            \
            return NULL;                                        \
    }while(0)  

#define GOTO_IF_TRUE(x, flag) if (x)                            \
    do {                                                        \
            fprintf(stderr, "!!!%s:%d ASSERT '%s' IS TRUE\n",   \
            __FILE__, __LINE__, #x);                            \
            goto flag;                                          \
    }while(0) 

static inline void backtrace_info(int param)
{
    int j, nptrs;
#define BT_SIZE 100
    char **strings;
    void *buffer[BT_SIZE];

    nptrs = backtrace(buffer, BT_SIZE);
    fprintf(stderr, "backtrace() returned %d addresses\n", nptrs);

    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) 
    {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < nptrs; j++)
        fprintf(stderr, "%s\n", strings[j]);

    free(strings);

    exit(EXIT_FAILURE);
}

#define SYS_ABORT(...)  \
    do{ fprintf( stderr,"!!!DIE:%s|%s<%d>\n",__FILE__, __FUNCTION__,__LINE__); \
        fprintf( stderr , __VA_ARGS__ ); \
        backtrace_info(0); abort();    \
    }while(0)


#ifdef __cplusplus 
}
#endif //__cplusplus 

#endif  //__ST_OTHERS_H
