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

void split_child(BTreeNode* parent, int index, BTreeNode* child) {
    BTreeNode* new_node = create_node(child->is_leaf);
    new_node->num_keys = MAX_KEYS / 2;

    // Copy higher half of keys/values from child to new_node
    for (int i = 0; i < MAX_KEYS / 2; i++) {
        new_node->keys[i] = child->keys[i + MAX_KEYS / 2 + 1];
        new_node->values[i] = child->values[i + MAX_KEYS / 2 + 1];
    }

    // Copy children if not a leaf
    if (!child->is_leaf) {
        for (int i = 0; i < MAX_KEYS / 2 + 1; i++) {
            new_node->children[i] = child->children[i + MAX_KEYS / 2 + 1];
        }
    }

    child->num_keys = MAX_KEYS / 2;

    // Shift parent's children to make room
    for (int i = parent->num_keys; i >= index + 1; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = new_node;

    // Shift parent's keys and values
    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
        parent->values[i + 1] = parent->values[i];
    }

    // Promote middle key from child to parent
    parent->keys[index] = child->keys[MAX_KEYS / 2];
    parent->values[index] = child->values[MAX_KEYS / 2];
    parent->num_keys++;
}

void insert_node(Table* table, int key, Row row) {
    if (table->root->num_keys == MAX_KEYS) {
    BTreeNode* old_root = table->root;
    BTreeNode* new_root = create_node(0);  // Not a leaf
    table->root = new_root;
    new_root->children[0] = old_root;

    // Split old root
    split_child(new_root, 0, old_root);

    // Decide where to insert the new key
    int i = (key > new_root->keys[0]) ? 1 : 0;
    // TODO: recursive_insert(new_root->children[i], key, row);
    return;
}

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
