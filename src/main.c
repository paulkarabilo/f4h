#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include "../include/log.h"
#include "../include/hdr.h"
#include "../include/addr.h"
#include "../include/tty.h"
#include "../include/buf.h"

void print_buffer_to_windows(word_buffer *b, tty_window* tty) {
    print_current_to_tty(b, tty);
    print_buf_to_left(b, 0, 192);
    print_buf_to_right(b, 192, 192);
}

int check_guess(word_buffer* b, log_window *l, int attempts) {
    int diff = get_str_diff(b->target, b->cont[b->cursor]);
    b->cont[b->cursor]->was_selected = 1;
    add_string_to_log(l, b->cont[b->cursor]->s);
    if (diff == 0) {
        add_string_to_log(l, "Entry OK!");
        render_log(l);
        return 1;
    } else {
        char match[12];
        add_string_to_log(l, "Entry denied");
        snprintf(match, 12, "%d/%d correct", b->complexity - diff, b->complexity);
        add_string_to_log(l, match);
        render_log(l);
        return 0;
    }
}

void main_loop(tty_window* tty, log_window* game_log, hdr_window* hdr, word_buffer* b) {
    int attempts = 4;
    print_hdr(hdr, attempts);
    int ch = get_tty(tty);
    while (ch != 27 && attempts > 0) {
        switch(ch) {
            case KEY_LEFT:
                navigate_buffer_word(b, -1);
                print_buffer_to_windows(b, tty);
                break;
            case KEY_RIGHT:
                navigate_buffer_word(b, 1);
                print_buffer_to_windows(b, tty);
                break;
            case KEY_UP:
                navigate_buffer_char(b, -14);
                print_buffer_to_windows(b, tty);
                break;
            case KEY_DOWN:
                navigate_buffer_char(b, 14);
                print_buffer_to_windows(b, tty);
                break;
            case 10: //Enter key only works like this
                if (b->cont[b->cursor]->is_word && !(b->cont[b->cursor]->was_selected)) {
                    attempts--;
                    if (check_guess(b, game_log, attempts)) {
                        print_hdr_win(hdr);
                        attempts = 0;
                        ch = get_tty(tty);
                        return;
                    } else if (attempts == 0) {
                        print_hdr_game_over(hdr);
                        ch = get_tty(tty);
                        return;
                    } else {
                        print_hdr(hdr, attempts);
                    }
                }
                break;
        }
        ch = get_tty(tty);
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    initscr();
    if (has_colors() == FALSE) {
        endwin();
        printf("Terminal does not support colors, aborting...\n");
        exit(1);
    }
    cbreak();
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    keypad(stdscr, TRUE);
    word_buffer* b = new_buf(16, 12, 6, 7, 16, 12, 6, 28);
    int complexity = 4;
    if (argc == 2 && (strcmp(argv[1], "--advanced") == 0)) {
        complexity = 5;
    }
    buf_complexity(b, complexity);
    addr_windows* aw = new_addr(16, 6, 6, 0, 16, 6, 6, 21);
    tty_window* tty = new_tty(1, 10, 21, 41);
    hdr_window* hdr = new_hdr(5, 80, 0, 0);
    log_window* game_log = new_log(15, 12, 6, 41);
    print_buffer_to_windows(b, tty);
    main_loop(tty, game_log, hdr, b);
    delete_log(game_log);
    del_tty(tty);
    del_addr(aw);
    delete_hdr(hdr);
    del_buf(b);
    endwin();
    return (EXIT_SUCCESS);
}