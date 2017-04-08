#include "include/windows.h"

WINDOW* new_window(int h, int w, int y, int x) {
    WINDOW* win = newwin(h, w, y, x);
    wrefresh(win);
    return win;
}

void del_window(WINDOW* win) {
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
}