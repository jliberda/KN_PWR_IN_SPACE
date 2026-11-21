#include <stdio.h>
#include <string.h>
#include "storage.h"

void cli_start(void) {
    char command[100]; // input

    while (1) {
        printf("cli> ");

        if (fgets(command, sizeof(command), stdin) == NULL) {break;}

        // 1st string after splitting the comand. (spaces, new line, tab)
        char *token = strtok(command, " \t\n");

        if (token == NULL) {continue;}
        else if (strcmp(token, "init") == 0) {
            esp_err_t err = storage_init();
            if (err != ESP_OK) {
                printf("Error: %s\n", esp_err_to_name(err));
            }
        }
        else if (strcmp(token, "save") == 0) {
            const char *type = strtok(NULL, " \t\n"); // strtok remembers prev place it ended it's operation. (in command)
            const char *key = strtok(NULL, " \t\n");
            const char *value = strtok(NULL, " \t\n");
            if (type != NULL && key != NULL && value != NULL) {storage_save(type, key, value);}
            else {printf("Invalid command.\n");}
        }
        else if (strcmp(token, "default") == 0) {
            storage_set_default();
        }
        else if (strcmp(token, "read") == 0) {
            char *key = strtok(NULL, " \t\n");
            if (key != NULL) {storage_read(key);}
            else {printf("Invalid command.\n");}
        }
        else if (strcmp(token, "delete") == 0) {
            char *key = strtok(NULL, " \t\n");
            if (key != NULL) {storage_delete(key);}
            else {printf("Invalid command.\n");}
        }
        else if (strcmp(token, "list") == 0) {
            storage_list();
        }
        else if (strcmp(token, "exit") == 0) {
            break;
        }
        else {printf("Invalid operation name.\n");}
    }

}