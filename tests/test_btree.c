#include <assert.h>
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

int main() {
    test_insert_into_empty_tree();
    return 0;
}
void test_insert_multiple_in_leaf() {
    Table table = {0};

    Row r1 = {1, "Alice", 20};
    Row r2 = {3, "Bob", 22};
    Row r3 = {2, "Charlie", 21};

    insert_node(&table, r1.id, r1);
    insert_node(&table, r2.id, r2);
    insert_node(&table, r3.id, r3);

    assert(table.root->num_keys == 3);
    assert(table.root->keys[0] == 1);
    assert(table.root->keys[1] == 2);
    assert(table.root->keys[2] == 3);
}
