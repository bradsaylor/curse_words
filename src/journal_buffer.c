#include <string.h>
#include <ncurses.h>
#include <stdlib.h>

#include "../include/journal_buffer.h"
#include "../include/journal.h"
#include "../include/journal_display.h"
#include "../include/journal_util.h"
#include "../include/journal_debug.h"
#include "../include/journal_io.h"
#include "../include/journal_files.h"

int buffer(char *menu_string)
{
    char date_stamp[display_width];
    int input_char = ' ';
    int xpos = 0;
    int ypos = 0;
    int previous_line_length;
    int read_count = 0;

    get_datestamp(date_stamp);

    mvwprintw(buffer_win, 1, 1, date_stamp);
    wmove(buffer_win, 2, 1);
    wrefresh(buffer_win);
    noecho();
    keypad(buffer_win, TRUE);

    while(1) {

	getyx(buffer_win, ypos , xpos);
	input_char = wgetch(buffer_win);
	
	if(input_char == KEY_F(1)) {
	    write_to_file();
	    wclear(buffer_win);
	    box(buffer_win, 0, 0);
	    wrefresh(buffer_win);
	    break;
	}

	else if(input_char == KEY_F(2)) {
	    wclear(buffer_win);
	    box(buffer_win, 0, 0);
	    wrefresh(buffer_win);
            break;
	}

	else if(input_char == KEY_F(5)) {
	    // store buffer_win to temp file
	    window_to_file(buffer_win, temp_file, buffer_height - 2, display_width - 2);
	    // clear buffer win
	    wclear(buffer_win);
	    // define string to hold returned keyword
	    char formatted_print_keyword[display_width];
	    // fetch keyword from insert_keyword
	    insert_keyword(formatted_print_keyword);
	    // clear buffer_win
	    wclear(buffer_win);
	    // redraw box for buffer_win
	    box(buffer_win, 0, 0);
	    // fetch and load window stored in temp file
	    window_from_file(buffer_win, temp_file, buffer_height - 2, display_width - 2);
//	    box(buffer_win, 0, 0);
	    wrefresh(buffer_win);
	        
	    int line_pos = 1;
	    int line_char = '\0';
	    // search for ' ' char in penultimate line of buffer_win and place keyword there
	    while(1) {
		line_char = (mvwinch(buffer_win, buffer_height - 2, line_pos) & A_CHARTEXT);
		if(line_char != 32) line_pos++;
		else {
		    break;
		}
	    }
	    mvwprintw(buffer_win, buffer_height - 2, line_pos, formatted_print_keyword);
	    curses_update_menu(menu_string);	

	    // move cursor back to previous position before keyword routine
	    wmove(buffer_win, ypos, xpos);
	    // refresh buffer_win
	    wrefresh(buffer_win);
	}

	// if( (not <BS>) AND ( (end of buffer) OR (<RET> AND last line)) ) -> block and print error
	else if((input_char != 127) && (((ypos == buffer_height - 2) && (xpos == display_width - 2))
					|| ((input_char == 10) && (ypos == buffer_height - 2)))) {
	    end_of_buffer();
	    wmove(buffer_win, ypos, xpos);
	    wrefresh(buffer_win);
	}
	
	else if(xpos == (display_width - 1)){
	    wrap_line(ypos, xpos, &previous_line_length);
	    waddch(buffer_win, input_char);
	    wrefresh(buffer_win);
	}
	
	else if(input_char == 127) {
	    backspace_func(ypos, xpos);
	    wrefresh(buffer_win);
	}

	else if(input_char == 10) nl_func(ypos);

	else {
	    int check = waddch(buffer_win, input_char);
	    read_count++;
	    if (check == ERR) print_to_buffer(-1, "error on print");
   
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

int end_of_buffer()
{
    print_error("Reached end of buffer");
    return 0;
}

int write_to_file()
{
    chtype raw_buffer_line[display_width - 1];
    char buffer_line[display_width - 1];
    int line_size = 0;
    int has_content_flag = 0;
    
    for(int count = 1; count < (buffer_height - 1); count++) {
	
	mvwinchnstr(buffer_win, count, 1,  raw_buffer_line, (display_width - 2));
	line_size = sizeof(raw_buffer_line) / sizeof(raw_buffer_line[0]);
	has_content_flag = 0;
	for(int count2 = 0; count2 < line_size - 1; count2++) {
	    buffer_line[count2] = raw_buffer_line[count2] & A_CHARTEXT;
	    if(buffer_line[count2] != ' ') has_content_flag = 1;
	}

	buffer_line[line_size - 1] = '\0';

	if(has_content_flag) append_to_file(journal_file, buffer_line);
    }
    append_to_file(journal_file, "\n");
    return 0;
}

int insert_keyword(char *formatted_print_keyword)
{
    int num_keywords = 0;
    char keyword_input[display_width];
    char print_keyword[display_width];
    char new_keyword[display_width];
    int x, y;
    
    // draw box for buffer_win erased before function call
    box(buffer_win, 0, 0);

    // display a numbered list of keywords in keywords file
    num_keywords = curses_list_file_numbered(keyword_file, display_width - 2, buffer_win);

    getyx(buffer_win, y, x);
    wmove(buffer_win, y + 1, 1);
    // append one more number for 'add a new keyword'
    wprintw(buffer_win, "[%d]  Add keyword", num_keywords + 1);

    // update window
    box(buffer_win, 0, 0);
    wrefresh(buffer_win);
    
    // move to prompt and scan for input
    wmove(prompt_win, 1, 1);
    echo();
    capture_input(keyword_input, 100);
    noecho();
    
    // validate input
    // if input bad print error
    if((atoi(keyword_input) < 1) || (atoi(keyword_input) > (num_keywords + 1))) {
	print_error("invalid selection");
    } else {
        // if input is new keyword -> add keyword to keyword file
	if(atoi(keyword_input) == (num_keywords + 1)) {
	    char file_keyword[display_width];
	    curses_update_menu("Enter new keyword");
	    echo();
	    wmove(prompt_win, 1, 1);
	    capture_input(new_keyword, 100);
	    noecho();
	    sprintf(file_keyword, "%s", new_keyword);
	    append_to_file(keyword_file, file_keyword);
	    strcpy(print_keyword, new_keyword);
	} else {
	    return_file_line(keyword_file, atoi(keyword_input), print_keyword, display_width);
	}
    }
    // format string with <> and store in passed string variable
    sprintf(formatted_print_keyword, "<%s>", print_keyword);

    return 0;
    
}
