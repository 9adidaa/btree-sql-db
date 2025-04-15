#ifndef DB_H
#define DB_H

#include "btree.h"

void save_to_file(Table* table, const char* filename);
void load_from_file(Table* table, const char* filename);

#endif
