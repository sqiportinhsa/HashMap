#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

static void list_resize(List *list);
static inline int __attribute__((always_inline)) strcmp_asm(const char *srt1, const char *str2);

void list_init(List *list) {
    assert(list);
    list->max_size = 0;
    list->size     = 0;
    list->nodes = nullptr;
}

void list_dtor(List *list) {
    assert(list);
    free(list->nodes);
}

void list_insert(List *list, const char *key, const char *value) {
    assert(list && key && value);
    if (list->size == list->max_size) {
        list_resize(list);
        assert(list->nodes);
    }

    list->nodes[list->size].value = value;
    strncpy(list->nodes[list->size].key, key, KEY_SIZE);
    ++(list->size);
}

static void list_resize(List *list) {
    assert(list);

    if (!list->nodes) {
        list->nodes = (Node*) calloc(INITIAL_LIST_SIZE, sizeof(Node));
        list->max_size = INITIAL_LIST_SIZE;
        return;
    }

    list->nodes = (Node*) realloc(list->nodes, list->max_size * 2 * sizeof(Node));
    list->max_size *= 2;
}

