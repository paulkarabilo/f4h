#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include "../include/windows.h"
#include "../include/buf.h"
#include "../include/log.h"

void print_header(WINDOW* hdr, int attempts) {
    wclear(hdr);
    wprintw(hdr, "Welcome to ***\n");
    wprintw(hdr, "Password required\n\n");
    wprintw(hdr, "Attempts remaining: ");
    while (attempts--) {
        wprintw(hdr, "| ");
    } 
    wprintw(hdr, "\n\n");
    wrefresh(hdr);
}

void print_header_game_over(WINDOW* hdr) {
    wclear(hdr);
    wprintw(hdr, "GAME OVER\n");
    wprintw(hdr, "Press any button to exit\n");
    wrefresh(hdr);
}

void print_row_hex_addresses(WINDOW* l, WINDOW* r) {
    int a = 100 * (rand() %  100);
    for (int i = 0; i < 16; i++) {
        wprintw(l, "0X%04X", a);
        wprintw(r, "0X%04X", a + 12 * 16);
        a += 12;
    }
    wrefresh(l);
    wrefresh(r);
}

void print_buffer_to_windows(WINDOW* lc, WINDOW* rc, WINDOW* tty, word_buffer *b) {
    wclear(lc);
    wclear(rc);
    print_current_to_tty(b, tty);
    print_buf_to_win(b, lc, 0, 192);
    print_buf_to_win(b, rc, 192, 192);
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

void main_loop(WINDOW* lc, WINDOW* rc, WINDOW* tty, log_window* game_log, WINDOW* hdr, word_buffer* b) {
    int attempts = 4;
    print_header(hdr, attempts);
    int ch = wgetch(tty);
    while (ch != 27 && attempts > 0) {
        switch(ch) {
            case KEY_LEFT:
                navigate_buffer(b, -1);
                print_buffer_to_windows(lc, rc, tty, b);
                break;
            case KEY_RIGHT:
                navigate_buffer(b, 1);
                print_buffer_to_windows(lc, rc, tty, b);
                break;
            case KEY_UP:
                navigate_buffer_char(b, -14);
                print_buffer_to_windows(lc, rc, tty, b);
                break;
            case KEY_DOWN:
                navigate_buffer_char(b, 14);
                print_buffer_to_windows(lc, rc, tty, b);
                break;
            case 10: //Enter key only works like this
                if (b->cont[b->cursor]->is_word && !(b->cont[b->cursor]->was_selected)) {
                    check_guess(b, game_log, attempts);
                    attempts--;
                    print_header(hdr, attempts);
                }
                break;
        }
        ch = wgetch(tty);
    }
    if (attempts == 0) {
        print_header_game_over(hdr);
        ch = wgetch(tty);
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
    word_buffer* b = new_buf();
    buf_complexity(b, 4);
    WINDOW* hdr = new_window(5, 80, 0, 0);
    WINDOW* l = new_window(16, 6, 6, 0);
    WINDOW* r = new_window(16, 6, 6, 21);
    WINDOW* lc = new_window(16, 12, 6, 7);
    WINDOW* rc = new_window(16, 12, 6, 28);
    WINDOW* tty = new_window(1, 10, 21, 41);
    //WINDOW* log = new_window(15, 10, 6, 41);
    log_window* game_log = new_log(15, 12, 6, 41);
    keypad(tty, TRUE);
    print_row_hex_addresses(l, r);
    print_buffer_to_windows(lc, rc, tty, b);
    main_loop(lc, rc, tty, game_log, hdr, b);
    delete_log(game_log);
    del_window(tty);
    del_window(rc);
    del_window(lc);
    del_window(r);
    del_window(l);
    del_window(hdr);
    
    endwin();
    del_buf(b);
    return (EXIT_SUCCESS);
}