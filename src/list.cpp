#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

static void list_resize(List *list);
static int __attribute__((always_inline)) strcmp_asm(const char *srt1, const char *str2);

void list_init(List *list) {
    list->max_size = 0;
    list->size     = 0;
    list->nodes = nullptr;
}

void list_dtor(List *list) {
    free(list->nodes);
}

void list_insert(List *list, const char *key, const char *value) {
    if (list->size == list->max_size) {
        list_resize(list);
        assert(list->nodes);
    }

    list->nodes[list->size].value = value;
    strncpy(list->nodes[list->size].key, key, MAX_KEY_SIZE);
    ++(list->size);
}

const char *list_find(List *list, const char *key) {
    const char *value = nullptr;
    for (size_t i = 0; i < list->size; ++i) {
        if (!strcmp_asm(list->nodes[i].key, key)) {
            value = list->nodes[i].value;
            break;
        }
    }
    return value;
}

static int __attribute__((always_inline)) strcmp_asm(const char *srt1, const char *str2) {
    int result = 0;

    asm(
    ".intel_syntax noprefix\n"

    "vmovdqu ymm0, ymmword ptr [%1]\n" /* ymm0 <- srt1 */
    "vmovdqu ymm1, ymmword ptr [%2]\n" /* ymm1 <- str2 */

    "vptest  ymm0, ymm1\n"             /* cf = (srt1 == str2) */
    "mov %0, 0\n"       
    "setnc %b0\n"

    ".att_syntax prefix\n"

    : "=r"(result)
    : "r"(srt1), "r"(str2)
    : "ymm0", "ymm1", "cc"
    );

    return result;
}

static void list_resize(List *list) {
    if (!list->nodes) {
        list->nodes = (Node*) calloc(INITIAL_LIST_SIZE, sizeof(Node));
        list->max_size = INITIAL_LIST_SIZE;
        return;
    }

    list->nodes = (Node*) realloc(list->nodes, list->max_size * 2 * sizeof(Node));
    list->max_size *= 2;
}

