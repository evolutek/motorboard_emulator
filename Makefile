
all: build clean

build:
	gcc -lutil -lpthread -o mb_emulator main.c  command.c queue.c interface.c

clean:
	rm -rf *.o
