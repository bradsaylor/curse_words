#include<string.h>
#include<ncurses.h>

#include "../include/journal_buffer.h"
#include "../include/journal.h"
#include "../include/journal_display.h"
#include "../include/journal_util.h"
#include "../include/journal_debug.h"

int buffer()
{
    char date_stamp[display_width];
    int input_char = ' ';

    get_datestamp(date_stamp);

    mvwprintw(buffer_win, 1, 1, date_stamp);
    wmove(buffer_win, 2, 1);
    wrefresh(buffer_win);
    noecho();
    keypad(buffer_win, TRUE);

    while(1) {
	input_char = wgetch(buffer_win);
	if(input_char == KEY_F(1)) break;
	waddch(buffer_win, input_char);
	wrefresh(buffer_win);
    }

    echo();
    return 0;
}
