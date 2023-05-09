#ifndef HASH_H
#define HASH_H

typedef unsigned int hash_t;

hash_t      const_hash(const char *key);
hash_t first_char_hash(const char *key);
hash_t   char_sum_hash(const char *key);
hash_t        rol_hash(const char *key);
hash_t        ror_hash(const char *key);
hash_t        gnu_hash(const char *key);
hash_t      crc32_hash(const char *key);

#endif