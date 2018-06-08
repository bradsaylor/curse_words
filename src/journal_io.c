#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "../include/journal_io.h"
#include "../include/journal.h"
#include "../include/journal_errors.h"
#include "../include/journal_display.h"
#include "../include/journal_search.h"
#include "../include/journal_files.h"
#include "../include/journal_buffer.h"

// menu strings array
const char *menu_strings[last - 1] = {
    "[n]ew, [v]iew, [q]uit",
    "[F1]save and exit, [F2] abort and exit, [F5] insert keyword",
    "[d]ate, [k]eyword, [t]ext, [e]xit",
    "enter date range",
    "enter keyword",
    "enter search text",
    "[n]ext match, [p]revious match, [e]xit search",
};

int search_result_index = 1;

int capture_input(char *input, int state)
{
    if(state == home_view_date) {
	capture_date_input(input);
	return 0;
    } else if (state == home_view_keyword){
	capture_keyword_input(input);
	return 0;
    } else {
	echo();
	wgetstr(prompt_win, input);
	noecho();
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

	// overwrite input with blank spaces
	for(int count = 0; count < 25; count++) {
	    mvwprintw(prompt_win, 1, 1 + (25 - count), "\b ");
	}
	wrefresh(prompt_win);


    return 0;
}

int capture_keyword_input(char *input)
{
    return_keyword(input);
    int input_size = (int)strlen(input);
    // overwrite input with blank spaces
    for(int count = 0; count < input_size; count++) {
	mvwprintw(prompt_win, 1, 1 + (input_size - count), "\b ");
    }
    wrefresh(prompt_win);
    return 0;
}

int validate_input(int state, char *input)
{
    
    switch(state){
	
    case home:
	if(input[0] == 'n') return home_new;
	else if(input[0] == 'v') return home_view;
	else if(input[0] == 'q') return 'q';
	else {
	    print_error("invalid input");
	    error_log("validate_input, state=home, invalid selection");
	    return home;
	}
	break;
	
    case home_new:
	return home_new;
	break;
	
    case home_view:

	if(input[0] == 'd') return home_view_date;
	else if(input[0] == 'k') return home_view_keyword;
	else if(input[0] == 't') return home_view_text;
	else if(input[0] == 'e') return home;
	else {
	    print_error("invalid input");
	    error_log("validate_input, state=home_view, invalid selection");
	    return home;
	}
        break;

	
    case home_view_date:
	
	if(!check_date_format(input)) {
	    if(search(input, 'd')) {
		search_result_index = 1;                
		display_search_result('i');
		return home_view_search_return;
	    }
	    else {
		print_error("No results found");
		reset_buffer_window();
		return home_view;
	    }
	}
	else return home_view_date;
	break;

	
    case home_view_keyword:
	
	if(!check_keyword_format(input)) {
	    if(search(input, 't')) {
		search_result_index = 1;                
		display_search_result('i');
		return home_view_search_return;
	    }
	    else {
		print_error("No results found");
		reset_buffer_window();
		return home_view;
	    }
	}
	break;

	
    case home_view_text:
	
	if(!check_text_format(input)) {
	    if(search(input, 't')) {
		search_result_index = 1;                
		display_search_result('i');
		return home_view_search_return;
	    }
	    else {
		print_error("No results found");
		reset_buffer_window();
		return home_view;
	    }
	}
	
	break;

    case home_view_search_return:
	if(input[0] == 'n') {
	    display_search_result('n');
	    return home_view_search_return;
	}
	else  if(input[0] == 'p') {
	    display_search_result('p');
	    return home_view_search_return;
	}
	else if(input[0] == 'e') {
	    reset_buffer_window();
	    return home;
	}
	else {
	    reset_buffer_window();
	    print_error("invalid input");
	    error_log(
		"validate_input, state = home_view_date_return, invalid selection"
	    );
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

int display_search_result(char mode)
{
    int num_results = 0;
    char file_line[display_width];
    int num_results_found = 0;

    FILE *fp;
    fp = fopen(search_results_file, "r");
    while((fgets(file_line, sizeof(file_line), fp)) != NULL) {
	if(strstr(file_line, token_string) != NULL) num_results++;
    }
    fclose(fp);

    
    if(mode == 'p') {
	if(search_result_index == 1) {
	    print_error("no previous results");
	    return 1;
	}
	search_result_index--;
    }
    if(mode == 'n') {
        if(search_result_index == num_results) {
	    print_error("no more results");
	    return 1;
	}
	search_result_index++;
    }


    fp = fopen(search_results_file, "r");

    while(((fgets(file_line, sizeof(file_line), fp))) != NULL) {

	if((strstr(file_line, token_string)) != NULL) num_results_found++;
	if(num_results_found == search_result_index) break;
    }

    wclear(buffer_win);
    box(buffer_win, 0, 0);
    int row_count = 1;

    while((fgets(file_line, sizeof(file_line), fp)) != NULL) {
	if(strstr(file_line, token_string) != NULL) break;
        wmove(buffer_win, row_count, 1);
	wprintw(buffer_win, file_line);
	row_count++;
    }

    wmove(buffer_win, 1, display_width - 10);
    wattron(buffer_win, A_UNDERLINE);
    wprintw(buffer_win, "%d/%d", search_result_index, num_results);
    wattroff(buffer_win, A_UNDERLINE);

    box(buffer_win, 0, 0);
    wrefresh(buffer_win);
    fclose(fp);

    return 0;
}
