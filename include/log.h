#ifndef F4H_LOG_H
#define F4H_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "win.h"

typedef struct log_window {
    WINDOW* win;
    char** strings;
    size_t size;
    int width;
    int height;
} log_window;

log_window* new_log(int h, int w, int y, int x);
void delete_log(log_window* l);
void add_string_to_log(log_window* l, char* str);
void render_log(log_window* l);

#endif