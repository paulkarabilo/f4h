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

void print_buf_to_windows(WINDOW* lc, WINDOW* rc, WINDOW* tty, word_buffer *b) {
    wclear(lc);
    wclear(rc);
    print_current_to_tty(b, tty);
    print_buf_to_win(b, lc, 0, 192);
    print_buf_to_win(b, rc, 192, 192);
}

void print_log(WINDOW* log, char* word, char matches) {
    wprintw(log, "%s\n", word);
    if (matches) {
        wprintw(log, "Password accepted\n");
    } else {
        wprintw(log, "Password invalid\n");
        wprintw(log, "Matches 3/7\n");
        wprintw(log, "3 attempts remaining\n");
    }
    wrefresh(log);
}

void loop(WINDOW* lc, WINDOW* rc, WINDOW* tty, WINDOW* log, WINDOW* hdr, word_buffer* b) {
    int ch = wgetch(tty);
    while (ch != 27) {
        switch(ch) {
            case KEY_LEFT:
                navigate_buffer(b, -1);
                print_buf_to_windows(lc, rc, tty, b);
                break;
            case KEY_RIGHT:
                navigate_buffer(b, 1);
                print_buf_to_windows(lc, rc, tty, b);
                break;
            case KEY_UP:
                navigate_buffer_char(b, -12);
                print_buf_to_windows(lc, rc, tty, b);
                break;
            case KEY_DOWN:
                navigate_buffer_char(b, 12);
                print_buf_to_windows(lc, rc, tty, b);
                break;
            case 10: //Enter key only works like this
                wprintw(log, "%s\n", b->cont[b->cursor]->s);
                wrefresh(log);
                break;
        }
        ch = wgetch(tty);
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    initscr();
    if (has_colors() == FALSE) {
        endwin();
        printf("Terminal does not support colors, aborting...\n");
        exit(1);
    }
    cbreak();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    keypad(stdscr, TRUE);
    word_buffer* b = new_buf();
    buf_complexity(b, 4);
    WINDOW* hdr = new_window(5, 80, 0, 0);
    WINDOW* l = new_window(16, 6, 6, 0);
    WINDOW* r = new_window(16, 6, 6, 21);
    WINDOW* lc = new_window(16, 12, 6, 7);
    WINDOW* rc = new_window(16, 12, 6, 28);
    WINDOW* tty = new_window(1, 10, 21, 41);
    WINDOW* log = new_window(15, 10, 6, 41);
    keypad(tty, TRUE);
    header(hdr);
    addr(l, r);
    print_buf_to_windows(lc, rc, tty, b);
    loop(lc, rc, tty, log, hdr, b);

    del_window(tty);
    del_window(log);
    del_window(rc);
    del_window(lc);
    del_window(r);
    del_window(l);
    del_window(hdr);
    
    endwin();
    del_buf(b);
    return (EXIT_SUCCESS);
}