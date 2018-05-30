#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "../include/journal_io.h"
#include "../include/journal.h"
#include "../include/journal_errors.h"
#include "../include/journal_display.h"
#include "../include/journal_debug.h"

// menu strings array
const char *menu_strings[last - 1] = {
    "[n]ew [v]iew",
    "F1 to save and exit",
    "[d]ate, [k]eyword, [t]ext",
    "enter date range",
    "enter keyword",
    "enter search text",
    "[n]ext match, [l]ast match, [e]xit search",
    "[n]ext match, [l]ast match, [e]xit search",
    "[n]ext match, [l]ast match, [e]xit search"    
};



int get_menu(int state, char *menu_string)
{
    int num_menus = (int)sizeof(menu_strings) / (int)sizeof(menu_strings[0]);

    if((state > 0) && (state <= num_menus)) {
	strcpy(menu_string, menu_strings[state - 1]);
     } else { 
     	error_log("requested menu does not exist"); 
     	return 1; 
     } 

    return 0;
}

int capture_input(char *input, int state)
{
    if(state == home_view_date) {
	capture_date_input(input);
	return 0;
    } else {
    
	wgetstr(prompt_win, input);
	int input_size = (int)strlen(input);
	// overwrite input with blank spaces
	for(int count = 0; count < input_size; count++) {
	    mvwprintw(prompt_win, 1, 1 + (input_size - count), "\b ");
	}
	wrefresh(prompt_win);
    }

    return 0;
}

int capture_date_input(char *input)
{
    chtype raw_date_string[26];
    char date_string[26];
    char input_char;

    mvwprintw(prompt_win, 1, 1, "<xxxx-xx-xx> <xxxx-xx-xx>");
    wmove(prompt_win, 1, 2);
    wrefresh(prompt_win);

    for(int count = 0; count < 4; count++) {
	input_char = getch();
	waddch(prompt_win, input_char);
	wrefresh(prompt_win);
	wmove(prompt_win, 1, 3 + count);
	wrefresh(prompt_win);
    }
    wmove(prompt_win, 1, 7);
    for(int count = 0; count < 2; count++) {
	input_char = getch();
	waddch(prompt_win, input_char);
	wmove(prompt_win, 1, 8 + count);
	wrefresh(prompt_win);
    }
    wmove(prompt_win, 1, 10);
    for(int count = 0; count < 2; count++) {
	input_char = getch();
	waddch(prompt_win, input_char);
	wmove(prompt_win, 1, 11 + count);
	wrefresh(prompt_win);
    }
    wmove(prompt_win, 1, 15);
    for(int count = 0; count < 4; count++) {
	input_char = getch();
	waddch(prompt_win, input_char);
	wrefresh(prompt_win);
	wmove(prompt_win, 1, 16 + count);
	wrefresh(prompt_win);
    }
    wmove(prompt_win, 1, 20);
    for(int count = 0; count < 2; count++) {
	input_char = getch();
	waddch(prompt_win, input_char);
	wmove(prompt_win, 1, 21 + count);
	wrefresh(prompt_win);
    }
    wmove(prompt_win, 1, 23);
    for(int count = 0; count < 2; count++) {
	input_char = getch();
	waddch(prompt_win, input_char);
	wmove(prompt_win, 1, 24 + count);
	wrefresh(prompt_win);
    }


    mvwinchnstr(prompt_win, 1, 1, raw_date_string, 25);
    for(int count = 0; count < 26; count++) {
	date_string[count] = (raw_date_string[count] & A_CHARTEXT);
    }

    strcpy(input, date_string);

    return 0;
}

int validate_input(int state, char *input)
{
    
    switch(state){
	
    case home:
	if(input[0] == 'n') return home_new;
	else if(input[0] == 'v') return home_view;
	else {
	    print_error("invalid input");
	    error_log("validate_input, state=home, invalid selection");
	    return home;
	}
	break;
	
    case home_new:
	return home;
	break;
	
    case home_view:
	if(input[0] == 'd') return home_view_date;
	else if(input[0] == 'k') return home_view_keyword;
	else if(input[0] == 't') return home_view_text;
	else {
	    print_error("invalid input");
	    error_log("validate_input, state=home_view, invalid selection");
	    return home;
	}
        break;
	
    case home_view_date:
	
	if(!check_date_format(input)) return home_view_date_return;
	else return home_view_date;
	break;
	
    case home_view_keyword:
	if(!check_keyword_format(input)) return home_view_keyword_return;
	break;
	
    case home_view_text:
	if(!check_text_format(input)) return home_view_text_return;
	
	break;

    case home_view_date_return:
	if(input[0] == 'n') return home;
	else if(input[0] == 'l') return home;
	else if(input[0] == 'e') return home;
	else {
	    print_error("invalid input");
	    error_log("validate_input, state = home_view_date_return, invalid selection");
	    return home;
	}
	break;

    case home_view_keyword_return:
	if(input[0] == 'n') return home;
	else if(input[0] == 'l') return home;
	else if(input[0] == 'e') return home;
	else {
	    print_error("invalid input");
	    error_log("validate_input, state = home_view_keyword_return, invalid selection");
	    return home;
	}
	break;

    case home_view_text_return:
	if(input[0] == 'n') return home;
	else if(input[0] == 'l') return home;
	else if(input[0] == 'e') return home;
	else {
	    print_error("invalid input");
	    error_log("validate_input, state = home_view_text__return, invalid selection");
	    return home;
	}
	break;

    default:
	error_log("validte_input, invalid state");
	return -1;
	break;
    }

    return 0;

}

int check_date_format(char *input)
{
    char date_string[25];
    int input_length = (int)strlen(input);
    int digit_count = 0;

    for(int count = 0; count < input_length; count++) {
	if((input[count] >=48) && (input[count] <= 57)) {
	    date_string[count] = input[count];
	    digit_count++;
	}
    }

    if(digit_count != 16) {
	print_error("date format incorrect");
	return 1;
    }

    return 0;
}

int check_keyword_format(char *input) {


    return 0;
}

int check_text_format(char *input) {


    return 0;
}
