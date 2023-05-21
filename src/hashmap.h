#ifndef HASHMAP_H
#define HASHMAP_H

#include "list.h"
#include "hash.h"

struct HashMap {
    hashfunc_t hashfunc = nullptr;
    List         *array = nullptr;
    size_t        array_size  = 0;
};

HashMap    *hashmap_create  (hashfunc_t hashfunc, size_t array_size);
void        hashmap_insert(HashMap *hashmap, const char *key, const char *value);
const char *hashmap_find  (HashMap *hashmap, const char *key);
void        hashmap_dtor  (HashMap *hashmap);

#endif