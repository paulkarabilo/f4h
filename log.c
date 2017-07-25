#include "include/log.h"

log* new_log(int h, int w, int y, int x) {
    log* l = malloc(sizeof(log));
    l->size = 0;
    l->strings = malloc(sizeof(char*));
    l->win = new_window(h, w, y, x);
    l->width = w;
    l->height = h;
    return l;
}

void delete_log(log* l) {
    for (int i = 0; i < l->size; i++) {
        free(l->strings[i]);
    }
    free(l->strings);
    del_window(l->win);
    free(l);
}

void add_string_to_log(log* l, char* str) {
    char* s = malloc(strlen(str) + 1);
    l->size++;
    l->strings = realloc(l->strings, sizeof(char*) * l->size);
    strcpy(s, str);
    l->strings[l->size - 1] = s;
}

void render_log(log* l) {
    uint8_t nrows = 0;
    uint8_t i;
    wclear(l->win);
    for (i = 0; i < l->size; i++) {
        nrows += strlen(l->strings[i]) / l->width;
    }
    wmove(l->win, nrows, 0);
    for (i = 0; i < l->size; i++) {
        wprintw(l->win, l->strings[i]);
    }
    wrefresh(l->win);
}