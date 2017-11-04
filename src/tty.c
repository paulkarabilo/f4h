#include "../include/tty.h"

tty_window* new_tty(int h, int w, int y, int x) {
    tty_window* tw = malloc(sizeof(tty_window));
    tw->win = new_window(h, w, y, x);
    keypad(tw->win, TRUE);
    return tw;
}

int get_tty(tty_window* tw) {
    return wgetch(tw->win);
}

void del_tty(tty_window* tw) {
    del_window(tw->win);
    free(tw);
}