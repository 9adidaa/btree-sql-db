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

    // TODO: Handle insert if root is not empty
}

// TODO: implement search_node
// TODO: implement delete_node
