#include "list.h"

struct HashMap {
    int (*hashfunc)(char *key);
    List *array = nullptr;
    size_t array_size = 0;
    char *input = nullptr;
};

HashMap *hashmap_init(int (*hashfunc)(char *key), size_t array_size);
void     hashmap_insert(HashMap *hashmap, char *key, char *value);
char    *hashmap_find  (HashMap *hashmap, char *key);
void     hashmap_dtor  (HashMap *hashmap);