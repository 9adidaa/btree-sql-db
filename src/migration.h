#ifndef MIGRATION_H
#define MIGRATION_H

#include "btree.h"

void handle_insert(Table* table, const char* input);
void handle_select(Table* table, const char* input);
void handle_delete(Table* table, const char* input);
void handle_import(Table* table, const char* input);
void handle_print(Table* table);

#endif

