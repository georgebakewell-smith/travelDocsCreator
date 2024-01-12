CC = gcc
CFLGS = -g -Wall
SRC = src
OBJ = obj
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/*.c, $(OBJ)/*.o, $(SRCS))
BINDIR = bin
BIN = $(BINDIR)/shortbread

all: $(BIN)


$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLGS) -c $< -o $@



clean:
	rm -f bin/* $(OBJ)/*
