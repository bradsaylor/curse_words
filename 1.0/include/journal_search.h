#ifndef _JOURNAL_SEARCH_H_
#define _JOURNAL_SEARCH_H_

int search(char *search_term, char mode);
int date_match(char *token, char *max_date, char *min_date);
int text_match(char *token, char *search_string);
int extract_dates(char *search_term, char *min_date, char *max_date);
int write_token(char *token);
int initialize_results_file();

#endif // _JOURNAL_SEARCH_H_
