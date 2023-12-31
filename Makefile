
CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=-lSDL2 -lm

OBJ_FILES=main.c.o draw.c.o raycast.c.o rotation.c.o
OBJS=$(addprefix obj/, $(OBJ_FILES))

BIN=raycasting.out

.PHONY: clean all run

# -------------------------------------------

all: $(BIN)

run: $(BIN)
	./$<

clean:
	rm -f $(OBJS)
	rm -f $(BIN)

# -------------------------------------------

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

obj/%.c.o : src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

