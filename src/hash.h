#ifndef HASH_H
#define HASH_H

typedef unsigned int hash_t;

typedef hash_t (*hashfunc_t)(const char *key);

hash_t      const_hash(const char *key);
hash_t first_char_hash(const char *key);
hash_t   char_sum_hash(const char *key);
hash_t        rol_hash(const char *key);
hash_t        ror_hash(const char *key);
hash_t        gnu_hash(const char *key);
hash_t      crc32_hash(const char *key);

const hashfunc_t HASHFUNCS[] = {const_hash,
                           first_char_hash,
                             char_sum_hash,
                                  rol_hash,
                                  ror_hash,
                                  gnu_hash,
                                crc32_hash};

const size_t HASHFUNCS_SIZE = sizeof(HASHFUNCS) / sizeof(hashfunc_t);

const char* HASHFUNC_NAMES[] = {"const hash", 
                           "first_char_hash",
                             "char_sum_hash",
                                  "rol_hash",
                                  "ror_hash",
                                  "gnu_hash",
                                "crc32_hash"};

#endif