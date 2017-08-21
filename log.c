#include "include/log.h"

log_window* new_log(int h, int w, int y, int x) {
    log_window* l = malloc(sizeof(log_window));
    l->size = 0;
    l->strings = malloc(sizeof(char*));
    l->win = new_window(h, w, y, x);
    l->width = w;
    l->height = h;
    return l;
}

void delete_log(log_window* l) {
    for (int i = 0; i < l->size; i++) {
        free(l->strings[i]);
    }
    free(l->strings);
    del_window(l->win);
    free(l);
}

void add_string_to_log(log_window* l, char* str) {
    char* s = malloc(strlen(str) + 1);
    l->size++;
    l->strings = realloc(l->strings, sizeof(char*) * l->size);
    strcpy(s, str);
    l->strings[l->size - 1] = s;
}

void render_log(log_window* l) {
    uint8_t nrows = 0;
    uint8_t i;
    wclear(l->win);
    for (i = 0; i < l->size; i++) {
        char* s = l->strings[i];
        size_t len = strlen(s);
        int rows = len / l->width;
        if (rows == 0) rows = 1;
        nrows += rows;
    }
    wmove(l->win, l->height - nrows, 0);
    for (i = 0; i < l->size; i++) {
        char* s = l->strings[i];
        size_t len = strlen(s);
        int mod = len % l->width;
        char* fmt;
        if (mod == 0) {
            fmt = "%s";
        } else {
            fmt = "%s\n";
        }
        wprintw(l->win, fmt, l->strings[i]);
    }
    wrefresh(l->win);
}