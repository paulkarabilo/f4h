#include "include/buf.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *rand_string(size_t size) {
    char* s = malloc(size + 1);
    if (s) {
         const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()|\?/><.,{}[]~";
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

char* strings[] = {
    "TEST", "FILL", "BUFF", "DOES", "WANT",
    "BEEP", "WEED", "ALSO", "MUST", "WILL",
    "CONS", "WHAT", "WHEN", "COAT", "GOAT"
};

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
    printf("ADDING %s\n", s);
    b->cont = realloc(b->cont, sizeof(str*) * b->size);
    b->cont[b->size - 1] = new_str(s, is_word);
    b->length += b->cont[b->size - 1]->len;
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
    while(b->length < BUF_LENGTH) {
        if (BUF_LENGTH - b->length < 5) {
            printf("FIN ");
            add_str_to_buf(b, rand_string(BUF_LENGTH - b->length + 1), 0);
        } else {
            if (rand() % 6 == 1) {
                printf("WORD ");
                add_str_to_buf(b, strings[rand() % (int)(size - 1)], 1);
                //something real;
            } else {
                printf("RAND ");
                add_str_to_buf(b, rand_string(1 + rand() % 5), 0);
                //rand string
            }
        }
    }
}


int main(int argc, char** argv) {
    buf* b = new_buf(1);
    fill_buf(b, strings, 15);
    print_buf(b);
    del_buf(b);
    str* s = new_str("test", 1);
    del_str(s);
    return 0;
}