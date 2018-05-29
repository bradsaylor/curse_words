#include <ncurses.h>
#include <string.h>

#include "../include/journal_display.h"

int curses_init()
{
    initscr();
    //noecho();
    raw();
    refresh();

    title_win = newwin(titile_height, display_width, 0, 0);
    box(title_win, 0, 0);
    wrefresh(title_win);

    buffer_win = newwin(buffer_height, display_width, titile_height, 0);
    box(buffer_win, 0, 0);
    keypad(buffer_win, TRUE);
    wrefresh(buffer_win);

    menu_win = newwin(menu_height, display_width, titile_height + buffer_height, 0);
    box(menu_win, 0, 0);
    wrefresh(menu_win);

    prompt_win = newwin(prompt_height, display_width, titile_height + buffer_height + menu_height, 0);
    box(prompt_win, 0, 0);
    wrefresh(prompt_win);

    return 0;
}

int curses_update_menu(char *menu_string)
{
    mvwprintw(menu_win, 1, 1, menu_string);
    wrefresh(menu_win);

    return 0;
}

int clear_menu(){
    char blank_menu[display_width - 1];
    for(int count = 0; count < (int)sizeof(blank_menu); count++) {
	strcat(blank_menu, " ");
    }
    mvwprintw(menu_win, 1, 1, blank_menu);
    wrefresh(menu_win);

    return 0;
}

int clear_prompt(){
    char blank_prompt[display_width - 1];
    for(int count = 0; count < (int)sizeof(blank_prompt); count++) {
	strcat(blank_prompt, " ");
    }
    mvwprintw(menu_win, 1, 1, blank_prompt);
    wrefresh(prompt_win);

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
    char error_message[display_width];
    sprintf(error_message, "%s%s", error_msg, "...any key to continue");
    
    mvwprintw(prompt_win, 1 ,1, error_message);
    wrefresh(prompt_win);

    return 0;
}
