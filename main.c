#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

WINDOW* new_window(int h, int w, int y, int x) {
    WINDOW* win = newwin(h, w, y, x);
    box(win, 0, 0);
    wrefresh(win);
    return win;
}

void del_window(WINDOW* win) {
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
}

void header() {
    printw("Welcome to ***\n");
    printw("Password required\n");
    printw("Attempts remaining: | | | |\n");
}

void loop() {
    int ch = getch();
    while (ch != 27) {
        if (ch == KEY_RIGHT) {
            printw("right");
        } else if (ch == KEY_LEFT) {
            printw("left");
        } else if (ch == KEY_DOWN) {
            printw("down");
        } else if (ch == KEY_UP) {
            printw("up");
        } else if (ch == KEY_ENTER) {
            printw("enter");
        } else {
            printw("%c", ch);
        }
        printw("\n");
        refresh();
        ch = getch();
    }
}

int main(int argc, char** argv) {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    header();
    loop();
    
    endwin();
    return (EXIT_SUCCESS);
}

