#ifndef F4H_HDR_H
#define F4H_HDR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "win.h"

typedef struct hdr_window {
    WINDOW* win;
} hdr_window;

hdr_window* new_hdr(int h, int w, int y, int x);
void delete_hdr(hdr_window* h);
void print_hdr(hdr_window* h, int attempts);
void print_hdr_game_over(hdr_window* h);
void print_hdr_win(hdr_window* h);

#endif