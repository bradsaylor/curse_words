#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

#include "../include/journal.h"

int files_init()
{


    if (access(journal_file, F_OK) == -1) {
	FILE *fp = fopen(journal_file, "w");
	fclose(fp);
    }

    if (access(keyword_file, F_OK) == -1) {
	FILE *fp = fopen(keyword_file, "w");
	fclose(fp);
    }

    if (access(error_log_file, F_OK) == -1) {
	FILE *fp = fopen(error_log_file, "w");
	fclose(fp);
    }

    if (access(debug_file, F_OK) == -1) {
	FILE *fp = fopen(debug_file, "w");
	fclose(fp);
    }

    if(access(temp_file, F_OK) == -1) {
	FILE *fp = fopen(temp_file, "w");
	fclose(fp);
    }
    return 0;
}

int window_to_file(WINDOW *win, char *file_name, int win_height, int win_width)
{
    FILE *fp;
    fp = fopen(file_name, "w");
    chtype raw_win_line[win_width + 1];
    char win_line[win_width + 1];

    for(int count1 = 1; count1 < win_height; count1++) {
	mvwinchnstr(win, count1, 1, raw_win_line, win_width);
	for(int count2 = 0; count2 < win_width; count2++) {
	    win_line[count2] = raw_win_line[count2] & A_CHARTEXT;
	}
	win_line[win_width] = '\0';
	fprintf(fp, "%s", win_line);
    }
    

    fclose(fp);
    return 0;
}

int window_from_file(WINDOW *win, char *file_name, int win_height, int win_width)
{
    FILE *fp;
    fp = fopen(file_name, "r");

    char win_line[win_width + 1];
    char test[win_width + 3];

    for(int count = 1; count < win_height + 1; count++) {
	fgets(win_line, win_width, fp);
//	win_line[win_width] = '\0';
	sprintf(test, "'%s'", win_line);
	mvwprintw(win, count, 1, test);
    }

    fclose(fp);
    return 0;
}
