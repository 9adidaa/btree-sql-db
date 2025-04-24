#include <stdio.h>
#include <string.h>
#include "migration.h"
#include "db.h"

void handle_insert(Table* table, const char* input) {
    int id, age;
    char name[50];

    if (sscanf(input, "INSERT INTO table VALUES (%d, '%49[^']', %d)", &id, name, &age) == 3) {
        Row row = {id, "", age};
        strncpy(row.name, name, sizeof(row.name) - 1);

        if (search_node(table, id)) {
            printf("Error: A row with id %d already exists.\n", id);
        } else {
            insert_node(table, id, row);
            save_to_file(table, "data.db");
            printf("Inserted (%d, %s, %d)\n", id, row.name, row.age);
        }
    } else {
        printf("Syntax error in INSERT command.\n");
    }
}

void handle_select(Table* table, const char* input) {
    int id;
    if (sscanf(input, "SELECT * FROM table WHERE id=%d", &id) == 1) {
        Row* result = search_node(table, id);
        if (result) {
            printf("Found: (%d, %s, %d)\n", result->id, result->name, result->age);
        } else {
            printf("No row found with id %d.\n", id);
        }
    } else if (strncmp(input, "SELECT * FROM table", strlen("SELECT * FROM table")) == 0) {
        print_btree(table->root, 0);
    } else {
        printf("Syntax error in SELECT command.\n");
    }
}

void handle_delete(Table* table, const char* input) {
    int id;
    if (sscanf(input, "DELETE FROM table WHERE id=%d", &id) == 1) {
        delete_node(table, id);
        save_to_file(table, "data.db");
    } else {
        printf("Syntax error in DELETE command.\n");
    }
}

void handle_import(Table* table, const char* input) {
    char filename[100];
    if (sscanf(input, "IMPORT %99s", filename) == 1) {
        load_csv_into_table(table, filename);
        save_to_file(table, "data.db");
    } else {
        printf("Syntax error in IMPORT command. Usage: IMPORT filename.csv\n");
    }
}

void handle_print(Table* table) {
    print_btree(table->root, 0);
}

