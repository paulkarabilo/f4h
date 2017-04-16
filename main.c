#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include "include/windows.h"
#include "include/buf.h"

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
        wprintw(r, "0X%04X", a + 12 * 16);
        a += 12;
    }
    wrefresh(l);
    wrefresh(r);
}

void loop(WINDOW* lc, WINDOW* rc) {
    int ch = wgetch(lc);
    while (ch != 27) {
        printw("%c\n", ch);
        refresh();
        ch = wgetch(lc);
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    buf* b = new_buf();
    buf_complexity(b, 4);
    WINDOW* hdr = new_window(5, 80, 0, 0);
    WINDOW* l = new_window(16, 6, 6, 0);
    WINDOW* r = new_window(16, 6, 6, 21);
    WINDOW* lc = new_window(16, 12, 6, 7);
    WINDOW* rc = new_window(16, 12, 6, 28);
    WINDOW* tty = new_window(21, 10, 0, 41);

    header(hdr);
    addr(l, r);
    print_buf_to_win(b, lc, 0, 192);
    print_buf_to_win(b, rc, 192, 192);
    loop(l, r);

    del_window(tty);
    del_window(rc);
    del_window(lc);
    del_window(r);
    del_window(l);
    del_window(hdr);
    
    endwin();
    del_buf(b);
    return (EXIT_SUCCESS);
}