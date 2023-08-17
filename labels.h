#ifndef C_LABELS_H
#define C_LABELS_H

#include "data_structers.h"


void set_label_input_information(InputInformation* inputInformation);

bool checking_if_the_label_exists(Functions *function, unsigned int line_number);

void print_label_list(InputInformation* input_information);

bool is_label_exist(const char * label_name);

unsigned int get_label_address(const char * label_name);

bool is_valid_label(unsigned int text_line, const char * label_name);

bool it_is_extern(const char * label_name);

bool it_is_entry(const char * label_name);

#endif /*C_LABELS_H*/
