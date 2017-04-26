#ifndef BUF_H
#define BUF_H

#include <ncurses.h>

#define BUF_LENGTH 384

#define STRINGS_4_SIZE 15
#define STRINGS_5_SIZE 15

typedef struct {
    char* s;
    int len;
    char is_word;
} str;

typedef struct {
    str** cont;
    int length;
    int size;
    int cursor;
} buf;

void print_buf_to_win(buf* b, WINDOW* win, int offset, int len);
void print_current_to_tty(buf* b, WINDOW* win);
void buf_complexity(buf* b, char complexity);
buf* new_buf();
void del_buf(buf* b);
void navigate_buffer(buf* b, char dir);
void navigate_buffer_char(buf* b, char dir);

#endif /* BUF_H */

