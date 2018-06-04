#include <ncurses.h>
#include <stdio.h>

int z_func();

WINDOW *first_win, *second_win, *third_win, *fourth_win;

int main ()
{
    FILE *fp;

    initscr();
    raw();
    noecho();
    refresh();
    

    first_win =  newwin(10, 30, 0, 0 );
    box(first_win, 0, 0);
    wrefresh(first_win);
    second_win = newwin(5, 30, 10, 0);
    box(second_win, 0, 0);
    wrefresh(second_win);

    wrefresh(second_win);
    
    wmove(first_win, 1, 1);
    char char_input = '\0';

    first_win = first_win;
    
    while(char_input != 'q') {
	char_input = wgetch(first_win);
	if(char_input == 'z') {
	    int y = 0, x = 0;
	    getyx(first_win, y, x);
	    fp = fopen("temp_file", "w");
	    chtype raw_win_line[29];
	    char win_line[29];
	    for(int count = 1; count < 9; count++) {
		mvwinchnstr(first_win, count, 1, raw_win_line, 28);
		for(int count2 = 0; count2 < 28; count2++) {
		    win_line[count2] = raw_win_line[count2] & A_CHARTEXT;
		}
		win_line[28] = '\0';
		fprintf(fp, win_line);
	    }
	    fclose(fp);
	    
	    z_func();

	    fp = fopen("temp_file", "r");
	    char print_line[29];
	    for(int count = 1; count < 9; count++) {
		fgets(print_line, 28, fp);
		print_line[28] = '\0';
		mvwprintw(first_win, count, 1, print_line);
	    }
	    fclose(fp);
	    wmove(first_win, y, x);
	}
	else {
	    int return_check = 0;
	    return_check = waddch(first_win, char_input);
	    if(return_check == ERR) mvwprintw(second_win, 1, 1, "error");
	    wrefresh(second_win);
	}
    }

    endwin();

    return 0;
}

int z_func()
{
    box(first_win, 0, 0);
    mvwprintw(first_win, 1, 1, "another window");
    wrefresh(first_win);
    mvwgetch(first_win, 1 ,1);
    return 0;
}
