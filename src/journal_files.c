#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>

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
    // initiate temp file 
    FILE *fp;
    fp = fopen(file_name, "w");

    // vars to hold read window lines
    chtype raw_win_line[win_width + 1];
    char win_line[win_width + 1];

    // start at y = 1 to avoid box, go to y = win_height
    for(int count1 = 1; count1 < win_height + 1; count1++) {
	// store current window line as ch_type var, max 
	mvwinchnstr(win, count1, 1, raw_win_line, win_width);
	for(int count2 = 0; count2 < win_width; count2++) {
	    // read raw ch_type input into a character array
	    win_line[count2] = raw_win_line[count2] & A_CHARTEXT;
	}
	win_line[win_width] = '\0';
	// print window line to file
	fprintf(fp, "%s", win_line);
    }
    

    fclose(fp);
    return 0;
}

int window_from_file(WINDOW *win, char *file_name,
		     int win_height, int win_width)
{
    // open window temp file
    FILE *fp, *fp2;
    fp = fopen(file_name, "r");
    fp2 = fopen("output.txt", "w");

    // vars for holding read file line
    char win_line[win_width + 1];

    wmove(win, 1, 1);
    for(int count = 0; count < win_height; count++) {

	fgets(win_line, win_width + 1, fp);


	for(int count2 = 0; count2 < (int)strlen(win_line); count2++){
	    fprintf(fp2, "%d ", win_line[count2]);
	}
	fprintf(fp2, "\n");
	fprintf(fp2, "%d:%s\n", count, win_line);
	
	mvwprintw(win, count + 1, 1, win_line);
    }

    fclose(fp);
    fclose(fp2);
    return 0;
}
