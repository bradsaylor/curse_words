#include <ncurses.h>

#include "../include/journal.h"
#include "../include/journal_display.h"
#include "../include/journal_io.h"
#include "../include/journal_buffer.h"
//
// constants
char error_log_file[] = ".journal_error_log";

int main()
{
    int quit = 0;
    int state = 1;
    char menu_string[MAX_MENU_STRING];
    char input[display_width];
    
    curses_init();

    while(!quit) {
	
	get_menu(state, menu_string);

	curses_update_menu(menu_string);
	
	cursor_to_prompt();
	
	capture_input(input, state);

	if(input[0] == 'q') break;
	
	if((state = validate_input(state, input))) {

	    call_sub(state);
	}
    }

    curses_exit;

    return 0;
}

int call_sub(int state)
{
    switch(state) {
    case home_new:
	buffer();
	break;
    }

    return 0;
}
    
