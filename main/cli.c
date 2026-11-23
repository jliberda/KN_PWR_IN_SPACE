#include <stdio.h>
#include <string.h>
#include "storage.h"
#include "nvs.h"
#include "freertos/FreeRTOS.h" //pdMS_TO_TICKS()
#include "freertos/task.h" // vTaskDelay()

static void print_result(esp_err_t err) {
    switch (err) {
        case ESP_OK:
            printf("OK\n");
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            printf("Variable not found.\n");
            break;
        case ESP_ERR_INVALID_ARG:
            printf("Invalid type or value.\n");
            break;
        case ESP_ERR_NVS_KEY_TOO_LONG:
            printf("Key too long (max 15 chars).\n");
            break;
        default:
            printf("Error: %s\n", esp_err_to_name(err));
            break;
    }
}

void cli_start(void) {
    char command[100];

    while (1) {
        printf("cli> ");

        while (fgets(command, sizeof(command), stdin) == NULL) {
            clearerr(stdin); // clears the error and EOF indicators of stdin.
            vTaskDelay(pdMS_TO_TICKS(10)); // stops the code for 10 ms.
        }

        printf("%s", command);

        // 1st string after splitting the comand. (spaces, tab, cursor return <-, new line)
        char *token = strtok(command, " \t\r\n");

        if (token == NULL) {continue;}
        else if (strcmp(token, "init") == 0) {
            esp_err_t err = storage_init();
            if (err != ESP_OK) {
                print_result(err);
            }
        }
        else if (strcmp(token, "save") == 0) {
            const char *type = strtok(NULL, " \t\r\n"); // strtok remembers prev place it ended it's operation. (in command)
            const char *key = strtok(NULL, " \t\r\n");
            const char *value = strtok(NULL, " \t\r\n");
            if (type != NULL && key != NULL && value != NULL) {
                esp_err_t err = storage_save(type, key, value);
                if (err != ESP_OK) {print_result(err);}
            }
            else {printf("Invalid command.\n");}
        }
        else if (strcmp(token, "default") == 0) {
            esp_err_t err = storage_set_default();
                if (err != ESP_OK) {print_result(err);}
        }
        else if (strcmp(token, "read") == 0) {
            char *key = strtok(NULL, " \t\r\n");
            if (key != NULL) {
                esp_err_t err = storage_read(key);
                if (err != ESP_OK) {print_result(err);}
            }
            else {printf("Invalid command.\n");}
        }
        else if (strcmp(token, "delete") == 0) {
            char *key = strtok(NULL, " \t\r\n");
            if (key != NULL) {
                esp_err_t err = storage_delete(key);
                if (err != ESP_OK) {print_result(err);}
            }
            else {printf("Invalid command.\n");}
        }
        else if (strcmp(token, "list") == 0) {
            storage_list();
        }
        else if (strcmp(token, "exit") == 0) {
            return;
        }
        else {printf("Invalid operation name.\n");}
    }
}