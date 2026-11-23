#include <assert.h>
#include <stdio.h>
#include "storage.h"
#include "cli.h"
#include "validate.h"

static void run_tests(void) {
    assert(validate_int("123"));
    assert(validate_int("-5"));
    assert(!validate_int("abc"));
    assert(!validate_int("12abc"));
    assert(!validate_int(""));

    assert(validate_float("40.7"));
    assert(!validate_float("abc"));
    assert(!validate_float("1.2.3"));

    assert(validate_bool("true"));
    assert(validate_bool("false"));
    assert(!validate_bool("yes"));

    printf("Unit tests passed.\n");
}

void app_main(void) {
    run_tests();
    storage_init();
    cli_start();
}