#include "windows.h"

typedef struct {
    WINDOW* win;
    char** strings;
    u_int8_t size;
    int width;
    int height;
} log;

log* new_log(int h, int w, int y, int x);
void del_log(log* l);
void str2log(log* l, char* str);