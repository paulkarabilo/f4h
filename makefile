all:
	gcc -std=c99 main.c windows.c buf.c -o build/f4h -lncurses
