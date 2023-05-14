#include "../../src/hashmap.h"
#include "../../src/hashmap.h"
#include "../../src/input.h"

struct Keys {
    char **data = nullptr;
    size_t size = 0;
};

void print_times(double *times);
void   get_times(Input input, double *times);

void get_and_report_all_distributions(Input input);