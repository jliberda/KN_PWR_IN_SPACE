#include "esp_err.h"

esp_err_t storage_init(void);
esp_err_t storage_save(const char *type, const char *key, const char *value);
esp_err_t storage_set_default(void);
esp_err_t storage_read(const char *key);
esp_err_t storage_delete(const char *key);
void storage_list(void);