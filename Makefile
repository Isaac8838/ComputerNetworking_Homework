CC = gcc
CFLAG = -g -m32
INC = -Iinclude

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, obj/%.o, $(SRCS))

.PHONY: clean all

all: client

client: $(OBJS)
	@$(CC) $^ -m32 -o $@

obj/%.o: src/%.c
	$(CC) $(CFLAG) $(INC) -c -o $@ $<

clean:
	@rm obj/*.o ./client