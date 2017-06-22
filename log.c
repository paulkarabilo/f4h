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

void del_log(log* l) {
    for (int i = 0; i < l->size; i++) {
        free(l->strings[i]);
    }
    free(l->strings);
    del_window(l->win);
    free(l);
}

void str2log(log* l, char* str) {
    
}