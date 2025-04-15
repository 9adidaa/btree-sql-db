#ifndef BTREE_H
#define BTREE_H

#define MAX_KEYS 3
#define MAX_CHILDREN 4

typedef struct {
    int id;
    char name[50];
    int age;
} Row;

typedef struct BTreeNode {
    int is_leaf;
    int num_keys;
    int keys[MAX_KEYS];
    Row values[MAX_KEYS];
    struct BTreeNode* children[MAX_CHILDREN];
} BTreeNode;

typedef struct {
    BTreeNode* root;
    int num_rows;
} Table;

// Function declarations
BTreeNode* create_node(int is_leaf);
void insert_node(Table* table, int key, Row row);
Row* search_node(Table* table, int key);
void delete_node(Table* table, int key);
void print_btree(BTreeNode* node, int level);


#endif
