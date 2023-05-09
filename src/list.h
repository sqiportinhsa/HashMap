#ifndef LIST_H
#define LIST_H

#include <stdio.h>

const size_t MAX_KEY_SIZE = 32;
const size_t INITIAL_LIST_SIZE = 1;

struct Node {
    char key[MAX_KEY_SIZE] = "";
    char *value = nullptr;
};

struct List {
    size_t max_size = 0;
    size_t     size = 0;

    Node *nodes = nullptr;
};

void  list_init  (List *list);
void  list_dtor  (List *list);
void  list_insert(List *list, char *key, char *value);
char *list_find  (List *list, char *key);

#endif 
