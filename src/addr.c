#include "../include/addr.h"

/**
 * Create new ncurses sidebar/windows for hex addresses of rows
 * populate them with random hex numbers
 */
addr_windows* new_addr(int lh, int  lw, int ly, int lx, int rh, int rw, int ry, int rx) {
    addr_windows* a = malloc(sizeof(addr_windows));
    a->l = new_window(lh, lw, ly, lx);
    a->r = new_window(rh, rw, ry, rx);

    int r = 100 * (rand() %  100);
    for (int i = 0; i < 16; i++) {
        wprintw(a->l, "0X%04X", r);
        wprintw(a->r, "0X%04X", r + 12 * 16);
        r += 12;
    }

    wrefresh(a->l);
    wrefresh(a->r);

    return a;
}

void del_addr(addr_windows* a) {
    del_window(a->l);
    del_window(a->r);
    free(a);
}