#include "../include/hdr.h"

hdr_window* new_hdr(int h, int w, int y, int x) {
    hdr_window* hdr = malloc(sizeof(hdr_window));
    hdr->win = new_window(h, w, y, x);
    return hdr;
}

void delete_hdr(hdr_window* hdr) {
    del_window(hdr->win);
    free(hdr);
}

void print_hdr(hdr_window* hdr, int attempts) {
    wclear(hdr->win);
    wprintw(hdr->win, "Welcome to ***\n");
    wprintw(hdr->win, "Password required\n\n");
    wprintw(hdr->win, "Attempts remaining: ");
    while (attempts--) {
        wprintw(hdr->win, "| ");
    } 
    wprintw(hdr->win, "\n\n");
    wrefresh(hdr->win);
}

void print_hdr_game_over(hdr_window* hdr) {
    wclear(hdr->win);
    wprintw(hdr->win, "GAME OVER\n");
    wprintw(hdr->win, "Press any button to exit\n");
    wrefresh(hdr->win);
}

void print_hdr_win(hdr_window* hdr) {
    wclear(hdr->win);
    wprintw(hdr->win, "Entry accepted\n");
    wprintw(hdr->win, "Press any button to continue\n");
    wrefresh(hdr->win);
}
