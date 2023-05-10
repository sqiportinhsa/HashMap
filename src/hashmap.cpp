#include <stdlib.h>

#include "hashmap.h"

static void init_lists(List *array, size_t size);
static void free_lists(List *array, size_t size);

HashMap *hashmap_init(hash_t (*hashfunc)(const char *key), size_t array_size) {
    HashMap *map = (HashMap*) calloc(1, sizeof(HashMap));
    if (!map) return nullptr;

    map->hashfunc   = hashfunc;
    map->array_size = array_size;

    map->array = (List*) calloc(array_size, sizeof(List));
    if (!map->array) {
        free(map);
        return nullptr;
    }

    init_lists(map->array, array_size);

    return map;
}

void hashmap_insert(HashMap *hashmap, char *key, char *value) {
    hash_t hash = hashmap->hashfunc(key) % hashmap->array_size;
    list_insert(hashmap->array + hash, key, value);
}

char *hashmap_find(HashMap *hashmap, const char *key) {
    hash_t hash = hashmap->hashfunc(key) % hashmap->array_size;
    return list_find(hashmap->array + hash, key);
}

void hashmap_dtor(HashMap *hashmap) {
    free_lists(hashmap->array, hashmap->array_size);
    free(hashmap->array);
    free(hashmap->input);
    free(hashmap);
}

static void init_lists(List *array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        list_init(array + i);
    }
}

static void free_lists(List *array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        list_dtor(array + i);
    }
}