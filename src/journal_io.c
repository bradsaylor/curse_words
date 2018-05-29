#include <string.h>
#include <stdio.h>

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
     "enter search text"};



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

int capture_input(char *input)
{
    wgetstr(prompt_win, input);
    wrefresh(prompt_win);
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
	}
	break;
	
    case home_new:
	break;
	
    case home_view:
	if(input[0] == 'd') return home_view_date;
	else if(input[0] == 'k') return home_view_keyword;
	else if(input[0] == 't') return home_view_text;
	else {
	    print_error("invalid input");
	    error_log("validate_input, state=home_view, invalid selection");
	}
        break;
	
    case home_view_date:
	if(!check_date_format(input)) return home_view_date_return;
	break;
	
    case home_view_keyword:
	if(!check_keyword_format(input)) return home_view_keyword_return;
	break;
	
    case home_view_text:
	if(!check_text_format(input)) return home_view_text_return;
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


    return 0;
}

int check_keyword_format(char *input) {


    return 0;
}

int check_text_format(char *input) {


    return 0;
}
