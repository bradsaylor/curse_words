#ifndef _JOURNAL_BUFFER_H_
#define _JOURNAL_BUFFER_H_

#include <ncurses.h>

int buffer(char *menu_string);
int wrap_line(int ypos, int xpos, int *previous_line_length);
int backspace_func(int ypos, int xpos);
int nl_func(int ypos);
int end_of_buffer();
int write_to_file();
int insert_keyword(char *formatted_print_keyword);
int return_keyword(char *formatted_print_keyword);
int place_keyword(char *keyword);
#endif  // _JOURNAL_BUFFER_H_
