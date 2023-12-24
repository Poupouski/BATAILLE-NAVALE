CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
LIB_OBJ = $(filter-out main.o, $(OBJ))

all: exec

%.o: %.c header.h
	$(CC) -c $< -o $@

lib.a: $(LIB_OBJ)
	ar rcs $@ $^

exec: main.o lib.a
	$(CC) -fsanitize=address $^ -o $@

clean:
	rm -f *.o
	rm -f exec
	rm -f lib.a

doxygen:
	doxygen Doxyfile
	xdg-open html/index.html