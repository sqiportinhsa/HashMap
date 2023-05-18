#include <stdlib.h>

#include "bench.h"

const char *DATA_FILENAME = "../data/big.txt";

int main() {
    Input input = get_input(DATA_FILENAME);
    Pairs dict  = get_pairs(input);

    HashMap *hashmap = hashmap_create(crc32_hash, dict.pairs_amount);
    fill_hashmap(dict, hashmap);
    get_time(hashmap, dict);

    hashmap_dtor(hashmap);
    free(input.data);
    free(dict.pairs);
}