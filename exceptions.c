#include "exceptions.h"


static const char * _file_name = NULL;


void set_file_name(const char * file_name) {
    _file_name = file_name;
}

void handle_alloc_error() {
    fprintf(stdout, "FATAL ERROR: Out of memory\n");
    exit(1);
}

void print_error(char * error, unsigned int text_line_number, const char * value) {
    if (text_line_number == 0)
        fprintf(stdout, "ERROR - %s : %s.\n", error, _file_name);
    else if(value == NULL)
        fprintf(stdout, "ERROR - In file %s line %d : %s.\n", _file_name, text_line_number, error);
    else
        fprintf(stdout,     "ERROR - In file %s line %d : '%s' %s.\n", _file_name, text_line_number,value, error);
}
