#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"
#include "hash.h"
#include "input.h"

const char *INPUT_FILENAME = "../data/big_processed.txt";
const size_t HASHMAP_SIZE = 16127;

int main() {
    HashMap *hashmap = hashmap_create(gnu_hash, HASHMAP_SIZE);
    Input input = get_input(INPUT_FILENAME);
    Pairs dict  = get_pairs(input);
    fill_hashmap(dict, hashmap);
    printf("%s %s!\n", hashmap_find(hashmap, "hello"), hashmap_find(hashmap, "world"));
    hashmap_dtor(hashmap);
    free(input.data);
    return 0;
}