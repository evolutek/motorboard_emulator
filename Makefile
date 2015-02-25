CC=gcc
CFLAGS=-lutil -lpthread 
LDFLAGS=-lutil -lpthread
EXEC=mb_emu
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

mb_emu: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: command.h interface.h queue.h robot.h colored_print.h

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $<

.PHONY: clean mrpoper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

