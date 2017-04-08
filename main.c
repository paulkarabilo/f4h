#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include "include/windows.h"

#define BUF_LENGTH 384

typedef struct {
    char* s;
    int len;
    char is_word;
} str;

typedef struct {
    str** cont;
    int length;
    int size;
    int cursor;
} buf;

char* strings[] = {
    "TEST", "FILL", "BUFF", "DOES", "WANT",
    "BEEP", "WEED", "ALSO", "MUST", "WILL",
    "CONS", "WHAT", "WHEN", "COAT", "GOAT"
};

str* new_str(char* c, int is_word) {
    str* res = malloc(sizeof(str));
    res->s = malloc(strlen(c) + 1);
    strcpy(res->s, c);
    res->is_word = is_word;
    return res;
}

void del_str(str* res) {
    free(res->s);
    free(res);
}

buf* new_buf(int length) {
    buf* res = malloc(sizeof(buf));
    res->size = 0;
    res->cont = malloc(sizeof(str*));
    res->length = 0;
    res->cursor = 0;
    return res;
}

void del_buf(buf* buf) {
    for (int i = 0; i < buf->length; i++) {
        free(buf->cont[i]);
    }
    free(buf->cont);
    free(buf);
}

void fill_buf(buf* b, char** strings, int size) {
    int c = 0;
    while(b->length < BUF_LENGTH) {
        b->size++;
        b->cont = realloc(b->cont, sizeof(str*) * b->size);
        if (BUF_LENGTH - b->length < 5) {
            //rand string
        } else {
            if (rand() % 6 == 1) {
                //something real;
            } else {
                //rand string
            }
        }
    }
}

void header(WINDOW* hdr) {
    wprintw(hdr, "Welcome to ***\n");
    wprintw(hdr, "Password required\n\n");
    wprintw(hdr, "Attempts remaining: | | | |\n\n");
    wrefresh(hdr);
}

void addr(WINDOW* l, WINDOW* r) {
    int a = 100 * (rand() %  100);
    for (int i = 0; i < 16; i++) {
        wprintw(l, "0X%04X", a);
        a += 12;
    }
    for (int i = 0; i < 16; i++) {
        wprintw(r, "0X%04X", a);
        a += 12;
    }
    wrefresh(l);
    wrefresh(r);
}

void loop(WINDOW* l, WINDOW* r) {
    int ch = wgetch(l);
    while (ch != 27) {
        printw("%c\n", ch);
        refresh();
        ch = wgetch(r);
    }
}

void randc(WINDOW* lc, WINDOW* rc) {
    for (int i = 0; i < 12 * 16; i++) {
        char c = rand() & 0x7F;
        wprintw(lc, "%c", c);
    }
    for (int i = 0; i < 12 * 16; i++) {
        char c = rand() & 0x7F;
        wprintw(rc, "%c", c);
    }
    wrefresh(lc);
    wrefresh(rc);
}

int main(int argc, char** argv) {
    srand(time(NULL));
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    WINDOW* hdr = new_window(5, 80, 0, 0);
    WINDOW* l = new_window(16, 6, 6, 0);
    WINDOW* r = new_window(16, 6, 6, 21);
    WINDOW* lc = new_window(16, 12, 6, 7);
    WINDOW* rc = new_window(16, 12, 6, 28);
    WINDOW* tty = new_window(21, 10, 0, 41);

    header(hdr);
    addr(l, r);
    randc(lc, rc);
    loop(l, r);

    del_window(tty);
    del_window(rc);
    del_window(lc);
    del_window(r);
    del_window(l);
    del_window(hdr);
    
    endwin();
    return (EXIT_SUCCESS);
}