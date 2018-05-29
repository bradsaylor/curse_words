#include <ncurses.h>

#include "../include/journal_display.h"


int print_to_buffer(int i)
{
    char print_string[display_width];

    sprintf(print_string, "%d", i);

    mvwprintw(buffer_win, 1, 1, print_string);

    wrefresh(buffer_win);

    return 0;
}
