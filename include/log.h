#ifndef BUF_H
#define BUF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "windows.h"

typedef struct {
    WINDOW* win;
    char** strings;
    size_t size;
    int width;
    int height;
} log;

log* new_log(int h, int w, int y, int x);
void delete_log(log* l);
void add_string_to_log(log* l, char* str);
void render_log(log* l);

#endif