#include "functions.h"


const char function_names[16][5] = {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};

bool set_mov(Functions *function, const char * line, unsigned line_number);
bool set_cmp(Functions *function, const char * line, unsigned line_number);
bool set_add(Functions *function, const char * line, unsigned line_number);
bool set_sub(Functions *function, const char * line, unsigned line_number);
bool set_not(Functions *function, const char * line, unsigned line_number);
bool set_clr(Functions *function, const char * line, unsigned line_number);
bool set_lea(Functions *function, const char * line, unsigned line_number);
bool set_inc(Functions *function, const char * line, unsigned line_number);
bool set_dec(Functions *function, const char * line, unsigned line_number);
bool set_jmp(Functions *function, const char * line, unsigned line_number);
bool set_bne(Functions *function, const char * line, unsigned line_number);
bool set_red(Functions *function, const char * line, unsigned line_number);
bool set_prn(Functions *function, const char * line, unsigned line_number);
bool set_jsr(Functions *function, const char * line, unsigned line_number);
bool set_rts(Functions *function, const char * line, unsigned line_number);
bool set_stop(Functions *function, const char * line, unsigned line_number);


int count_commas(const char* line);

/* 	file: functions.c
 *	function name: function_syntax_checker
 *	parameters: function
 *				line
 *				line number
 *	return: 1 if the syntax is OK
 * */
bool function_syntax_checker(Functions *function, const char * line, unsigned int line_number) {
    int num_of_coomas;
    bool found_function = false;
    char word[LENGTH_OF_STOP];
    memset(word,'\0',LENGTH_OF_STOP);
    num_of_coomas = count_commas(line);
    if (num_of_coomas > 1){
        fprintf(stdout,"ERROR - In a line number %d Overuse of ',' character\n",line_number);
        return found_function;
    }
    if(strstr(line,function_names[0]) != NULL){
        function->number_function = 0;
        return set_mov(function, line, line_number);
    }
    else if(strstr(line,function_names[1]) != NULL) {
        function->number_function = 1;
        return set_cmp(function, line, line_number);
    }
    else if(strstr(line,function_names[2]) != NULL) {
        function->number_function = 2;
        return set_add(function, line, line_number);
    }
    else if(strstr(line,function_names[3]) != NULL) {
        function->number_function = 3;
        return set_sub(function, line, line_number);
    }
    else if(strstr(line,function_names[4]) != NULL) {
        function->number_function = 4;
        if (num_of_coomas != 0) {
            fprintf(stdout, "ERROR - In a line number %d There are too many arguments\n", line_number);
            found_function = false;
            return found_function;
        }
        return set_not(function, line, line_number);
    }
    else if(strstr(line,function_names[5]) != NULL) {
        if (num_of_coomas != 0){
            fprintf(stdout,"ERROR - In a line number %d There are too many arguments\n",line_number);
            found_function = false;
            return found_function;
        }
        return set_clr(function, line, line_number);
    }
    else if(strstr(line,function_names[6]) != NULL) {
        function->number_function = 6;
        return set_lea(function, line, line_number);
    }
    else if(strstr(line,function_names[7]) != NULL) {
        function->number_function = 7;
        if (num_of_coomas != 0){
            fprintf(stdout,"ERROR - In a line number %d There are too many arguments\n",line_number);
            found_function = false;
            return found_function;
        }
        return set_inc(function, line, line_number);
    }
    else if(strstr(line,function_names[8]) != NULL) {
        function->number_function = 8;
        if (num_of_coomas != 0){
            fprintf(stdout,"ERROR - In a line number %d There are too many arguments\n",line_number);
            found_function = false;
            return found_function;
        }
        return set_dec(function, line, line_number);
    }
    else if(strstr(line,function_names[9]) != NULL) {
        function->number_function = 9;
        if (num_of_coomas != 0){
                    fprintf(stdout,"ERROR - In a line number %d There are too many arguments\n",line_number);
                    found_function = false;
                    return found_function;
        }
        return set_jmp(function, line, line_number);
    }
    else if(strstr(line,function_names[10]) != NULL) {
        function->number_function = 10;
        if (num_of_coomas != 0){
        	fprintf(stdout,"ERROR - In a line number %d There are too many arguments\n",line_number);
            found_function = false;
            return found_function;
         }
        return set_bne(function, line, line_number);
    }
    else if(strstr(line,function_names[11]) != NULL)
    {
        function->number_function = 11;
        if (num_of_coomas != 0){
            fprintf(stdout,"ERROR - In a line number %d There are too many arguments\n",line_number);
            found_function = false;
            return found_function;
        }
        return set_red(function, line, line_number);
    }
    else if(strstr(line,function_names[12]) != NULL) {
        function->number_function = 12;
        if (num_of_coomas != 0){
            fprintf(stdout,"ERROR - In a line number %d There are too many arguments\n",line_number);
            found_function = false;
            return found_function;
        }
        return set_prn(function, line, line_number);
    }
    else if(strstr(line,function_names[13]) != NULL) {
        function->number_function = 13;
        return set_jsr(function, line, line_number);
    }
    else if(strstr(line,function_names[14]) != NULL) {
        function->number_function = 14;
        if (num_of_coomas != 0){
            fprintf(stdout,"ERROR - In a line number %d There are too many arguments\n",line_number);
            found_function = false;
            return found_function;
        }
        return set_rts(function, line, line_number);
    }
    else if(strstr(line,function_names[15]) != NULL) {
        function->number_function = 15;
        if (num_of_coomas != 0){
            fprintf(stdout,"ERROR - In a line number %d There are too many arguments\n",line_number);
            found_function = false;
            return found_function;
        }
        return set_stop(function, line, line_number);
    }
    else{
        fprintf(stdout,"ERROR - Does not recognize the function in line number %d\n",line_number);
        return false;
    }

}

/* 	file: functions.c
 *	function name: count_commas
 *	parameters: line
 *	return: number of commas
 * */
int count_commas(const char* line) {
    int count = 0;
    const char* ptr = line;
    while (*ptr != '\0') {
        if (*ptr == ',') {
            count++;
        }
        ptr++;
    }
    return count;
}

/* 	file: functions.c
 *	function name: has_spaces
 *	parameters: word
 *	return: 1 if the word had spaces
 * */
int has_spaces(char *word){

    int has_spaces = 0;
    int i;
    for ( i = 0; i < strlen(word); i++) {
        if (isspace(word[i])) {
            has_spaces = 1;
            break;
        }
    }
    return has_spaces;
}

/* 	file: functions.c
 *	function name: clean_left_spaces
 *	parameters: word
 * */
void clean_left_spaces(char* word) {
    int i, j;
    unsigned int len = strlen(word);

    /* Find the first non-space character*/
    for (i = 0; i < len; i++) {
        if (word[i] != ' ') {
            break;
        }
    }

    /* Shift the string to remove the left spaces*/
    if (i > 0) {
        for (j = 0; j < len - i; j++) {
            word[j] = word[j + i];
        }
        word[j] = '\0';
    }
}

/* 	file: functions.c
 *	function name: strtrim
 *	parameters: string
 *	return: word without spaces in the start and the end of the word
 * */
char * strtrim(char *str) {
    char *start = str;
    char *end = str + strlen(str) - 1;

    /* Trim leading whitespace characters*/
    while (isspace(*start)) {
        start++;
    }

    /* Trim trailing whitespace characters*/
    while (end > start && isspace(*end)) {
        end--;
    }
    *(end+1) = '\0'; /* Add null terminator*/

    return start;
}

/*Type1 : mov, add, sub */
bool set_function_values_type1(Functions * function,const char *line,unsigned int line_number) {
    int number_of_line = 1; /* initialize the line number to 1 */
    bool compilation_errors = true; /* initialize the compilation errors flag to true */
    char *fun_name = NULL;
    char *name1 = NULL;
    char *name2 = NULL;
    char *line_copy = NULL;
    /* create a copy of the input line */
    line_copy = malloc(strlen(line) + 1);
    strcpy(line_copy, line);
    if (line_copy == NULL) {
        handle_alloc_error();
    }
    fun_name = strtok(line_copy, " "); /* get the first word (function name) */
    name1 = strtok(NULL, ","); /* get the second word (up to the comma) */
    name2 = strtok(NULL, "\n"); /* get the third word (up to the end of the line) */

    if (strlen(fun_name) != LENGTH_OF_COMMAND){
        fprintf(stdout,"ERROR - In a line number %d %s function name should be free of other characters\n",line_number, fun_name);
        compilation_errors = false;
        return compilation_errors;
    }

    if(name2 == NULL || name1 == NULL){
        compilation_errors = false;
        fprintf(stdout,"ERROR - In a line number %d %s function accepts two operands\n",line_number, fun_name);
        return compilation_errors;
    }

    name1 = strtrim(name1); /* remove trailing spaces from name1*/
    name2 = strtrim(name2); /* remove trailing spaces from name2*/

    /* allocate memory for the source name and copy it*/
    strcpy(function->function_name, fun_name);

    /* allocate memory for the function name and copy it*/
    strcpy(function->source_name, name1);

    /* allocate memory for the target name and copy it*/
    strcpy(function->target_name, name2);

    /* check the type of the first variable and set the method source accordingly*/
    if (('+' == name1[0] || '-' == name1[0]) || (name1[10] >= 48 && name1[0] <= 57)) {
         function->method_source = 1;
         number_of_line += 1;/* increment the line number*/
    }
    else if (name1[1] == 'r' && name1[0] == '@' && strlen(name1) == 3 && (name1[2] >= 48 && name1[2] <= 55)) {
        function->method_source = 5;
        number_of_line += 1;
    }
    else if ((name1[0] < 91 && name1[0] > 64) || (name1[0] < 123 && name1[0] > 96)) {
        if (has_spaces(name1) == 1){
            fprintf(stdout,"ERROR - In a line number %d This variable %s cannot contain spaces\n",line_number, name1);
            compilation_errors = false; /* set compilation errors flag to false*/
        }
        function->method_source = 3;
        number_of_line += 1;
    }
    /* check the type of the second variable and set the method target accordingly*/
    if (name2[0] == '-' || name2[0] == '+' ||(name2[0] >= 48 && name2[0] <= 57)) {
        fprintf(stdout,"ERROR - In a line number %d This variable %s is not possible as a target operator in the %s function\n",line_number, name2, fun_name);
        compilation_errors = false;
    }
    else if (name2[0] == '@' && name2[1] == 'r' && strlen(name2) == 3 && (name2[2] >= 48 && name2[2] <= 55)) {
        function->method_target = 5;
        number_of_line += 1;
    }
    else if ((name2[0] < 91 && name2[0] > 64) || (name2[0] < 123 && name2[0] > 96)) {
        if (has_spaces(name2) == 1){
            fprintf(stdout,"ERROR - In a line number %d This variable %s cannot contain spaces\n",line_number, name2);
            compilation_errors = false; /* set compilation errors flag to false*/
        }
        function->method_target = 3;
        number_of_line += 1;     
    }
    /*Checking if two operators are registers*/
    if((name2[0] == '@' && name1[0] == '@') &&( name2[1] == 'r' && name1[1] == 'r') && strlen(name1) == 3 && strlen(name2) == 3)
            number_of_line -= 1;
    function->number_of_lines = number_of_line;
    free(line_copy);
    return compilation_errors;

}
/*Type2 : cmp */
bool set_function_values_type2(Functions * function,const char *line,unsigned int line_number) {
    int number_of_line = 1;
    bool compilation_errors = true;
    char *fun_name = NULL;
    char *name1 = NULL;
    char *name2 = NULL;
    char *line_copy = NULL;
    line_copy = malloc(strlen(line) + 1);
    strcpy(line_copy, line);
    if (line_copy == NULL) {
        handle_alloc_error();
    }
    fun_name = strtok(line_copy, " ");
    name1 = strtok(NULL, ",");
    name2 = strtok(NULL, "\n");
    if (strlen(fun_name) != LENGTH_OF_COMMAND){
        fprintf(stdout,"ERROR - In a line number %d %s The function name should be free of other characters\n",line_number, fun_name);
        compilation_errors = false;
        return compilation_errors;
    }
    if(name2 == NULL || name1 == NULL){
        compilation_errors = false;
        fprintf(stdout,"ERROR - In a line number %d %s function accepts two operand\n",line_number, fun_name);
        return compilation_errors;
    }
    name1 = strtrim(name1);
    name2 = strtrim(name2);
    /* allocate memory for the function name and copy it*/
    strcpy(function->function_name, fun_name);
    /* allocate memory for the function name and copy it*/
    strcpy(function->source_name, name1);
    /* allocate memory for the target name and copy it*/
    strcpy(function->target_name, name2);
    /* check the type of the first variable and set the method source accordingly*/
    if (name1[0] == '+' || name1[0] == '-' || (name1[0] >= '0' && name1[0] <= '9')) {
    	function->method_source = 1;
        number_of_line += 1;
    }
    else if (name1[0] == '@' && name1[1] =='r' && strlen(name1) == 3 && (name1[0] >= '0' && name1[0] <= '7')) {
        function->method_source = 3;
        number_of_line += 1;
    }
    else if ((name1[0] < 91 && name1[0] > 64) || (name1[0] < 123 && name1[0] > 96)) {
        if (has_spaces(name1) == 1){
            fprintf(stdout,"ERROR - In a line number %d This variable %s cannot contain spaces\n",line_number, name1);
            compilation_errors = false; /* set compilation errors flag to false*/
        }
        function->method_source = 1;
        number_of_line += 1;
    }
    else{
        fprintf(stdout,"ERROR - In a line number %d This variable %s does not fit a function %s\n",line_number, name2, fun_name);
        compilation_errors = false; /* set compilation errors flag to false*/
    }
    /* check the type of the second variable and set the method target accordingly*/
    if (name2[0] == '+' || name2[0] == '-' || (name2[0] >= '0' && name2[0] <= '9')) {
    	function->method_source = 1;
    	number_of_line += 1;/* increment the line number*/
    }
    else if (name2[0] == '@' && name2[1] == 'r'&& strlen(name2) == 3 && (name2[1] >= '0' && name2[1] <= '7')) {
        function->method_target = 5;
        number_of_line += 1;
    }
    else if ((name2[0] < 91 && name2[0] > 64) || (name2[0] < 123 && name2[0] > 96)) {
        if (has_spaces(name2) == 1){
            fprintf(stdout,"ERROR - In a line number %d This variable %s cannot contain spaces\n",line_number, name2);
            compilation_errors = false; /* set compilation errors flag to false*/
        }
        function->method_target = 3;
        number_of_line += 1;
    }
    else{
        fprintf(stdout,"ERROR - In a line number %d This variable %s does not fit a function %s\n",line_number, name2, fun_name);
        compilation_errors = false; /* set compilation errors flag to false*/
    }
    if((name2[0] == '@' && name1[0] == '@') &&( name2[1] == 'r' && name1[1] == 'r') && strlen(name1) == 3 && strlen(name2) == 3){
        number_of_line -= 1;
    }
    function->number_of_lines = number_of_line;
    free(line_copy);
    return compilation_errors;

}
/*Type3 : not, clr, inc, dec,jmp, bne, red, jsr  */
bool set_function_values_type3(Functions * function,const char *line,unsigned int line_number) {
    int number_of_line = 1; /* initialize the line number to 1*/
    bool compilation_errors = true; /* initialize the compilation errors flag to true*/
    char *fun_name = NULL;
    char *name2 = NULL;
    char *line_copy = NULL;
    line_copy = malloc(strlen(line) + 1);
    strcpy(line_copy, line);
    if (line_copy == NULL) {
        handle_alloc_error();
    }
    fun_name = strtok(line_copy, " "); /* get the first word (function name) */
    name2 = strtok(NULL, "\n"); /* get the third word (up to the end of the line) */
    if (strlen(fun_name) != LENGTH_OF_COMMAND){
        fprintf(stdout,"ERROR - In a line number %d %s The function name should be free of other characters\n",line_number, fun_name);
        compilation_errors = false;
        return compilation_errors;
    }
    if(name2 == NULL){
        compilation_errors = false;
        fprintf(stdout,"ERROR - In a line number %d %s function accepts only one operand\n",line_number, fun_name);
        return compilation_errors;
    }
    name2 = strtrim(name2);


    strcpy(function->function_name, fun_name);
    strcpy(function->target_name, name2);
    if (name2[0] == '-' || name2[0] == '+' || (name2[0] >= '0' && name2[0] <= '9')) {
        fprintf(stdout,"ERROR - In a line number %d This variable %s does not fit a function %s\n",line_number, name2, fun_name);
        compilation_errors = false;
    }
    else if (name2[0] == '@' && name2[1] == 'r' && strlen(name2) == 3 && (name2[2] >= '0' && name2[2] <= '7')) {
        function->method_target = 5;
        number_of_line += 1;

    }
    else if ((name2[0] < 91 && name2[0] > 64) || (name2[0] < 123 && name2[0] > 96)) {
        if (has_spaces(name2) == 1){
            fprintf(stdout,"ERROR - In a line number %d This variable %s cannot contain spaces\n",line_number, name2);
            compilation_errors = false; /* set compilation errors flag to false*/
        }
        function->method_target = 3;
        number_of_line += 1;
    }
    else{
        fprintf(stdout,"ERROR - In a line number %d This variable %s does not fit a function %s\n",line_number, name2, fun_name);
        compilation_errors = false; /* set compilation errors flag to false*/
    }

    function->number_of_lines = number_of_line;
    free(line_copy); /* free the memory allocated by strdup */
    return compilation_errors;/*return the flag*/
}
/*Type4 : lea */
bool set_function_values_type4(Functions * function,const char *line,unsigned int line_number) {
    int number_of_line = 1; /* initialize the line number to 1*/
    bool compilation_errors = true; /* initialize the compilation errors flag to true*/
    char *fun_name = NULL;
    char *name1 = NULL;
    char *name2 = NULL;
    char *line_copy = NULL;
    /* create a copy of the input line */
    line_copy = malloc(strlen(line) + 1);
    strcpy(line_copy, line);
    if (line_copy == NULL) {
        handle_alloc_error();
    }
    fun_name = strtok(line_copy, " "); /* get the first word (function name) */
    name1 = strtok(NULL, ","); /* get the second word (up to the comma) */
    name2 = strtok(NULL, "\n"); /* get the third word (up to the end of the line) */
    if (strlen(fun_name) != LENGTH_OF_COMMAND){
        fprintf(stdout,"ERROR - In a line number %d %s The function name should be free of other characters\n",line_number, fun_name);
        compilation_errors = false;
        return compilation_errors;
    }
    if(name2 == NULL || name1 == NULL){
        compilation_errors = false;
        fprintf(stdout,"ERROR - In a line number %d %s function accepts two operand\n",line_number, fun_name);
        return compilation_errors;
    }
    name1 = strtrim(name1); /* remove trailing spaces from name1*/
    name2 = strtrim(name2); /* remove trailing spaces from name2*/
    strcpy(function->function_name, fun_name);
    /* allocate memory for the function name and copy it */
    strcpy(function->source_name, name1);
    /* allocate memory for the target name and copy it*/
    strcpy(function->target_name, name2);
    if ((name1[0] == '@')){
        compilation_errors = false;
        fprintf(stdout,"ERROR - In a line number %d This variable %s is not possible as a source operator in the %s function\n",line_number, name1, fun_name);
        return compilation_errors;
    }
    else if ((name1[0] < 91 && name1[0] > 64) || (name1[0] < 123 && name1[0] > 96)) {
        if (has_spaces(name1) == 1){
            fprintf(stdout,"ERROR - In a line %s This variable %s cannot contain spaces\n",line, name1);
            compilation_errors = false; /* set compilation errors flag to false*/
        }
        function->method_source = 3;
        number_of_line += 1;
    }
    else{
        compilation_errors = false;
        fprintf(stdout,"ERROR - In a line number %d This variable %s is not possible as a source operator in the %s function\n",line_number, name1, fun_name);
        return compilation_errors;
    }
    /* check the type of the second variable and set the method target accordingly*/
    if (name2[0] == '-' || name2[0] == '+' || (name2[0] >= '0' && name2[0] <= '9' )) {
        fprintf(stdout,"ERROR - In a line number %d This variable %s is not possible as a target operator in the %s function\n",line_number, name2, fun_name);
        compilation_errors = false;
    }
    else if ((name2[0] == '@' && name2[1] == 'r' && strlen(name2) == 3) && (name2[2] >= '0' && name2[2] <= '7')) {
        function->method_target = 5;
        number_of_line += 1;

    }
    else if ((name2[0] < 91 && name2[0] > 64) || (name2[0] < 123 && name2[0] > 96)) {
        if (has_spaces(name2) == 1){
            fprintf(stdout,"ERROR - In a line number %d This variable %s cannot contain spaces\n",line_number, name2);
            compilation_errors = false; /* set compilation errors flag to false*/
        }
        function->method_target = 3;
        number_of_line += 1;
    }
    else{
        fprintf(stdout,"ERROR - In a line number %d This variable %s does not fit a function %s\n",line_number, name2, fun_name);
        compilation_errors = false; /* set compilation errors flag to false*/
    }
    function->number_of_lines = number_of_line;
    free(line_copy); /* free the memory allocated by strdup */
    return compilation_errors;/* return the flag */
}
/*Type5 : prn */
bool set_function_values_type5(Functions * function,const char *line,unsigned int line_number)
{
    int number_of_line = 1; /* initialize the line number to 1*/
    bool compilation_errors = true; /* initialize the compilation errors flag to true*/
    char *fun_name = NULL;
    char *name2 = NULL;
    char *line_copy = NULL;
    /* create a copy of the input line */
    line_copy = malloc(strlen(line) + 1);
    strcpy(line_copy, line);
    if (line_copy == NULL) {
        handle_alloc_error();
    }
    fun_name = strtok(line_copy, " "); /* get the first word (function name) */
    name2 = strtok(NULL, "\n"); /* get the second word (up to the end of the line) */
    if (strlen(fun_name) != LENGTH_OF_COMMAND){
        fprintf(stdout,"ERROR - In a line number %d %s The function name should be free of other characters\n",line_number, fun_name);
        compilation_errors = false;
        return compilation_errors;
    }
    if(name2 == NULL){
        compilation_errors = false;
        fprintf(stdout,"ERROR - In a line number %d %s function accepts one operand\n",line_number, fun_name);
        return compilation_errors;
    }
    name2 = strtrim(name2); /* remove trailing spaces from name1*/
    /* allocate memory for the function name and copy it*/
    strcpy(function->function_name, fun_name);
    /* allocate memory for the target name and copy it*/
    strcpy(function->target_name, name2);
    /* check the type of the first variable and set the method source accordingly*/
    if (name2[0] == '@' && name2[1] == 'r' && strlen(name2) ==3 ) {
            function->method_target = 5;
            number_of_line += 1;/* increment the line number*/
    }
    else if (name2[0] == '+' || name2[0] == '-'|| (name2[0] >= '0' && name2[0] <= '9')) {
        function->method_target = 1;
        number_of_line += 1;

    }
    else if ((name2[0] < 91 && name2[0] > 64) || (name2[0] < 123 && name2[0] > 96)) {
        if (has_spaces(name2) == 1){
            fprintf(stdout,"ERROR - In a line number %d This variable %s cannot contain spaces\n",line_number, name2);
            compilation_errors = false; /* set compilation errors flag to false*/
        }
        function->method_target = 3;
        number_of_line += 1;

    }
	else{
        fprintf(stdout,"ERROR - In a line number %d This variable %s does not fit a function %s\n",line_number, name2, fun_name);
        compilation_errors = false; /* set compilation errors flag to false*/
    }
    function->number_of_lines = number_of_line;
    free(line_copy); /* free the memory allocated by strdup */
    return compilation_errors;/*return the flag*/
}
/* Type6: stop, rts */
bool set_function_values_type6(Functions * function,const char *line,unsigned int line_number) {
    int number_of_line = 1; /* initialize the line number to 1*/
    bool compilation_errors = true; /* initialize the compilation errors flag to true*/
    char *fun_name = NULL;
    char *name2 = NULL;
    char *line_copy = NULL;
    /* create a copy of the input line */
    line_copy = malloc(strlen(line) + 1);
    strcpy(line_copy, line);
    if (line_copy == NULL) {
        handle_alloc_error();
    }
    fun_name = strtok(line_copy, " "); /* get the first word (function name) */
    name2 = strtok(NULL, "\n"); /* get the third word (up to the end of the line) */
    if (strlen(fun_name) != LENGTH_OF_STOP && strlen(fun_name) != LENGTH_OF_COMMAND + 1){
        fprintf(stdout,"ERROR - In a line number %d %s The function name should be free of other characters\n",line_number, fun_name);
        compilation_errors = false;
        return compilation_errors;
    }
    if (name2 != NULL ) {
        if ((strlen(name2) != 1)) {
            compilation_errors = false;
            fprintf(stdout, "ERROR - In a line number %d The function %s does not accept operators\n", line_number,
                    fun_name);
            return compilation_errors;
        }
    }
    else {
/* allocate memory for the function name and copy it*/
            strcpy(function->function_name, fun_name);
            function->number_of_lines = number_of_line;
            function->number_of_lines = number_of_line;
            free(line_copy); /* free the memory allocated by strdup */
            return compilation_errors;/*return the flag*/
        }
    return compilation_errors;/*return the flag*/
}

bool set_mov(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type1(function,line,line_number);
}

bool set_cmp(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type2(function,line,line_number);
}

bool set_add(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type1(function,line,line_number);
}

bool set_sub(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type1(function,line,line_number);
}

bool set_not(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type3(function,line,line_number);
}

bool set_clr(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type3(function,line,line_number);
}

bool set_lea(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type4(function,line,line_number);
}

bool set_inc(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type3(function,line,line_number);
}

bool set_dec(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type3(function,line,line_number);
}

bool set_jmp(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type3(function,line,line_number);
}

bool set_bne(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type3(function,line,line_number);
}

bool set_red(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type3(function,line,line_number);
}

bool set_prn(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type5(function,line,line_number);
}

bool set_jsr(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type3(function,line,line_number);
}

bool set_rts(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type6(function,line,line_number);
}

bool set_stop(Functions *function, const char * line, unsigned line_number){
    return set_function_values_type6(function,line,line_number);
}

void print_function_name_error(unsigned line_number){
    fprintf(stdout,"ERROR - In line number %d Does not recognize the function name\n",line_number);
}

