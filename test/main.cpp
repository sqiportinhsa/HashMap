#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "../src/hash.h"

const char *DATA_FILENAME = "../data/big.txt";

int main() {
    Input input = get_input(DATA_FILENAME);
    Pairs pairs = get_pairs(input);
    qsort(pairs.pairs, pairs.pairs_amount, sizeof(Pair), comparator);
    check_hashmap(crc32_hash, pairs);
    //check_hashmap(const_hash,      input);
    //check_hashmap(first_char_hash, input);
    //check_hashmap(char_sum_hash,   input);
    //check_hashmap(ror_hash,        input);
    //check_hashmap(rol_hash,        input);
    //check_hashmap(gnu_hash,        input);
    free(input.data);
    free(pairs.pairs);
    return 0;
}