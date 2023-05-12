#include <string.h>
#include "test.h"

static bool check_hashmap(HashMap *hashmap, Input input);

static bool check_pairs(Input input, HashMap *hashmap);
static bool check_pair (HashMap *hashmap, const char *key, const char *value);

static bool check_hash(HashMap *hashmap);
static bool check_hash(List *list, hashfunc_t hashfunc, hash_t correct_hash);

const size_t HASHMAP_SIZE = 5;
const char *DATA_FILENAME = "../data/vova.txt";

void check_hashmap(hashfunc_t hashfunc) {
    HashMap *hashmap = hashmap_init(hashfunc, HASHMAP_SIZE);
    Input input = get_input(DATA_FILENAME);
    fill_hashmap(input, hashmap);
    check_hashmap(hashmap, input);
    hashmap_dtor(hashmap);
}

static bool check_hashmap(HashMap *hashmap, Input input) {
    bool hash_correct  = check_hash(hashmap);
    if (hash_correct) {
        printf("hash checkup done successful\n");
    }

    bool pairs_correct = check_pairs(input, hashmap);
    if (pairs_correct) {
        printf("pairs checkup done successful\n");
    }

    return hash_correct & pairs_correct;
}

static bool check_pairs(Input input, HashMap *hashmap) {
    size_t shift = 0;
    bool correct = true;

    while (shift < input.size) {
        char *key = input.data + shift;
        shift += shift_to_next_string(input.data + shift);

        char *value = input.data + shift;
        shift += shift_to_next_string(input.data + shift);

        if(!check_pair(hashmap, key, value)) {
            correct = false;
        }

        if (shift % 1000 == 0) {
            printf("%zu\n", shift);
        }
    }

    return correct;
}

static bool check_pair(HashMap *hashmap, const char *key, const char *value) {
    char *found = hashmap_find(hashmap, key);
    if (!found) {
        fprintf(stderr, "error: value not found.\n"
                    "key: %s. expected value: %s\n", key, value);
        return false;
    }

    if (!strcmp(value, found)) {
        return true;
    }

    fprintf(stderr, "error: value in dictionary and value in hashmap don't match.\n"
                    "key: %s. expected value: %s. got: %s\n", key, value, found);
    return false;
}

static bool check_hash(HashMap *hashmap) {
    bool correct = true;

    for (size_t i = 0; i < hashmap->array_size; ++i) {
        if (!check_hash(&hashmap->array[i], hashmap->hashfunc, i)) {
            correct = false;
        }
    }

    return correct;
}

static bool check_hash(List *list, hashfunc_t hashfunc, hash_t correct_hash) {
    bool correct = true;

    for (size_t i = 0; i < list->size; ++i) {
        hash_t hash = hashfunc(list->nodes[i].key) % HASHMAP_SIZE;
        if (hash != correct_hash) {
            correct = false;
            fprintf(stderr, "error: node with inappropriate hash in list\n"
                            "key: %s. expected hash: %u. got: %u\n", 
                            list->nodes[i].key, correct_hash, hash);
        }
    }

    return correct;
}
