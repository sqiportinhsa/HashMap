#ifndef HASH_H
#define HASH_H

#include <stdint.h>
#include <stdio.h>

typedef uint32_t hash_t;

typedef hash_t (*hashfunc_t)(const char *key);

hash_t      const_hash(const char *key);
hash_t first_char_hash(const char *key);
hash_t   char_sum_hash(const char *key);
hash_t     strlen_hash(const char *key);
hash_t        rol_hash(const char *key);
hash_t        ror_hash(const char *key);
hash_t        gnu_hash(const char *key);
hash_t      crc32_hash(const char *key);

// ToDo единый массив
const hashfunc_t HASHFUNCS[] = {const_hash,
                           first_char_hash,
                             char_sum_hash,
                              strlen_hash,
                                  rol_hash,
                                  ror_hash,
                                  gnu_hash,
                                crc32_hash};

const size_t HASHFUNCS_SIZE = sizeof(HASHFUNCS) / sizeof(hashfunc_t);

const char* const HASHFUNC_NAMES[] = {"const hash", 
                                 "first_char_hash",
                                   "char_sum_hash",
                                     "strlen_hash",
                                        "rol_hash",
                                        "ror_hash",
                                        "gnu_hash",
                                      "crc32_hash"};

#endif