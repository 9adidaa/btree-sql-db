#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

#define INPUT_SIZE 256

int main() {
    Table table = {0};
    char input[INPUT_SIZE];

    while (1) {
        printf("db > ");
        if (!fgets(input, sizeof(input), stdin)) break;

        if (strncmp(input, "EXIT", 4) == 0) {
            printf("Exiting.\n");
            break;
        } else if (strncmp(input, "INSERT", 6) == 0) {
            int id, age;
            char name[50];

            if (sscanf(input, "INSERT INTO table VALUES (%d, '%49[^']', %d)", &id, name, &age) == 3) {
                Row row = {id, "", age};
                strncpy(row.name, name, sizeof(row.name) - 1);

                if (search_node(&table, id) != NULL) {
                    printf("Error: A row with id %d already exists.\n", id);
                } else {
                    insert_node(&table, id, row);
                    printf("Inserted (%d, %s, %d)\n", id, row.name, row.age);
                }
            } else {
                printf("Syntax error in INSERT command.\n");
            }
        }
         else if (strncmp(input, "SELECT", 6) == 0) {
            int id;
            if (sscanf(input, "SELECT * FROM table WHERE id=%d", &id) == 1) {
                Row* result = search_node(&table, id);
                if (result) {
                    printf("Found: (%d, %s, %d)\n", result->id, result->name, result->age);
                } else {
                    printf("No row found with id %d\n", id);
                }
            } else {
                printf("Syntax error in SELECT command.\n");
            }

        } else if (strncmp(input, "DELETE", 6) == 0) {
            int id;
            if (sscanf(input, "DELETE FROM table WHERE id=%d", &id) == 1) {
                delete_node(&table, id);
            } else {
                printf("Syntax error in DELETE command.\n");
            }

        } else if (strncmp(input, "PRINT", 5) == 0) {
            print_btree(table.root, 0);
        } else {
            printf("Unrecognized command.\n");
        }
    }

    return 0;
}
