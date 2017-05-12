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
} word_buffer;

void print_buf_to_win(word_buffer* b, WINDOW* win, int offset, int len);
void print_current_to_tty(word_buffer* b, WINDOW* win);
void buf_complexity(word_buffer* b, char complexity);
word_buffer* new_buf();
void del_buf(word_buffer* b);
void navigate_buffer(word_buffer* b, char dir);
void navigate_buffer_char(word_buffer* b, char dir);

#endif /* BUF_H */

