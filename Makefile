
all: build clean

build:
	gcc -lutil -o mb_emulator main.c interface.c

clean:
	rm -rf *.o
