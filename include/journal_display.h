#ifndef _JOURNAL_DISPLAY_H_
#define _JOURNAL_DISPLAY_H_

#include <ncurses.h>

// define macros
#define curses_exit endwin()

// window declarations
WINDOW *title_win, *buffer_win, *menu_win, *prompt_win;
#define display_width 100
#define titile_height 5
#define buffer_height 35
#define menu_height 5
#define prompt_height 5

// function declarations
int curses_init();
int curses_update_menu(char *menu_string);
int cursor_to_prompt();
int print_error(char *error_msg);

#endif //_JOURNAL_DISPLAY_H_
