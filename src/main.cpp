#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"
#include "hash.h"
#include "input.h"

int main() {
    HashMap *hashmap = hashmap_init(const_hash, 5);
    Input input = get_input("../data/small.txt");
    fill_hashmap(input, hashmap);
    printf("%s %s\n", hashmap_find(hashmap, "hello"), hashmap_find(hashmap, "world"));
    hashmap_dtor(hashmap);
    return 0;
}