#include "include/buf.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

str* new_str(char* c, int is_word) {
    str* res = malloc(sizeof(str));
    res->s = malloc(strlen(c) + 1);
    strcpy(res->s, c);
    res->is_word = is_word;
    return res;
}

void del_str(str* res) {
    free(res->s);
    free(res);
}

buf* new_buf() {
    buf* res = malloc(sizeof(buf));
    res->size = 0;
    res->cont = malloc(sizeof(str*));
    res->length = 0;
    res->cursor = 0;
    return res;
}

void del_buf(buf* buf) {
    for (int i = 0; i < buf->size; i++) {
        del_str(buf->cont[i]);
    }
    free(buf->cont);
    free(buf);
}

void add_str_to_buf(buf* b, char* s, int is_word) {
    b->size++;
    b->cont = realloc(b->cont, sizeof(str*) * b->size);
    b->cont[b->size - 1] = new_str(s, is_word);
}

void print_str(str* s) {
    if (s->is_word) {
        printf("[%s]", s->s);
    } else {
        printf("%s", s->s);
    }
}

void print_buf(buf* b) {
    printf("Buffer <%p> (%i item(s)) \n", ((void *)b), b->size);
    for (int i = 0; i < b->size; i++) {
        printf("%i: ", i);
        print_str(b->cont[i]);
        printf("\n");
    }
}

void fill_buf(buf* b, char** strings, int size) {
    int c = 0;
    while(b->length < BUF_LENGTH) {
        b->size++;
        b->cont = realloc(b->cont, sizeof(str*) * b->size);
        if (BUF_LENGTH - b->length < 5) {
            //rand string
        } else {
            if (rand() % 6 == 1) {
                //something real;
            } else {
                //rand string
            }
        }
    }
}


int main(int argc, char** argv) {
    buf* b = new_buf(1);
    add_str_to_buf(b, "test", 1);
    add_str_to_buf(b, "&^*^", 0);
    add_str_to_buf(b, "foo bar", 1);
    print_buf(b);
    del_buf(b);
    str* s = new_str("test", 1);
    del_str(s);
    return 0;
}