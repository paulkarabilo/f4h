#ifndef BUF_H
#define BUF_H

#include <ncurses.h>
#include "windows.h"

#define BUF_LENGTH 384

#define STRINGS_4_SIZE 15
#define STRINGS_5_SIZE 15

typedef struct {
    char* s;
    int len;
    char is_word;
    short was_selected;
} str;

typedef struct {
    str** cont;
    str* target;
    int length;
    int size;
    int cursor;
    short complexity;
    WINDOW* lc;
    WINDOW* rc;
} word_buffer;

void print_buf_to_win(word_buffer* b, WINDOW* win, int offset, int len);
void print_buf_to_left(word_buffer* b, int offset, int len);
void print_buf_to_right(word_buffer* b, int offset, int len);
void print_current_to_tty(word_buffer* b, WINDOW* win);
void buf_complexity(word_buffer* b, short complexity);
word_buffer* new_buf(int lh, int  lw, int ly, int lx, int rh, int rw, int ry, int rx);
void del_buf(word_buffer* b);
void navigate_buffer(word_buffer* b, char dir);
void navigate_buffer_char(word_buffer* b, char dir);
int get_str_diff(str* s1, str* s2);

#endif /* BUF_H */

