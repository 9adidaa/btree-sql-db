#include "btree.h"
#include <stdlib.h>
#include <string.h>
#include "btree.h"

BTreeNode* create_node(int is_leaf) {
    BTreeNode* node = malloc(sizeof(BTreeNode));
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void insert_node(Table* table, int key, Row row) {
    if (table->root == NULL) {
        table->root = create_node(1); // 1 = true, leaf
        table->root->keys[0] = key;
        table->root->values[0] = row;
        table->root->num_keys = 1;
        table->num_rows++;
        return;
    }

    
    if (table->root->num_keys < MAX_KEYS) {
        BTreeNode* root = table->root;

        // Find position to insert key (keep sorted order)
        int i = root->num_keys - 1;
        while (i >= 0 && key < root->keys[i]) {
            root->keys[i + 1] = root->keys[i];
            root->values[i + 1] = root->values[i];
            i--;
        }

        // Insert new key and value
        root->keys[i + 1] = key;
        root->values[i + 1] = row;
        root->num_keys++;
        table->num_rows++;
        return;
    }

}

// TODO: implement search_node
// TODO: implement delete_node
