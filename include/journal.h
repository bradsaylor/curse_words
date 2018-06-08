#ifndef _JOURNAL_H_
#define _JOURNAL_H_

// max array size constants
#define MAX_MENU_STRING 50
#define MAX_INPUT 50
#define MAX_JOURNAL_ENTRIES 1000

// function declarations
int call_sub(int *state);

// enumeration for program states
enum {
    home = 1,
    home_new,
    home_view,
    home_view_date,
    home_view_keyword,
    home_view_text,
    home_view_search_return,
    last,
};

// constants define in journal.c
extern char journal_file[];
extern char keyword_file[];
extern char error_log_file[];
extern char debug_file[];
extern char temp_file[];
extern char search_results_file[];
#endif //_JOURNAL_H_
