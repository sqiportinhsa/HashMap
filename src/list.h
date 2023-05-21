#ifndef LIST_H
#define LIST_H

#include <stdio.h>

const size_t KEY_SIZE = 32;
const size_t INITIAL_LIST_SIZE = 1;

struct Node {
    char key[KEY_SIZE] = "";
    const char *value = nullptr;
};

struct List {
    size_t max_size = 0;
    size_t     size = 0;

    Node *nodes = nullptr;
};

void list_init  (List *list);
void list_dtor  (List *list);
void list_insert(List *list, const char *key, const char *value);

const char *list_find(List *list, const char *key);

#endif 
