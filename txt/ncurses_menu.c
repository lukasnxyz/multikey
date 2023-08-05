#include <stdio.h>
#include <ncurses.h>

/*
 * Printing
 *  addstr — prints the specified string
 *  addch — prints a single char
 *  printw — the ncurses equivalent of printf
 */

int main(void) {

    WINDOW *w;
    char list[5][7] = {"One", "Two", "Three", "Four", "Five"};
    char item[7];

    int ch, width = 7;
    initscr();
    w = newwin(10, 12, 1, 1);
    box(w, 0, 0);

    for(int i = 0; i < 5; i++) {
        if(i == 0)
            wattron(w, A_STANDOUT);
        else
            wattroff( w, A_STANDOUT );

        sprintf(item, "%-7s", list[i]);
        mvwprintw(w, i+1, 2, "%s", item);
    }

    wrefresh(w);
    int i = 0;
    noecho();
    keypad(w, TRUE);
    curs_set( 0 );

    while((ch = wgetch(w)) != 'q'){
        sprintf(item, "%-7s", list[i]);
        mvwprintw( w, i+1, 2, "%s", item );
        switch(ch) {
            case KEY_UP:
                i--;
                i = ( i<0 ) ? 4 : i;
                break;
            case KEY_DOWN:
                i++;
                i = ( i>4 ) ? 0 : i;
                break;
        }

        wattron( w, A_STANDOUT );
        sprintf(item, "%-7s", list[i]);
        mvwprintw( w, i+1, 2, "%s", item);
        wattroff( w, A_STANDOUT );
    }

    delwin(w);
    endwin();

    return 0;
}
