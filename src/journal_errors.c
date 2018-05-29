#include "../include/journal.h"
#include "../include/journal_util.h"

int error_log(char *error_msg)
{
    append_to_file(error_log_file, error_msg);

    return 0;
}
