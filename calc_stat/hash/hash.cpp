#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hash.h"

const size_t HASHMAP_SIZE = 16127; 
const double CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;
const int REPEAT_TIMES = 100;

static double get_time(hashfunc_t hashfunc, Keys keys);
static Keys   get_keys(Input input);

static void get_and_report_distribution(hashfunc_t hashfunc, Input input, const char *hashfunc_name);
static void           print_distribution(const char *hashfunc_name, size_t *sizes);
static void             get_distribution(List *lists,         size_t *sizes);


void get_times(Input input, double *times) {
    Keys keys = get_keys(input);

    for (size_t i = 0;  i < HASHFUNCS_SIZE; ++i) {
        times[i] = get_time(HASHFUNCS[i], keys);
    }

    free(keys.data);
}

void print_times(double *times) {
    for (size_t i = 0; i < HASHFUNCS_SIZE; ++i) {
        printf("%s,%lf\n", HASHFUNC_NAMES[i], times[i]);
    }
}

void get_and_report_all_distributions(Input input) {
    for (size_t i = 0; i < HASHFUNCS_SIZE; ++i) {
        get_and_report_distribution(HASHFUNCS[i], input, HASHFUNC_NAMES[i]);
    }
}

static void get_and_report_distribution(hashfunc_t hashfunc, Input input, const char *hashfunc_name) {
    HashMap *hashmap = hashmap_create(hashfunc, HASHMAP_SIZE);
    fill_hashmap(input, hashmap);
    size_t sizes[HASHMAP_SIZE] = {};
    get_distribution(hashmap->array, sizes);
    print_distribution(hashfunc_name, sizes);
    hashmap_dtor(hashmap);
}

static void print_distribution(const char *hashfunc_name, size_t *sizes) {
    for (size_t i = 0; i < HASHMAP_SIZE; ++i) {
        printf("%s,%zu,%zu\n", hashfunc_name, i, sizes[i]);
    }
}

static void get_distribution(List *lists, size_t *sizes) {
    for (size_t i = 0; i <  HASHMAP_SIZE; ++i) {
        sizes[i] = lists[i].size;
    }
}

static double get_time(hashfunc_t hashfunc, Keys keys) {
    volatile hash_t hash = 0;

    clock_t begin = clock();
    for (int t = 0; t < REPEAT_TIMES; ++t) {
        for (size_t i = 0; i < keys.size; ++i) {
            hash = hashfunc(keys.data[i]);
        }
    }
    clock_t end = clock();

    double time =  (double)(end - begin) / CLOCKS_PER_MS;
    return time;
}

static Keys get_keys(Input input) {
    Keys keys = {};
    size_t shift = 0;
    keys.data = (char**) calloc(input.size / 2, sizeof(char*));

    while (shift < input.size) {
        char *key = input.data + shift;
        shift += shift_to_next_string(input.data + shift);

        char *value = input.data + shift;
        shift += shift_to_next_string(input.data + shift);

        keys.data[keys.size] = key;
        ++keys.size;
    }

    return keys;
}