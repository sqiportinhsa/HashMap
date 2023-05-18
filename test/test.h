#ifndef TEST_H
#define TESH_H

#include "../src/hashmap.h"
#include "../src/input.h"

void check_hashmap(hashfunc_t hashfunc, Pairs dict);

int comparator(const void *pair1, const void *pair2);

#endif