#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hash.h"

const size_t HASHMAP_SIZE = 4013; 
const double CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;
const size_t REPEAT_TIMES = 100;

static double get_time(hashfunc_t hashfunc, Pairs pairs);

static void get_and_report_distribution(hashfunc_t hashfunc, Pairs dict, const char *hashfunc_name);
static void print_distribution(const char *hashfunc_name, size_t *sizes, HashMap *hashmap);
static void            get_distribution(List *lists,               size_t *sizes);


void get_times(double *times, Pairs dict) {
    for (size_t i = 0;  i < HASHFUNCS_SIZE; ++i) {
        times[i] = get_time(HASHFUNCS[i], dict);
    }
}

void print_times(double *times) {
    for (size_t i = 0; i < HASHFUNCS_SIZE; ++i) {
        printf("%s,%lf\n", HASHFUNC_NAMES[i], times[i]);
    }
}

void get_and_report_all_distributions(Pairs dict) {
    for (size_t i = 0; i < HASHFUNCS_SIZE; ++i) {
        get_and_report_distribution(HASHFUNCS[i], dict, HASHFUNC_NAMES[i]);
    }
}

static void get_and_report_distribution(hashfunc_t hashfunc, Pairs dict, const char *hashfunc_name) {
    HashMap *hashmap = hashmap_create(hashfunc, HASHMAP_SIZE);
    fill_hashmap(&dict, hashmap);
    size_t sizes[HASHMAP_SIZE] = {};
    get_distribution(hashmap->array, sizes);
    print_distribution(hashfunc_name, sizes, hashmap);
    hashmap_dtor(hashmap);
}

static void print_distribution(const char *hashfunc_name, size_t *sizes, HashMap *hashmap) {
    for (size_t i = 0; i < HASHMAP_SIZE; ++i) {
        printf("%s,%zu,%zu", hashfunc_name, i, sizes[i]);
        for (size_t w = 0; w < sizes[i]; ++w) {
            printf(",%s", hashmap->array[i].nodes[w].key);
        }
        printf("\n");
    }
}

static void get_distribution(List *lists, size_t *sizes) {
    for (size_t i = 0; i <  HASHMAP_SIZE; ++i) {
        sizes[i] = lists[i].size;
    }
}

static double get_time(hashfunc_t hashfunc, Pairs pairs) {
    volatile hash_t hash = 0;

    clock_t begin = clock();
    for (size_t t = 0; t < REPEAT_TIMES; ++t) {
        for (size_t i = 0; i < pairs.pairs_amount; ++i) {
            hash = hashfunc(pairs.pairs[i].key);
        }
    }
    clock_t end = clock();

    double time =  (double)(end - begin) / CLOCKS_PER_MS;
    return time;
}
