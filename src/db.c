#include <stdio.h>
#include <string.h>
#include "db.h"

void write_node_binary(FILE* f, BTreeNode* node) {
    if (node == NULL) return;

    for (int i = 0; i < node->num_keys; i++) {
        fwrite(&node->values[i], sizeof(Row), 1, f);
    }

    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++) {
            write_node_binary(f, node->children[i]);
        }
    }
}

void save_to_file(Table* table, const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (!f) {
        printf("Error: cannot open file for writing.\n");
        return;
    }

    write_node_binary(f, table->root);
    fclose(f);
}

void load_from_file(Table* table, const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) {
        printf("No binary data to load.\n");
        return;
    }

    Row row;
    while (fread(&row, sizeof(Row), 1, f) == 1) {
        insert_node(table, row.id, row);
    }

    fclose(f);
}

void load_csv_into_table(Table* table, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Error: couldn't open CSV file %s\n", filename);
        return;
    }

    int id, age;
    char name[50];
    while (fscanf(f, "%d,%49[^,],%d\n", &id, name, &age) == 3) {
        if (search_node(table, id) == NULL) {
            Row row = {id, "", age};
            strncpy(row.name, name, sizeof(row.name) - 1);
            insert_node(table, id, row);
        }
    }

    fclose(f);
    printf("CSV file %s loaded successfully.\n", filename);
}
