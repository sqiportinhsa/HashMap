#include <stdlib.h>

#include "hash.h"

const char *DATA_FILENAME = "../data/big2.txt";

int main() {
    Input input = get_input(DATA_FILENAME);
    double times[HASHFUNCS_SIZE] = {};
    get_times(input, times);
    print_times(times);
    get_and_report_all_distributions(input);
    free(input.data);
}