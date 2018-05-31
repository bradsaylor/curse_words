#include <stdio.h>
#include <unistd.h>

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

    return 0;
}
