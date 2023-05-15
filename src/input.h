#ifndef INPUT_H
#define INPUT_H

#include "hashmap.h"

struct Input {
    char  *data = nullptr;
    size_t size = 0;
};

struct Pair {
    const char *key;
    const char *value;
};

struct Pairs {
    Pair  *pairs;
    size_t pairs_amount;
};

Input get_input(const char *filename);
Pairs get_pairs(Input input);
void fill_hashmap(Pairs dict, HashMap *hashmap);

#endif