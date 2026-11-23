#include <stdlib.h> // strtol(), strtof()
#include <string.h>
#include "validate.h"

bool validate_int(const char *x) {
    char *end;
    long v = strtol(x, &end, 10); // strtol(str, pointer to end(e.g. when numbers end), base ten)
    return end != x && *end == '\0' && INT32_MIN <= v && v <= INT32_MAX;
}

bool validate_float(const char *x) {
    char *end;
    float v = strtof(x, &end);
    return end != x && *end == '\0';
}

bool validate_bool(const char *x) {
    return strcmp(x, "true") == 0 || strcmp(x, "false") == 0;
}