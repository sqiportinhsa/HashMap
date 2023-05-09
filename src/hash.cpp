#include <assert.h>
#include <stdio.h>

#include "hash.h"

static hash_t rol(hash_t val);
static hash_t ror(hash_t val);

hash_t const_hash(const char *key) {
    assert(key);
    return 1;
}

hash_t first_char_hash(const char *key) {
    assert(key);
    return *key;
}

hash_t char_sum_hash(const char *key) {
    assert(key);
    hash_t sum = 0;
    hash_t sym = *key;

    while (sym != 0) {
        sum += sym;
        ++key;
        sym = *key;
    }

    return sum;
}

hash_t rol_hash(const char *key) {
    assert(key);
    hash_t hash = 0;
    char sym = *key;

    while (sym != 0) {
        hash = rol(hash) + sym;
        ++key;
        sym = *key;
    }

    return hash;
}

hash_t ror_hash(const char *key) {
    assert(key);
    hash_t hash = 0;
    char sym = *key;

    while (sym != 0) {
        hash = ror(hash) + sym;
        ++key;
        sym = *key;
    }

    return hash;
}

hash_t gnu_hash(const char *key) {
    assert(key);
    hash_t hash = 5381;
    char sym = *key;

    while (key != 0) {
        hash = ((hash << 5) + hash) + sym;
        ++key;
        sym = *key;
    }

    return hash;
}

hash_t crc32_hash(const char *key) {
    unsigned char sym = *key;
    unsigned int  crc = 0xFFFFFFFF; 
    unsigned int mask = 0;

    while (sym != 0) {
        crc = crc ^ sym;

        for (int j = 7; j >= 0; j--) {
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0x82608EDB & mask);
        }

        ++key;
        sym = *key;
    }

    return ~crc;
}

static hash_t rol(hash_t val) {
    size_t shift = sizeof(hash_t) << 3 - 1;
    hash_t new_val = (val << 1) | (val >> shift);
    return new_val;
}

static hash_t ror(hash_t val) {
    size_t shift = sizeof(hash_t) << 3 - 1;
    hash_t new_val = (val >> 1) | (val << shift);
    return new_val;
}