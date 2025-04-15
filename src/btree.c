#include "btree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

    for (int i = 0; i < MAX_KEYS / 2; i++) {
        new_node->keys[i] = child->keys[i + MAX_KEYS / 2 + 1];
        new_node->values[i] = child->values[i + MAX_KEYS / 2 + 1];
    }

    if (!child->is_leaf) {
        for (int i = 0; i < MAX_KEYS / 2 + 1; i++) {
            new_node->children[i] = child->children[i + MAX_KEYS / 2 + 1];
        }
    }

    child->num_keys = MAX_KEYS / 2;

    for (int i = parent->num_keys; i >= index + 1; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = new_node;

    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
        parent->values[i + 1] = parent->values[i];
    }

    parent->keys[index] = child->keys[MAX_KEYS / 2];
    parent->values[index] = child->values[MAX_KEYS / 2];
    parent->num_keys++;
}

void insert_non_full(BTreeNode* node, int key, Row row) {
    int i = node->num_keys - 1;

    if (node->is_leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            node->values[i + 1] = node->values[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->values[i + 1] = row;
        node->num_keys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        if (node->children[i]->num_keys == MAX_KEYS) {
            split_child(node, i, node->children[i]);

            if (key > node->keys[i]) {
                i++;
            }
        }

        insert_non_full(node->children[i], key, row);
    }
}

void insert_node(Table* table, int key, Row row) {
    if (table->root == NULL) {
        table->root = create_node(1);
        table->root->keys[0] = key;
        table->root->values[0] = row;
        table->root->num_keys = 1;
        table->num_rows++;
        return;
    }

    if (table->root->num_keys == MAX_KEYS) {
        BTreeNode* old_root = table->root;
        BTreeNode* new_root = create_node(0);
        table->root = new_root;
        new_root->children[0] = old_root;

        split_child(new_root, 0, old_root);

        int i = (key > new_root->keys[0]) ? 1 : 0;
        insert_non_full(new_root->children[i], key, row);
    } else {
        insert_non_full(table->root, key, row);
    }

    table->num_rows++;
}

Row* search_node(Table* table, int key) {
    if (table->root == NULL) return NULL;

    BTreeNode* current = table->root;

    while (1) {
        int i = 0;
        while (i < current->num_keys && key > current->keys[i]) {
            i++;
        }

        // If found, return the value
        if (i < current->num_keys && key == current->keys[i]) {
            return &current->values[i];
        }

        // If it's a leaf, key doesn't exist
        if (current->is_leaf) {
            return NULL;
        }

        // Go deeper
        current = current->children[i];
    }
}

// TODO: implement delete_node
