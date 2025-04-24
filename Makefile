CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRC = src/main.c src/btree.c src/db.c src/migration.c
OBJ = $(SRC:.c=.o)
BIN = btree_db

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c files to .o files (object files)
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)
