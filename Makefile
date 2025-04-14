CC=gcc
CFLAGS=-Wall -Wextra -Werror -g -fsanitize=address

SRC=src/main.c src/btree.c src/db.c
OBJ=$(SRC:.c=.o)
BIN=btree_db

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(BIN)
