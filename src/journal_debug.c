#include <ncurses.h>
#include <string.h>
#include <stdio.h>

#include "../include/journal.h"
#include "../include/journal_display.h"
#include "../include/journal_util.h"

int print_to_buffer(int num, char *str)
{
    char print_string[display_width];

    mvwprintw(debug_win, 1, 1, "                   ");

    if(num != -1 && !strcmp(str, ""))    sprintf(print_string, "%d", num);
    if(num == -1 && strcmp(str, "")) sprintf(print_string, "result: '%s'", str);
    if(num != -1 && strcmp(str, "")) sprintf(print_string, "'%s': %d", str, num);

    mvwprintw(debug_win, 1, 1, print_string);

    wrefresh(debug_win);

    return 0;
}

int debug_print_line()
{
    FILE *fp;
    char str[display_width + 1];
    int xpos = 0;
    int buffer_char;

    for(int count = 0; count < 100; count++) {
	buffer_char = mvwinch(buffer_win, 2, xpos + count) & A_CHARTEXT;
	str[count] = buffer_char;
    }
    str[100] = '\0';

    fp = fopen(debug_file, "w");
    for(int count = 0; count < 100; count++) {
        fprintf(fp,"%d\t%d\n", count, str[count]);
    }
    fclose(fp);

    
    return 0;
}
