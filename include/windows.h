#ifndef WINDOWS_H
#define WINDOWS_H


#include <ncurses.h>

WINDOW* new_window(int h, int w, int y, int x);
void del_window(WINDOW* win);

#endif /* WINDOWS_H */

