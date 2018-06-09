#include <ncurses.h>

#include "../include/journal.h"
#include "../include/journal_display.h"
#include "../include/journal_io.h"
#include "../include/journal_buffer.h"
#include "../include/journal_files.h"
#include "../include/journal_util.h"

// constants
char journal_file[] = ".journal_log";
char keyword_file[] = ".keywords";
char error_log_file[] = ".journal_error_log";
char debug_file[] = ".debug";
char temp_file[] = ".temp";
char search_results_file[] = ".search_results";

int main()
{
    int state = 1;
    char menu_string[MAX_MENU_STRING];
    char input[display_width];

    bash_resize(display_width + 1, 44);

    curses_init();
    files_init();

    while(1) {
	if(state == 'q') break;
	
	get_menu(state, menu_string);

	curses_update_menu(menu_string);
	
	cursor_to_prompt();
	
	capture_input(input, state);
	
	if((state = validate_input(state, input))) {
	    call_sub(&state);
	}
    }

    curses_exit;

    return 0;
}

int call_sub(int *state)
{
    char menu_string[MAX_MENU_STRING];
    switch(*state) {

    case home_new:
	get_menu(*state, menu_string);
	curses_update_menu(menu_string);

	buffer(menu_string);
	*state = home;
	break;

    }

    return 0;
}
    
