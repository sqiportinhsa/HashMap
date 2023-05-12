#ifndef HASHMAP_H
#define HASHMAP_H

#include "list.h"
#include "hash.h"

typedef hash_t (*hashfunc_t)(const char *key);

struct HashMap {
    hashfunc_t hashfunc = nullptr;
    List *array = nullptr;
    size_t array_size = 0;
    char *input = nullptr;
};

HashMap *hashmap_init  (hashfunc_t hashfunc, size_t array_size);
void     hashmap_insert(HashMap *hashmap,  char *key, char *value);
char    *hashmap_find  (HashMap *hashmap,  const char *key);
void     hashmap_dtor  (HashMap *hashmap);

#endif