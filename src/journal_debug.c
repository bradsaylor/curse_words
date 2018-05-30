#include <ncurses.h>
#include <string.h>

#include "../include/journal_display.h"


int print_to_buffer(int num, char *str)
{
    char print_string[display_width];

    mvwprintw(debug_win, 1, 1, "                   ");

    if(num != -1 && !strcmp(str, ""))    sprintf(print_string, "%d", num);
    if(num == -1 && strcmp(str, "")) sprintf(print_string, "result: '%s'", str);
    if(num != -1 && strcmp(str, "")) sprintf(print_string, "'%s': %d", str, num);

    mvwprintw(debug_win, 1, 1, print_string);

    wrefresh(debug_win);

    return 0;
}
