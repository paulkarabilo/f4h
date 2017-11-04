#ifndef F4H_ADDR_H
#define F4H_ADDR_H

#include "win.h"
#include <stdlib.h>

typedef struct {
    WINDOW* l;
    WINDOW* r;
} addr_windows;

addr_windows* new_addr(int lh, int  lw, int ly, int lx, int rh, int rw, int ry, int rx);
void del_addr(addr_windows* a);

#endif