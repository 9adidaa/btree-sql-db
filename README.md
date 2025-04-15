# BTree SQL Database (ESGI 3SI Project)

## Author
- **Name**: Mohamed Mokdad
- **Class**: 3SI (rentree de janvier)

## Description
This project implements a simple SQL-like in-memory database using a B-tree structure for indexing and fast lookups. It supports basic commands such as:

- `INSERT INTO table VALUES (id, 'name', age)`
- `SELECT * FROM table WHERE id=...`
- `DELETE FROM table WHERE id=...`
- `PRINT` to display the tree structure
- `EXIT` to quit the database

The data is persisted to disk between sessions using a file named `data.db`.

## Build Instructions

```bash
make
./btree_db
```

## Compiler Flags Used

- `-Wall -Wextra -Werror` : to enforce clean and secure code
- `-g -fsanitize=address` : for debugging and memory error detection

## Notes

- IDEs are not used. The project is built and run from the command line.
- The code is modular and separated into multiple `.c` and `.h` files.
- Commits are made continuously during development.
