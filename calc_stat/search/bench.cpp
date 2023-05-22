#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bench.h"

const size_t HASHMAP_SIZE = 4013; 
const double CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;
const size_t REPEAT_TIMES = 100;

void get_time(HashMap *hashmap, Pairs *pairs) {
    volatile const char *found = nullptr;

    clock_t begin = clock();
    for (size_t t = 0; t < REPEAT_TIMES; ++t) {
        for (size_t i = 0; i < pairs->pairs_amount; ++i) {
            found = hashmap_find(hashmap, pairs->pairs[i].key);
        }
    }
    clock_t end = clock();

    printf("%f", (end-begin) / CLOCKS_PER_MS);
}
