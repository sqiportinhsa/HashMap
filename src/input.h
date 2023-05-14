#ifndef INPUT_H
#define INPUT_H

#include "hashmap.h"

struct Input {
    char  *data = nullptr;
    size_t size = 0;
};

Input get_input(const char *filename);
void fill_hashmap(Input input, HashMap *hashmap);
size_t shift_to_next_string(char *ptr);

#endif