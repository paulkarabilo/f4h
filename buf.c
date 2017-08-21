#include "include/buf.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>

char* strings_4[] = {
    "TEST", "FILL", "BUFF", "DOES", "WANT",
    "BEEP", "WEED", "ALSO", "MUST", "WILL",
    "CONS", "WHAT", "WHEN", "COAT", "GOAT"
};

char* strings_5[] = {
    "SPEAK", "SHARD", "COULD", "WOULD", "GUARD",
    "SPLIT", "SPEAR", "TREES", "POWER", "TABLE",
    "CHAIR", "BREAK", "CRANE", "SPACE", "CAMEL"
};

/*
 * Returns string of random characters of a given size
*/
char* rand_string(int size) {
    char* s = malloc(size + 1);
    if (s) {
        const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()|?/><.,{}[]~";
        if (size) {
            --size;
            for (size_t n = 0; n < size; n++) {
                int key = rand() % (int) (sizeof charset - 1);
                s[n] = charset[key];
            }
            s[size] = '\0';
        }
    }
    return s;
}

str* new_str(char* c, int is_word) {
    str* res = malloc(sizeof(str));
    res->s = malloc(strlen(c) + 1);
    res->len = strlen(c);
    strcpy(res->s, c);
    res->is_word = is_word;
    return res;
}

void del_str(str* res) {
    free(res->s);
    free(res);
}

word_buffer* new_buf() {
    word_buffer* res = malloc(sizeof(word_buffer));
    res->size = 0;
    res->cont = malloc(sizeof(str*));
    res->length = 0;
    res->cursor = 0;
    return res;
}

/*
 * Retuns amount of chars that are different between 2 strings
 */
int get_str_diff(str* s1, str* s2) {
    if (s1->len != s2->len) {
        return -1;
    }
    int matches = 0;
    for (int i = 0; i < s1->len; i++) {
        if (tolower(s1->s[i]) == tolower(s2->s[i])) {
            matches++;
        }
    }
    return s1->len - matches;
}

void del_buf(word_buffer* buf) {
    for (int i = 0; i < buf->size; i++) {
        del_str(buf->cont[i]);
    }
    if (buf->target != NULL) {
        del_str(buf->target);
    }
    free(buf->cont);
    free(buf);
}

void add_str_to_buf(word_buffer* b, char* s, int is_word) {
    b->size++;
    b->cont = realloc(b->cont, sizeof(str*) * b->size);
    b->cont[b->size - 1] = new_str(s, is_word);
    b->length += b->cont[b->size - 1]->len;
}

char** shuffle_strings(char** strings, size_t size) {
    char** shuffled = malloc(sizeof(char*) * size);
    size_t i = 0;
    for(; i < size; i++) {
        shuffled[i] = malloc(sizeof(char));
        strcpy(shuffled[i], strings[i]);
    }
    for (i = 0; i < size - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
        char* t = shuffled[j];
        shuffled[j] = shuffled[i];
        shuffled[i] = t;
    }
    return shuffled;
}

void set_target_word(word_buffer* b, char* target) {
    b->target = new_str(target, 1);
}

void del_shuffled_strings(char** strings, int size) {
    for (unsigned int i = 0; i < size; i++) {
        free(strings[i]);
    }
    free(strings);
}


void fill_buf(word_buffer* b, char** strings, int size, short complexity) {
    char** shuffled = shuffle_strings(strings, size);
    int cursor = 0;
    while(b->length < BUF_LENGTH) {
        if (BUF_LENGTH - b->length < 5) {
            char* s = rand_string(BUF_LENGTH - b->length + 1);
            add_str_to_buf(b, s, 0);
            free(s);
        } else {
            if ((cursor < size - 1) && (rand() % 5) == 0) {
                cursor++;
                add_str_to_buf(b, shuffled[cursor], 1);
            } else {
                char* s = rand_string(2 + (rand() % 5));
                add_str_to_buf(b, s, 0);
                free(s);
            }
        }
    }
    b->complexity = complexity;
    set_target_word(b, shuffled[rand() % cursor]);
    del_shuffled_strings(shuffled, size);
}

/**
 * Make sure that buffer cursor stays inside buffer
 */
void clamp_buffer_cursor(word_buffer* b) {
    if (b->cursor < 0) b->cursor = 0;
    if (b->cursor >= b->size) b->cursor = b->size - 1;
}

/**
 * Simple buffer navigation, 1 word forward or backward
 */
void navigate_buffer(word_buffer* b, char dir) {
    b->cursor = b->cursor + dir;
    clamp_buffer_cursor(b);
}

/**
 * Navigate buffer forward or backward certain amount of characters
 */
void navigate_buffer_char(word_buffer* b, char dir) {
    str* current = b->cont[b->cursor];
    uint8_t _cursor = 0;
    while (dir != 0) {
        if (_cursor >= current->len) {
            _cursor = 0;
            b->cursor = b->cursor + (dir < 0 ? -1 : 1);
            clamp_buffer_cursor(b);
        }
        _cursor += 1;
        dir = dir + (dir > 0 ? -1 : 1);
    }
}

/**
 * Helper method to create buffer of given complexity
 * from predefined list of strings
 * (complexity simply means length of word in buffer)
 */
void buf_complexity(word_buffer* b, short complexity) {
    if (complexity == 4) {
        fill_buf(b, strings_4, STRINGS_4_SIZE, complexity);
    } else if (complexity == 5) {
        fill_buf(b, strings_5, STRINGS_5_SIZE, complexity);
    }
}

void print_current_to_tty(word_buffer* b, WINDOW* win) {
    str* s = b->cont[b->cursor];
    wclear(win);
    if (s->is_word) {
        wprintw(win, "> %s", s->s);
    } else {
        wprintw(win, "> ");
    }
}

/*
 * Prints part of word buffer (starting at given offset, of given length)
 * to ncurses window
 */
void print_buf_to_win(word_buffer* b, WINDOW* win, int offset, int len) {
    int cursor = 0;
    int string_cursor = 0;
    int selected = (b->cursor == 0) ? 1 : 0;
    if (selected) {
        wattron(win, COLOR_PAIR(1));
    }
    str* s = b->cont[cursor];
    for (int i = 0; i < b->length; i++) {
        if (i >= offset && i < offset + len) {
            wprintw(win, "%c", s->s[string_cursor]);   
        }
        string_cursor++;
        if (string_cursor >= s->len) {
            if ((++cursor) > b->length) return;
            if (cursor == b->cursor && !selected) {
                selected = 1;
                wattron(win, COLOR_PAIR(1));
            }
            if (cursor != b->cursor && selected) {
                selected = 0;
                wattroff(win, COLOR_PAIR(1));
            }
            s = b->cont[cursor];
            string_cursor = 0;
        }
    }
    wrefresh(win);
}