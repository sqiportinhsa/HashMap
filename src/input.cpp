#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "input.h"

static size_t count_elements_in_file(const char *filename);
static size_t read_file(char *dest, size_t size, const char* filename);
static size_t shift_to_next_string(char *ptr);
static size_t skip_to_newline(char *pointer);

Input get_input(const char *filename) {
    Input input = {};
    input.size = count_elements_in_file(filename);
    input.data = (char*) calloc(input.size, sizeof(char));
    if (!input.data) return input;

    input.size = read_file(input.data, input.size, filename);
    return input;
}

void fill_hashmap(Pairs dict, HashMap *hashmap) {
    for (size_t i = 0; i < dict.pairs_amount; ++i) {
        hashmap_insert(hashmap, dict.pairs[i].key, dict.pairs[i].value);
    }
}

Pairs get_pairs(Input input) {
    Pairs pairs  = {};
    pairs.pairs  = (Pair*) calloc(input.size / 2, sizeof(Pair));
    size_t shift = 0;

    while (shift < input.size) {
        size_t key_len = 0;
        char *key = input.data + shift;
        key_len = shift_to_next_string(input.data + shift);
        shift += key_len;

        char *value = input.data + shift;
        shift += shift_to_next_string(input.data + shift);

        if (key_len <= 32) {
            pairs.pairs[pairs.pairs_amount].key   = key;
            pairs.pairs[pairs.pairs_amount].value = value;
            ++pairs.pairs_amount;
        }
    }

    return pairs;
}

static size_t shift_to_next_string(char *ptr) {
    size_t shift = skip_to_newline(ptr);
    *(ptr + shift) = '\0';
    ++shift;
    return shift;
}

static size_t count_elements_in_file(const char *filename) {
    assert(filename != nullptr && "nullptr to filename");
    struct stat a = {};
    stat(filename, &a);
    return a.st_size + 1;
}

static size_t read_file(char *dest, size_t size, const char* filename) {
    // returns file size
    assert(dest != nullptr && "dest  is nullptr");
    
    FILE *input = fopen(filename, "rb");
    if (input == nullptr) {
        return 0;
    }
    size_t nread = fread(dest, sizeof(char), size, input);
    fclose(input);

    size_t real_amount_of_symbols = nread + 1;
    dest[real_amount_of_symbols - 1] = '\0';
    return real_amount_of_symbols;
}

static size_t skip_to_newline(char *pointer) {
    assert(pointer != nullptr && "pointer is nullptr");
    size_t i = 0;
    for (; *(pointer + i) != '\n' && *(pointer + i) != '\0'; ++i);
    return i;
}

