#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include "db.h"
#include "migration.h"  // You’ll create this

#define INPUT_SIZE 256

void print_help() {
    printf("\nAvailable Commands:\n");
    printf("  INSERT INTO table VALUES (id, 'name', age)\n");
    printf("  SELECT * FROM table WHERE id=xxx\n");
    printf("  SELECT * FROM table\n");
    printf("  DELETE FROM table WHERE id=xxx\n");
    printf("  IMPORT filename.csv\n");
    printf("  PRINT\n");
    printf("  EXIT\n\n");
}

int main() {
    Table table = {0};
    load_from_file(&table, "data.db");

    char input[INPUT_SIZE];
    print_help();

    while (1) {
        printf("db > ");
        if (!fgets(input, sizeof(input), stdin)) break;

        input[strcspn(input, "\n")] = 0;

        // Optional: remove semicolon
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == ';') input[len - 1] = '\0';

        if (strncmp(input, "EXIT", 4) == 0) {
            printf("Exiting.\n");
            break;

        } else if (strncmp(input, "INSERT", 6) == 0) {
            handle_insert(&table, input);

        } else if (strncmp(input, "SELECT", 6) == 0) {
            handle_select(&table, input);

        } else if (strncmp(input, "DELETE", 6) == 0) {
            handle_delete(&table, input);

        } else if (strncmp(input, "IMPORT", 6) == 0) {
            handle_import(&table, input);

        } else if (strncmp(input, "PRINT", 5) == 0) {
            handle_print(&table);

        } else {
            printf("Unrecognized command.\n");
            print_help();
        }
    }

    return 0;
}
