#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"
#include "hash.h"
#include "input.h"

const char *INPUT_FILENAME = "../data/big2.txt";
const size_t HASHMAP_SIZE = 16127;

int main() {
    HashMap *hashmap = hashmap_create(const_hash, HASHMAP_SIZE);
    Input input = get_input(INPUT_FILENAME);
    fill_hashmap(input, hashmap);
    printf("%s %s!\n", hashmap_find(hashmap, "Hello"), hashmap_find(hashmap, "World"));
    hashmap_dtor(hashmap);
    free(input.data);
    return 0;
}