#include<string.h>
#include<ncurses.h>

#include "../include/journal_buffer.h"
#include "../include/journal.h"
#include "../include/journal_display.h"
#include "../include/journal_util.h"

int buffer()
{
    char date_stamp[display_width];
    get_datestamp(date_stamp);

    mvwprintw(buffer_win, 1, 1, date_stamp);
    wrefresh(buffer_win);

    return 0;
}
