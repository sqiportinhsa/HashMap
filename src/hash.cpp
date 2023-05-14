#include <assert.h>
#include <stdio.h>

#include "hash.h"

static hash_t rol(hash_t val);
static hash_t ror(hash_t val);

const size_t BIT_PER_BYTE = 8;
const size_t SHIFT = sizeof(hash_t) * BIT_PER_BYTE - 1;

const hash_t CRC32_CONST = 0x04C11DB7;

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
    hash_t symbol = *key;

    while (symbol != 0) {
        sum += symbol;
        ++key;
        symbol = *key;
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

    while (sym != 0) {
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
            crc = (crc >> 1) ^ (CRC32_CONST & mask);
        }

        ++key;
        sym = *key;
    }

    return ~crc;
}

static hash_t rol(hash_t val) {
    hash_t new_val = (val << 1) | (val >> SHIFT);
    return new_val;
}

static hash_t ror(hash_t val) {
    hash_t new_val = (val >> 1) | (val << SHIFT);
    return new_val;
}