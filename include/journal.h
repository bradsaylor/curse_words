#ifndef _JOURNAL_H_
#define _JOURNAL_H_

// max array size constants
#define MAX_MENU_STRING 50
#define MAX_INPUT 50

// function declarations
int call_sub(int state);

// enumeration for program states
enum {
    home = 1,
    home_new,
    home_view,
    home_view_date,
    home_view_keyword,
    home_view_text,
    home_view_date_return,
    home_view_keyword_return,
    home_view_text_return,
    last,
};

// constants define in journal.c
extern char journal_file[];
extern char keyword_file[];
extern char error_log_file[];
#endif //_JOURNAL_H_
