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
