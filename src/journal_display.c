#include <ncurses.h>
#include <string.h>

#include "../include/journal_display.h"

int curses_init()
{
    initscr();
//    noecho();
    raw();
    refresh();

    title_win = newwin(title_height, display_width, 0, 0);
    box(title_win, 0, 0);
    wattron(title_win, A_REVERSE);
    mvwprintw(title_win, 1, (display_width/2) - 6, " CURSE-WORDS ");
    wrefresh(title_win);
    wattroff(title_win, A_REVERSE);

    buffer_win = newwin(buffer_height, display_width, title_height, 0);
    box(buffer_win, 0, 0);
    keypad(buffer_win, TRUE);
    wrefresh(buffer_win);

    menu_win = newwin(menu_height, display_width,
		      title_height + buffer_height, 0);
    box(menu_win, 0, 0);
    wrefresh(menu_win);

    prompt_win = newwin(prompt_height, display_width,
			title_height + buffer_height + menu_height, 0);
    box(prompt_win, 0, 0);
    wrefresh(prompt_win);

    return 0;
}

int curses_update_menu(char *menu_string)
{
    int blank_chars = 0;

    mvwprintw(menu_win, 1, 1, menu_string);
    blank_chars = (display_width - 2) - strlen(menu_string);
    for(int count = 0; count < blank_chars; count ++) wprintw(menu_win, " ");
    wrefresh(menu_win);

    return 0;
}

int cursor_to_prompt()
{
    wmove(prompt_win, 1, 1);
    wrefresh(prompt_win);

    return 0;
}

int print_error(char *error_msg)
{
    char continue_string[] = "...any key to continue";
    int blank_chars = (int)strlen(error_msg) + strlen(continue_string);

    char error_message[display_width];
    sprintf(error_message, "%s%s", error_msg, continue_string);
    mvwprintw(prompt_win, 1 ,1, error_message);
    wrefresh(prompt_win);
    flash();
    char temp = getch();
    for(int count = 0; count < blank_chars; count++) {
	mvwprintw(prompt_win, 1, (blank_chars + 1) - count , "\b ");
    }
    wrefresh(prompt_win);
    
    return 0;
}

int reset_buffer_window()
{
    wclear(buffer_win);
    box(buffer_win, 0, 0);
    wrefresh(buffer_win);

    return 0;
}
