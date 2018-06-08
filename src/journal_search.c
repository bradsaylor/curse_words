#include <string.h>
#include <stdio.h>

#include "../include/journal_search.h"
#include "../include/journal.h"
#include "../include/journal_display.h"
#include "../include/journal_util.h"
#include "../include/journal_files.h"

int search(char *search_term, char mode)
{
    char min_date[9], max_date[9];
//    char file_string[display_width * buffer_height * MAX_JOURNAL_ENTRIES];
    char file_string[MAX_JOURNAL_ENTRIES];
    char *token;
    int match_result = 0;
    int found_match_flag = 0;

    // intialize file for storing search results
    initialize_results_file();

    // convert journal file to string
    return_file_as_string(journal_file, file_string, (int)sizeof(file_string));

    // tokenize the journal file
    token = strtok(file_string, token_string);

    // find tokens
    while(token != NULL) {

        // evaluate token for match conditions
	if(mode == 'd') {
	    extract_dates(search_term, max_date, min_date);
	    // if matched print token to result file
	    if((match_result = date_match(token, max_date, min_date))) {
		write_token(token);
		found_match_flag = 1;
	    }
	} else if (mode == 't') {
	    // if matched print token to result file	    
	    if((match_result = text_match(token, search_term))) {
		write_token(token);
		found_match_flag = 1;
	    }
	}
	// grab next token if there is one
	token = strtok(NULL, token_string);
    }

    return found_match_flag;
}

int date_match(char *token, char *max_date, char *min_date)
{
    char *date_ptr = token;
    char date_string[50];
    int write_counter = 0;
    
    // search for date string in token and load into local var
    while((*date_ptr) != '<') {
	// for a null entry (aka first token) return 0 if
	// crossing into next token (aka finds a '\0')
	// before finding star of date string (aka '<')
	if((*date_ptr) == '\0') return 0;
	date_ptr++;
    }

    do {
	date_string[write_counter] = (*date_ptr);
	date_ptr++;
	write_counter++;
    } while ((*date_ptr) != '>');

    // terminate with '\0' for string operations
    date_string[write_counter] = '\0';

    remove_chars(date_string, "<>-");

    if((strcmp(date_string, min_date) >= 0)
       && (strcmp(date_string, max_date) <= 0)) return 1;
    
    return 0;
}

int text_match(char *token, char *search_term)
{
    char *search_result;

    search_result = strstr(token, search_term);
    if(search_result != NULL) return 1;

    return 0;
}

int extract_dates(char *search_term, char *max_date, char *min_date)
{
    remove_chars(search_term, "<>-");
    sscanf(search_term, "%s %s", min_date, max_date);
    return 0;
}

int write_token(char *token)
{
    char temp[display_width * buffer_height] = {'\0'};
    strcat(temp, token_string);
    strcat(temp, token);
    append_to_file(search_results_file, temp);

    return 0;
}

int initialize_results_file()
{
    FILE *fp;
    fp = fopen(search_results_file, "w");
    fclose(fp);
    return 0;
}
