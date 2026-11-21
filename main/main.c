#include "storage.h"
#include "cli.h"

void app_main(void) {
    storage_init();
    cli_start();
}