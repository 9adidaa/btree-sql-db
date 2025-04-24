#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include "db.h"

#define INPUT_SIZE 256

void print_help() {
    printf("\nAvailable Commands:\n");
    printf("  INSERT INTO table VALUES (id, 'name', age)\n");
    printf("  SELECT * FROM table WHERE id=xxx\n");
    printf("  DELETE FROM table WHERE id=xxx\n");
    printf("  IMPORT filename.csv\n");
    printf("  PRINT  → Display the B-tree\n");
    printf("  EXIT   → Exit the program\n\n");
}

int main() {
    Table table = {0};

    // Load persisted binary data
    load_from_file(&table, "data.db");

    char input[INPUT_SIZE];
    print_help();

    while (1) {
        printf("db > ");
        if (!fgets(input, sizeof(input), stdin)) break;

        // Remove trailing newline
        input[strcspn(input, "\n")] = 0;

        if (strncmp(input, "EXIT", 4) == 0) {
            printf("Exiting.\n");
            break;

        } else if (strncmp(input, "INSERT", 6) == 0) {
            int id, age;
            char name[50];

            if (sscanf(input, "INSERT INTO table VALUES (%d, '%49[^']', %d)", &id, name, &age) == 3) {
                Row row = {id, "", age};
                strncpy(row.name, name, sizeof(row.name) - 1);

                if (search_node(&table, id)) {
                    printf("Error: A row with id %d already exists.\n", id);
                } else {
                    insert_node(&table, id, row);
                    save_to_file(&table, "data.db");
                    printf("Inserted (%d, %s, %d)\n", id, row.name, row.age);
                }
            } else {
                printf("Syntax error in INSERT command.\n");
            }

        } else if (strncmp(input, "SELECT", 6) == 0) {
            int id;
            if (sscanf(input, "SELECT * FROM table WHERE id=%d", &id) == 1) {
                Row* result = search_node(&table, id);
                if (result) {
                    printf("Found: (%d, %s, %d)\n", result->id, result->name, result->age);
                } else {
                    printf("No row found with id %d.\n", id);
                }
            } else {
                printf("Syntax error in SELECT command.\n");
            }

        } else if (strncmp(input, "DELETE", 6) == 0) {
            int id;
            if (sscanf(input, "DELETE FROM table WHERE id=%d", &id) == 1) {
                delete_node(&table, id);
                save_to_file(&table, "data.db");
            } else {
                printf("Syntax error in DELETE command.\n");
            }

        } else if (strncmp(input, "PRINT", 5) == 0) {
            print_btree(table.root, 0);

        } else if (strncmp(input, "IMPORT", 6) == 0) {
            char filename[100];
            if (sscanf(input, "IMPORT %99s", filename) == 1) {
                load_csv_into_table(&table, filename);
                save_to_file(&table, "data.db");
            } else {
                printf("Syntax error in IMPORT command. Usage: IMPORT filename.csv\n");
            }

        } else {
            printf("Unrecognized command.\n");
            print_help();
        }
    }

    return 0;
}
