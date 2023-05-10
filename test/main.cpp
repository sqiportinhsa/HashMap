#include <stdio.h>

#include "test.h"
#include "../src/hash.h"

int main() {
    check_hashmap(const_hash);
    check_hashmap(first_char_hash);
    check_hashmap(char_sum_hash);
    check_hashmap(ror_hash);
    check_hashmap(rol_hash);
    check_hashmap(gnu_hash);
    check_hashmap(crc32_hash);
    return 0;
}