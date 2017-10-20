all:
	gcc -std=c99 src/main.c src/windows.c src/buf.c src/hdr.c src/log.c -o build/f4h -lncurses
debug:
	gcc -g -std=c99 src/main.c src/windows.c src/buf.c src/hdr.c src/log.c -o build/f4h-debug -lncurses