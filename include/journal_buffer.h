#ifndef _JOURNAL_BUFFER_H_
#define _JOURNAL_BUFFER_H_

int buffer();
int wrap_line(int ypos, int xpos, int *previous_line_length);
int backspace_func(int ypos, int xpos);
int nl_func(int ypos);

#endif  // _JOURNAL_BUFFER_H_
