
all: build clean

build:
	gcc -o mb_emulator main.c interface.c

clean:
	rm -rf *.o
