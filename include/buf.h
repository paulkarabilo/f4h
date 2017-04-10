#ifndef BUF_H
#define BUF_H

#define BUF_LENGTH 384

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


#endif /* BUF_H */

