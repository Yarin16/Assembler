#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H

#include "data_structers.h"


LinkedList * crete_macro_list(char *name_file, InputInformation * inputInformation);

void pre_assembler(InputInformation * inputInformation, char * name_file);

#endif /*C_INIT_FILES_H*/
