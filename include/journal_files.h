#ifndef _JOURNAL_FILES_H_
#define _JOURNAL_FILES_H_

#include <ncurses.h>

int files_init();
int window_to_file(WINDOW *win, char *file_name, int win_height, int win_width);
int window_from_file(WINDOW *win, char *file_name, int win_height, int win_width);

#endif // _JOURNAL_FILES_H_
