/*
Chun-Wei Chen
CSE 351 - Spring 2013
Lab 4 - Mystery Caches

Mystery Cache Geometries:
mystery0:
    block size = 64 bytes
    cache size = 4 KB
    associativity = 32
mystery1:
    block size = 8 bytes
    cache size = 8 KB
    associativity = 8
mystery2:
    block size = 32 bytes
    cache size = 32 KB
    associativity = 2
mystery3:
    block size = 16 bytes
    cache size = 4 KB
    associativity = 1
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  int i = 0;
  int size = 0;
  access_cache(0);
  while (access_cache(i)) {
    size++;
    i++;
  }

  return size;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int size) {
  int i = 0;
  int cache_check = size;
  flush_cache();
  access_cache(0);
  while (access_cache(0)) {
    i = size;
    while (i <= cache_check) {
      i += size;
      access_cache(i);
    }
    cache_check += size;
  }

  return i;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int size) {
  int i = 0;
  int cache_check = 1;
  int assoc = 0;
  flush_cache();
  access_cache(0);
  while (access_cache(0)) {
    i = size;
    assoc = 0;
    while (i <= cache_check) {
      i += size;
      assoc++;
      access_cache(i);
    }
    cache_check += size;
  }

  return assoc;
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.
     You can test your geometry paramter discovery routines by
     calling cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
