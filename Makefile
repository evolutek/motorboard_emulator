
all: build clean

build:
	gcc -o mb_emulator main.c

clean:
	rm -rf *.o
