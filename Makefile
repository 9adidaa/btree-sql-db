CC=gcc
CFLAGS=-Wall -Wextra -Werror -g -fsanitize=address

SRC=src/main.c src/btree.c src/db.c
OBJ=$(SRC:.c=.o)
BIN=btree_db

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for building .o files from .c files
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)
