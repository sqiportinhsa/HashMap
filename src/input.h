#ifndef INPUT_H
#define INPUT_H

#include "hashmap.h"

struct Input {
    char  *data = nullptr;
    size_t size = 0;
};

Input get_input(char *filename);
void fill_hashmap(Input input, HashMap *hashmap);

#endif