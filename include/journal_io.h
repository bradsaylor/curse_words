#ifndef _JOURNAL_IO_H_
#define _JOURNAL_IO_H_

// function prototypes
int get_menu(int state, char *menu_string);
int capture_input(char *input);
int validate_input(int state, char *input);
int check_date_format(char *input);
int check_keyword_format(char *input);
int check_text_format(char *input);

#endif //_JOURNAL_IO_H_
