#ifndef F4H_TTY_H
#define F4H_TTY_H
#include "win.h"
#include <stdlib.h>

typedef struct {
    WINDOW* win;
} tty_window;

tty_window* new_tty(int h, int w, int y, int x);
int get_tty(tty_window* tw);
void del_tty(tty_window* tw);

#endif