#include <stdlib.h>

#include "hash.h"

const char *DATA_FILENAME = "../data/big.txt";

int main() {
    Input input = get_input(DATA_FILENAME);
    Pairs dict  = get_pairs(&input);
    double times[HASHFUNCS_SIZE] = {};
    get_times(times, dict);
    print_times(times);
    //get_and_report_all_distributions(dict);
    free(input.data);
    free(dict.pairs);
}