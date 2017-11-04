#ifndef F4H_WIN_H
#define F4H_WIN_H


#include <ncurses.h>

WINDOW* new_window(int h, int w, int y, int x);
void del_window(WINDOW* win);

#endif /* WINDOWS_H */

