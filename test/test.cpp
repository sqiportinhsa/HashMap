#include <stdlib.h>
#include <string.h>
#include "test.h"

static bool check_hashmap(HashMap *hashmap, Pairs dict);

static bool check_pairs(HashMap *hashmap, Pairs pairs);
static bool check_pair (HashMap *hashmap, const char *key, const char *value);

static bool check_hash(HashMap *hashmap);
static bool check_hash(List *list, hashfunc_t hashfunc, hash_t correct_hash);

const size_t HASHMAP_SIZE = 16127;

void check_hashmap(hashfunc_t hashfunc, Pairs dict) {
    HashMap *hashmap = hashmap_create(hashfunc, HASHMAP_SIZE);
    fill_hashmap(&dict, hashmap);
    check_hashmap(hashmap, dict);
    hashmap_dtor(hashmap);
}

int comparator(const void *pair1, const void *pair2) {
    return strcmp(((const Pair*) pair1)->key, ((const Pair*) pair2)->key);
}

static bool check_hashmap(HashMap *hashmap, Pairs dict) {
    bool hash_correct  = check_hash(hashmap);
    if (hash_correct) {
        printf("hash checkup done successful\n");
    }

    bool pairs_correct = check_pairs(hashmap, dict);
    if (pairs_correct) {
        printf("pairs checkup done successful\n");
    }

    return hash_correct & pairs_correct;
}

static bool check_pairs(HashMap *hashmap, Pairs pairs) {
    size_t shift = 0;
    bool correct = true;

    if(!check_pair(hashmap, pairs.pairs[0].key, pairs.pairs[0].value)) {
        correct = false;
    }

    for (size_t i = 1; i < pairs.pairs_amount; ++i) {
        if (!strcmp(pairs.pairs[i].key, pairs.pairs[i-1].key)) {
            continue;
        }

        if(!check_pair(hashmap, pairs.pairs[i].key, pairs.pairs[i].value)) {
            check_pair(hashmap, pairs.pairs[i].key, pairs.pairs[i].value);
            correct = false;
        }
    }

    return correct;
}

static bool check_pair(HashMap *hashmap, const char *key, const char *value) {
    const char *found = hashmap_find(hashmap, key);
    if (!found) {
        fprintf(stderr, "error: value not found.\n"
                        "key: %s. expected value: %s\n", key, value);
        return false;
    }

    if (!strcmp(value, found)) {
        return true;
    }

    fprintf(stderr, "error: value in dictionary and value in hashmap don't match.\n"
                    "key: <%s>. expected value: <%s>. got: <%s>\n", key, value, found);
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
