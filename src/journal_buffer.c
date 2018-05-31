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
    int xpos = 0;
    int ypos = 0;
    int previous_line_length;

    get_datestamp(date_stamp);

    mvwprintw(buffer_win, 1, 1, date_stamp);
    wmove(buffer_win, 2, 1);
    wrefresh(buffer_win);
    noecho();
    keypad(buffer_win, TRUE);

    while(1) {
	getyx(buffer_win, ypos , xpos);
	input_char = wgetch(buffer_win);
	
	if(input_char == KEY_F(1)) break;
	else if(xpos == (display_width - 1)){
	    wrap_line(ypos, xpos, &previous_line_length);
	    waddch(buffer_win, input_char);
	    wrefresh(buffer_win);
	}
	else if(input_char == 127) {
	    backspace_func(ypos, xpos);
	    wrefresh(buffer_win);
	} else if(input_char == 10) nl_func(ypos);
	else {
	waddch(buffer_win, input_char);
	wrefresh(buffer_win);
	}
    }
   
    echo();
    return 0;
}

int wrap_line(int ypos, int xpos, int *previous_line_length)
{
    int chars_to_space = 0;
    int found_space_flag = 0;
    int buffer_char = '_';
    chtype raw_wrap_string[display_width];
    char wrap_string[display_width];

    while(!found_space_flag) {
	buffer_char = mvwinch(buffer_win, ypos, xpos - chars_to_space) & A_CHARTEXT;
	if(buffer_char == ' ') found_space_flag = 1;
	chars_to_space++;
    }

    chars_to_space--;

    *previous_line_length = (xpos - chars_to_space);

    wmove(buffer_win, ypos, xpos - (chars_to_space - 1));

    winchnstr(buffer_win, raw_wrap_string, chars_to_space);
    
    for(int count = 0; count < chars_to_space - 1; count++) {
	wrap_string[count] = raw_wrap_string[count] & A_CHARTEXT;
	if(count == (chars_to_space - 1)) break;
	else waddch(buffer_win, ' ');
    }

    wrap_string[chars_to_space - 1] = '\0';

    mvwprintw(buffer_win, ypos + 1, 1, wrap_string);

    wrefresh(buffer_win);

    return 0;
}

int backspace_func(int ypos, int xpos)
{
    if((ypos == 2) && (xpos == 1)) return 0;
    
    else if(xpos == 1) {
	int line_position = display_width - 2;
	int line_char = 0;
	while(1) {
	    line_char =  mvwinch(buffer_win, ypos - 1, line_position) & A_CHARTEXT;
	    
	    if((line_char < 33) || (line_char > 126)) {
		line_position--;                
	    } else break;
	}
	wmove(buffer_win, ypos-1, line_position + 1);
	
    } else {
	wmove(buffer_win, ypos, xpos - 1);
	waddch(buffer_win, ' ');
	wmove(buffer_win, ypos, xpos - 1);
    }
    
    wrefresh(buffer_win);

    return 0;
}

int nl_func(int ypos)
{
    wmove(buffer_win, ypos + 1, 1);

    return 0;
}
