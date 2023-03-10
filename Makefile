CC=g++
CFLAGS=-Wall -Wextra -fsanitize=address
LFLAGS=
SRC=main.cpp
INC=any.hpp

run: $(SRC) $(INC)
	$(CC) $(CFLAGS) -o any $(SRC) $(LFLAGS)
	./any
