#ifndef C_TOOLS_H
#define C_TOOLS_H


#include <limits.h>
#include <errno.h>
#include "labels.h"
#include "data_structers.h"

void write_function_to_file(Functions* func, char* file_name, unsigned int decimal_address);

void write_word_to_ob_file(char * word, char* file_name, unsigned int decimal_address);

void write_num_to_ob_file(int num, char* file_name, unsigned int decimal_address);


#endif /*C_TOOLS_H*/

