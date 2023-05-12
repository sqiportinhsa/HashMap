#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "input.h"

static int prepare_pairs(char *input_ptr, size_t size);
static size_t count_elements_in_file(const char *filename);
static size_t read_file(char *dest, size_t size, const char* filename);
static size_t skip_to_newline(char *pointer);

Input get_input(const char *filename) {
    Input input = {};
    input.size = count_elements_in_file(filename);
    input.data = (char*) calloc(input.size, sizeof(char));
    if (!input.data) return input;

    input.size = read_file(input.data, input.size, filename);
    return input;
}

void fill_hashmap(Input input, HashMap *hashmap) {
    size_t shift = 0;

    while (shift < input.size) {
        char *key = input.data + shift;
        shift += shift_to_next_string(input.data + shift);

        char *value = input.data + shift;
        shift += shift_to_next_string(input.data + shift);

        hashmap_insert(hashmap, key, value);
    }
}

size_t shift_to_next_string(char *ptr) {
    size_t shift = skip_to_newline(ptr);
    *(ptr + shift) = '\0';
    ++shift;
    return shift;
}

static int prepare_pairs(char *input_ptr, size_t size) {
    size_t shift = 0;
    size_t strings_counter = 0;

    // set '\0' between strings to split words & count strings
    while (shift < size) {
        size_t delta = skip_to_newline(input_ptr);
        input_ptr += delta;
        shift     += delta;

        *input_ptr = '\0';

        ++strings_counter;
        ++input_ptr;
        ++shift;
    }

    return strings_counter % 2;
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

