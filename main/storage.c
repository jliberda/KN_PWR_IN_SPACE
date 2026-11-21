#include <stdio.h> // printf
#include <stdlib.h> // atoi, atof
#include <string.h> // strcmp
#include "nvs_flash.h" // nvs_flash_init, nvs_flash_erase
#include "nvs.h" // nvs_open, nvs_close, nvs_commit...
#include "esp_err.h" // esp_err_t, ESP_OK...
#include "storage.h" // declarations of the functs.

// esp_err_t - typ danych int, przyjmujący wartości w postaci np. ESP_OK == 0. (Espressif Error Type)
esp_err_t storage_init(void) {
    esp_err_t err = nvs_flash_init();

    if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
    printf("WARNING: NVS has no free pages, erasing partition and restoring defaults.\n");
    nvs_flash_erase();
    err = nvs_flash_init();
    }
    else if (err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    printf("WARNING: NVS data is in a newer format, erasing partition and restoring defaults.\n");
    nvs_flash_erase();
    err = nvs_flash_init();
    }

    return err;
}

esp_err_t storage_save(const char *type, const char *key, const char *value) {
    nvs_handle_t handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &handle);
    if (err != ESP_OK) return err;

    if (strcmp(type, "int") == 0) {
            int v = atoi(value);
            err = nvs_set_i32(handle, key, v);
    }
    else if (strcmp(type, "float") == 0) {
            float v = atof(value);
            err = nvs_set_blob(handle, key, &v, sizeof(v));
    }
    else if (strcmp(type, "bool") == 0) {
        if (strcmp(value, "true") == 0) {
            err = nvs_set_u8(handle, key, 1);
        } else {
            err = nvs_set_u8(handle, key, 0);
        }
    }
    else if (strcmp(type, "str") == 0) {
            err = nvs_set_str(handle, key, value);
    }
    else {
        err = ESP_ERR_INVALID_ARG;
    }

    // writes the initialized above pairs into nvs partition's namespace.
    if (err == ESP_OK) {err =nvs_commit(handle);}

    nvs_close(handle);

    return err;
}

esp_err_t storage_set_default(void) {
    nvs_flash_erase();
    esp_err_t err = nvs_flash_init();
    if (err != ESP_OK) {return err;}

    storage_save("str", "rocket_name", "Atlantis");
    storage_save("int", "max_amplitude", "800");
    storage_save("float", "max_temp", "40.7");
    storage_save("bool", "ready", "false");
    
    return ESP_OK;
}

esp_err_t storage_read(const char *key) {
    nvs_handle_t handle;
    esp_err_t err = nvs_open("storage", NVS_READONLY, &handle);
    if (err != ESP_OK) {return err;}

    nvs_type_t type;
    err = nvs_find_key(handle, key, &type);
    if (err  != ESP_OK) {
        nvs_close(handle);
        return err;
    }

    if (type == NVS_TYPE_I32) {
        int32_t v;
        nvs_get_i32(handle, key, &v);
        printf("%ld (int)\n", v);
    }
    else if (type == NVS_TYPE_BLOB) {
        float v;
        size_t len = sizeof(v);
        nvs_get_blob(handle, key, &v, &len);
        printf("%f (float)\n", v);
    }
    else if (type == NVS_TYPE_U8) {
        uint8_t v;
        nvs_get_u8(handle, key, &v);

        printf("%s (bool)\n", (v == 1) ? "true" : "false");
    }
    else if (type == NVS_TYPE_STR) {
        // nvs_get_str() - handle, key, buffer(value), len (first: bufor size, 2nd: string length(value len)).
        size_t len = 0;
        nvs_get_str(handle, key, NULL, &len);
        
        char s[len];
        nvs_get_str(handle, key, s, &len);
        printf("%s (str)\n", s);
    }

    nvs_close(handle);

    return err;
}

esp_err_t storage_delete(const char *key) {
    nvs_handle_t handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &handle);
    if (err != ESP_OK) {return err;}

    err = nvs_erase_key(handle, key);
    if (err == ESP_OK) {err = nvs_commit(handle);}

    nvs_close(handle);
    return err;
}

void storage_list(void) {
    // pointer to first variable in the storage.
    nvs_iterator_t iter = NULL;

    // nvs_entry_find(partition_name, namespace_name, type_you_want_to_find, where_to_save_output)
    esp_err_t res = nvs_entry_find("nvs", "storage", NVS_TYPE_ANY, &iter);
    if (res != ESP_OK) {printf("No variables to be listed.\n"); return;}
    
    printf("KEY : VALUE (type)\n");
    while (res == ESP_OK) {
        nvs_entry_info_t info;
        nvs_entry_info(iter, &info);

        printf("%s : ", info.key);
        storage_read(info.key);

        res = nvs_entry_next(&iter); // move the pointer.
    }
    // nvs_iterator_t reserves memory. (like malloc)
    nvs_release_iterator(iter);
}