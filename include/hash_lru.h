#ifndef __HASH_LRU_H_
#define __HASH_LRU_H_

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "minicached.h"

#ifdef __cplusplus 
extern "C" {
#endif //__cplusplus 

#include "slabs.h"

#ifndef SLAB_SZ_TYPE
#define SLAB_SZ_TYPE (SZ_1M + 1)
#endif


uint32_t jenkins_hash(const void *key, size_t length);
uint32_t MurmurHash3_x86_32(const void *key, size_t length);

typedef uint32_t (*hash_func)(const void *key, size_t length);
extern hash_func hash;

#define HASH_POWER 10
#define hashsize(n) ((unsigned long int)1<<(n))
#define hashmask(n) (hashsize(n)-1)

extern RET_T mnc_hash_init();

mnc_item* hash_find(const void* key, const size_t nkey);


RET_T mnc_hash_insert(mnc_item *it);
RET_T mnc_hash_delete(mnc_item *it);


// LRU related item
RET_T mnc_lru_init(void);
RET_T mnc_lru_insert(mnc_item *it);
RET_T mnc_lru_delete(mnc_item *it);

#ifdef __cplusplus 
}
#endif //__cplusplus 


#endif //__HASH_LRU_H_