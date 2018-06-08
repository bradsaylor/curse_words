#ifndef _JOURNAL_IO_H_
#define _JOURNAL_IO_H_

// function prototypes
int get_menu(int state, char *menu_string);
int capture_input(char *input, int state);
int capture_date_input(char *input);
int capture_keyword_input(char *input);
int validate_input(int state, char *input);
int check_date_format(char *input);
int check_keyword_format(char *input);
int check_text_format(char *input);
int display_search_result(char mode);

// global declarations
extern int search_result_index;

#endif //_JOURNAL_IO_H_
