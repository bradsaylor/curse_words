#ifndef _JOURNAL_SEARCH_H_
#define _JOURNAL_SEARCH_H_

int search(char *search_term, int mode);
int tokenize_file(char *filename, char *token);
int search_token_for_date(char *token);
int search_token_for_text(char *token, char *text);
int search_results_display();

#endif // _JOURNAL_SEARCH_H_
