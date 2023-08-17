#ifndef ASSEMBLY_DATA_STRUCTERS_H
#define ASSEMBLY_DATA_STRUCTERS_H

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "exceptions.h"

#define START_DECIMAL_ADDRESS 100

#define MAX_LINE_LENGTH 82
#define MAX_NAME_MACROS 31
#define MAX_NAME_MACRO 500
#define MAX_LABEL_NAME_LENGTH 30
#define MAX_STRING_LENGTH 31
#define MAX_FILE_NAME 101
#define MAX_LEN_LABEL_NAME 200

#define START_MACRO "mcro"
#define END_MACRO "endmcro"

#define LENGTH_OF_COMMAND 3
#define LENGTH_OF_STOP 5
#define LEN_OF_FUNCTION_NAME 3
#define LEN_OF_STOP_FUNCTION 4
#define NUMBER_OF_FUNCTIONS 15
#define LEN_OF_MEMORY_WORD 12

#define END_OF_OUTPUT_FILE ".am"
#define MAX_NAME_MACROS 31
#define END_OF_EXT_FILE ".ext"
#define END_OF_ENT_FILE ".ent"
#define END_OF_INPUT_FILE ".as"
#define END_OF_OB_FILE ".ob"

#define NOTE_SING ';'
#define SPACE_SING ' '
#define TAB_SING '\t'
#define LABELS_SING ':'
#define DOT_SING '.'
#define COMMA_SING ','
#define QUOTATION_MARKS_SING '"'
#define END_OF_STRING_SING '\0'

#define PLUS_SING '+'
#define MINUS_SING '-'
#define SIZE_TMP_DATA 5

#define NAME_EXTERNAL ".extern"
#define NAME_ENTRY ".entry"
#define NAME_STRING ".string"
#define NAME_DATA ".data"

#define NAME_LEN_IN_FUNCTION 31

typedef enum {UNKNOWN, CODE, DATA, STRING, ENTRY, EXTERNAL} SYMBOL_TYPE;

typedef enum {ERROR, SUCCESS} RESULT;

typedef struct Integer{
    int num;
    struct Integer * next;
} Integer;

typedef struct Data{
    unsigned int number_of_elements;
    Integer * integer;
} Data;

typedef struct String{
    unsigned int number_of_elements;
    char * letter;
} String;

typedef struct Functions{
    char  function_name[NAME_LEN_IN_FUNCTION];
    char  target_name[NAME_LEN_IN_FUNCTION];
    char  source_name[NAME_LEN_IN_FUNCTION];
    int number_function;
    int method_target;
    int method_source;
    unsigned int number_of_lines;
} Functions;

typedef struct Node{
    char * label_name;
    bool is_label;
    unsigned int text_line;
    unsigned int decimal_address;
    unsigned int number_of_lines;
    SYMBOL_TYPE type;
    Functions * functions;
    Data * data;
    String * string;
    struct Node * next;
} Node;

typedef struct InputInformation{
    char* file_name;
    unsigned int DC;
    unsigned int IC;
    RESULT result;
    Node * head_nodes;
}InputInformation;

typedef struct Node_m {
    char string[NAME_LEN_IN_FUNCTION];
    struct Node_m * next;
}Node_m;

typedef struct LinkedList {
    struct Node_m * head;
}LinkedList;


#endif /*ASSEMBLY_DATA_STRUCTERS_H*/
