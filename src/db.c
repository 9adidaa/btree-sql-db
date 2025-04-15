#include <stdio.h>
#include <string.h>
#include "db.h"

void write_node(FILE* f, BTreeNode* node) {
    if (node == NULL) return;

    for (int i = 0; i < node->num_keys; i++) {
        fprintf(f, "%d,%s,%d\n", node->values[i].id, node->values[i].name, node->values[i].age);
    }

    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++) {
            write_node(f, node->children[i]);
        }
    }
}

void save_to_file(Table* table, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Error: cannot open file for writing.\n");
        return;
    }

    write_node(f, table->root);
    fclose(f);
}

void load_from_file(Table* table, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("No existing data to load.\n");
        return;
    }

    int id, age;
    char name[50];
    while (fscanf(f, "%d,%49[^,],%d\n", &id, name, &age) == 3) {
        Row row = {id, "", age};
        strncpy(row.name, name, sizeof(row.name) - 1);
        insert_node(table, id, row);
    }

    fclose(f);
}
