#include <string.h>
#include <stdio.h>

#include "../include/journal_search.h"
#include "../include/journal.h"
#include "../include/journal_display.h"
#include "../include/journal_util.h"
#include "../include/journal_files.h"

int search(char *search_term, int mode)
{
    switch(mode) {
    case 'd':
	search_date(search_term);
	break;
    case 't':
	search_text(search_term);
	break;
    default:
	break;
    }


    return 0;
}

int search_date(char *search_term)
{
    char min_date[9], max_date[9];

    extract_dates(search_term, max_date, min_date);
    


    return 0;
}

int search_text(char *search_term)
{


    return 0;
}

int extract_dates(char *search_term, char *max_date, char *min_date)
{
    remove_chars(search_term, "<>-");
    sscanf(search_term, "%s %s", min_date, max_date);
    return 0;
}

int tokenize_file(char *filename, char *token)
{
    char *tok;
    char file_string[display_width * buffer_height * MAX_JOURNAL_ENTRIES];

    return_file_as_string(journal_file, file_string, (int)sizeof(file_string));

    tok = strtok(file_string, token_string);

    return 0;
}

int search_token_for_date(char *token)
{


    return 0;
}

int search_token_for_text(char *token, char *text)
{


    return 0;
}

int search_results_display()
{


    return 0;
}
