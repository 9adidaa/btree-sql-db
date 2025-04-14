# Simple B-Tree SQL-Like Database

## Author
- Mohamed Mokdad – ESGI 3SI

## Description
A small database engine written in C that supports basic SQL-like commands (`INSERT`, `SELECT`, `DELETE`) using a B-tree for internal storage.

## Build
```bash
make
```

## Run
```bash
./btree_db
```

## Features
- B-tree structure with insert/search/delete
- Simple command parser
- Disk persistence (to be added)
- Tests using asserts

## Compiler
- gcc with `-Wall -Wextra -Werror -g -fsanitize=address`
