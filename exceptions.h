
#ifndef C_EXCEPTIONS_H
#define C_EXCEPTIONS_H

#include <stdio.h>
#include <stdlib.h>



void set_file_name(const char * file_name);

void handle_alloc_error();

void print_error(char * error, unsigned int text_line_number, const char * value);

#endif /*C_EXCEPTIONS_H*/
