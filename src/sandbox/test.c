#include <stdio.h>
#include <string.h>

int remove_chars(char *str, char *exclude_str);

int main()
{
    char date1[9], date2[9];

    char str[] = "<2018-03-05> <2019-06-07>";

    remove_chars(str, "<>-");

    sscanf(str, "%s %s", date1, date2);

    printf("\ndate1: '%s'\t\tdate2: '%s'\n", date1, date2);
    
    return 0;
}

int remove_chars(char *str, char *exclude_str)
{
    int length = (int)strlen(str);
    char *read_ptr = str;
    char write_ptr[length];
    int write_pos = 0;
    char *result;
    char temp[2];

    
    for(int count = 0; count < length; count ++) {

	sprintf(temp, "%c", (*read_ptr));
	result = strstr(exclude_str, temp);
	
	if(result == NULL) {
	    write_ptr[write_pos] = (*read_ptr);
	    write_pos ++;
	}
	read_ptr++;
    }

    write_ptr[write_pos] = '\0';
    strcpy(str, write_ptr);
    
    return 0;
}
