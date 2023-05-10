#ifndef HASHMAP_H
#define HASHMAP_H

#include "list.h"
#include "hash.h"

struct HashMap {
    hash_t (*hashfunc)(const char *key);
    List *array = nullptr;
    size_t array_size = 0;
    char *input = nullptr;
};

HashMap *hashmap_init  (hash_t (*hashfunc)(const char *key), size_t array_size);
void     hashmap_insert(HashMap *hashmap,  char *key, char *value);
char    *hashmap_find  (HashMap *hashmap,  const char *key);
void     hashmap_dtor  (HashMap *hashmap);

#endif