#include <assert.h>
#include <stdio.h> 
#include "../src/btree.h"
#include <string.h>   // for strcmp
#include <stddef.h>   // for NULL

void test_insert_into_empty_tree() {
    Table table = {0};
    Row r = {1, "Mohamed", 23};

    insert_node(&table, r.id, r);

    assert(table.root != NULL);
    assert(table.root->num_keys == 1);
    assert(table.root->keys[0] == 1);
    assert(strcmp(table.root->values[0].name, "Mohamed") == 0);
}
void test_split_root_node() {
    Table table = {0};

    // Insert 4 rows (triggers root split at 4th insert)
    Row r1 = {10, "A", 20};
    Row r2 = {20, "B", 21};
    Row r3 = {30, "C", 22};
    Row r4 = {40, "D", 23};  // This one causes root to split

    insert_node(&table, r1.id, r1);
    insert_node(&table, r2.id, r2);
    insert_node(&table, r3.id, r3);
    insert_node(&table, r4.id, r4);

    // Assertions
    assert(table.root != NULL);
    assert(table.root->is_leaf == 0);  // Root should now be internal
    assert(table.root->num_keys == 1); // One promoted key
    assert(table.root->keys[0] == 20); // Middle key promoted

    BTreeNode* left = table.root->children[0];
    BTreeNode* right = table.root->children[1];

    assert(left->num_keys == 1);
    assert(left->keys[0] == 10);

    assert(right->num_keys == 2);
    assert(right->keys[0] == 30);
    assert(right->keys[1] == 40);
}

void test_search_node() {
    Table table = {0};

    Row r1 = {1, "Alice", 20};
    Row r2 = {2, "Bob", 21};
    Row r3 = {3, "Charlie", 22};

    insert_node(&table, r1.id, r1);
    insert_node(&table, r2.id, r2);
    insert_node(&table, r3.id, r3);

    Row* result = search_node(&table, 2);
    assert(result != NULL);
    assert(strcmp(result->name, "Bob") == 0);

    Row* not_found = search_node(&table, 99);
    assert(not_found == NULL);
}

void test_delete_leaf_node() {
    Table table = {0};

    Row r1 = {1, "Alice", 20};
    Row r2 = {2, "Bob", 21};
    Row r3 = {3, "Charlie", 22};

    insert_node(&table, r1.id, r1);
    insert_node(&table, r2.id, r2);
    insert_node(&table, r3.id, r3);

    delete_node(&table, 2);

    Row* result = search_node(&table, 2);
    assert(result == NULL);

    assert(table.root->num_keys == 2);
}

int main() {
    Table table = {0};

    insert_node(&table, 10, (Row){10, "A", 20});
    insert_node(&table, 20, (Row){20, "B", 21});
    insert_node(&table, 30, (Row){30, "C", 22});
    insert_node(&table, 40, (Row){40, "D", 23});
    insert_node(&table, 50, (Row){50, "E", 24});
    insert_node(&table, 25, (Row){25, "F", 25});

    printf("======= B-Tree =======\\n");
    print_btree(table.root, 0);
    printf("======================\\n");

    return 0;
}



