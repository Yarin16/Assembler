#include "statements.h"

/* 	file: tools.c
 *	function name: set_string
 *	parameters: Node
 *				line
 *	return: 1 is success
 * This function get a .string line and set the values in node->String
 * expected input: "string"
 */
RESULT set_string(Node * node, const char * line) {
    unsigned int index = 0, start = 0, end = 1;
    node->string = init_string();
    if (!(line[0] == SPACE_SING || line[0] == TAB_SING)){
        print_error("Need to have space after '.string'", node->text_line, NULL);
        return ERROR;
    }
    while(line[index] != '\n') {
        if( line[index] == '"' ){
        	if((start == 0) && (end == 1)){
        		start = index;
        		end = 0;
        	}
        	else{
                end = index;
                break;
        	}
        }
        index++;
    }
    index = end + 1;
    while (line[index] != '\n') {
        if ((line[index] == SPACE_SING || line[index] == TAB_SING)){
            print_error("Illegal text after end of string", node->text_line, NULL);
            return ERROR;
        }
        index++;
    }
    if (line[end] != '"'){
        printf(" 1ERROR: string not end as excepted with - %s %c %d ",line, line[end], end);
        return ERROR;
    }
    node->string->letter = (char  *) malloc(sizeof (char )*(end-start));
    for (index = start+1 ; index < end ; index++) {
        node->string->letter[node->string->number_of_elements] = line[index];
        node->string->number_of_elements++;
    }
    node->string->letter[node->string->number_of_elements] = END_OF_STRING_SING;
    node->string->number_of_elements++;
    return SUCCESS;
}

/* 	file: tools.c
 *	function name: set_data
 *	parameters: Node
 *				line
 *	return: 1 is success
 *  This function get a .data line and set the values in node->data
 *  the function split integer by integer and set a list in data of Integer struct
 *  expected input: 1,2,3,-4,+5
 */
RESULT set_data(Node * node, const char * line) {
    char * data_input;
    char tmp[SIZE_TMP_DATA];
    int i = 0, j = 0, start = 0, end = 0, len = 0, number_of_comma = 0;
    int number_value = 0;
    Integer * current_integer = NULL;

    node->data = init_data();

    /* check for space after '.data' */
    if (line[0] != SPACE_SING && line[0] != TAB_SING && line[0] != '\n') {
        print_error("Need to have space after '.data'", node->text_line, NULL);
        return ERROR;
    }

    /* check for values after '.data' */
    for (i = 0; line[i] != '\n'; i++)
        if (line[i] != SPACE_SING && line[i] != TAB_SING)
            break;
    if(line[i] == '\n'){
        print_error("Missing values in '.data'", node->text_line, NULL);
        return ERROR;
    }
    /* check for missing comma: */
    for (i = 0; line[i] != '\n' && i < strlen(line); i++){
        if (line[i] == COMMA_SING)
            number_of_comma++;
        else if (line[i] != SPACE_SING && line[i] != TAB_SING) {
            number_value++;
            while (line[i] != COMMA_SING && line[i] != SPACE_SING && line[i] != TAB_SING) {
                if(line[i] == '\n')
                    break;
                i++;
            }            if(line[i] == COMMA_SING)
                number_of_comma++;
        }
    }
    if (number_value != 0 && number_of_comma != number_value -1) {
        if (number_of_comma < number_value -1)
            print_error("Missing comma", node->text_line, NULL);
        else
            print_error("Extra comma", node->text_line, NULL);
        return ERROR;
    }
    /* Clear space : */
    data_input = (char *) malloc(sizeof (char)* strlen(line));
    memset(data_input, '\0', strlen(line));
    for (i=0; line[i] != '\n' && i < strlen(line); i++) {
        if (!(line[i] == SPACE_SING || line[i] == TAB_SING)) {
            data_input[j] = line[i];
            j++;
        }
    }
    data_input[j] = '\n';
    len = j;
    /* Check how the data end - with a comma*/
    if (data_input[j-1] == COMMA_SING){
        print_error("Illegal comma in the end", node->text_line, NULL);
        free(data_input);
        return ERROR;
    }
    /* Check if there are multiple consecutive commas*/
    for (i=0; i < strlen(data_input); i++){
        if (*(data_input+i) == COMMA_SING && i < (strlen(data_input) - 1)){
            if (*(data_input + i + 1) == ','){
                print_error("multiple consecutive commas", node->text_line, NULL);
                free(data_input);
                return ERROR;
            }
        }
    }
    for ( i = 0 ; i < len ; i++) {
        start = i;
        memset( tmp , '\0' , SIZE_TMP_DATA );
        while (data_input[i] != COMMA_SING){
            if (i == len)
                break;
            i++;
        }
        end = i;
        strncpy(tmp,data_input+start,end-start);
        /*checking if contains only numbers with leading minus or plus sign*/
        for(j = 0; j < end - start; j++){
            if(!isdigit(tmp[j])){ /* none number parameter in .data*/
                if (((tmp[j] == '-' || tmp[j] == '+') && j != 0) || (tmp[j] != '-' && tmp[j] != '+')) {
                    /* has minus or plus but not in the lead or not a number or minus/plus sign*/
                    print_error("argument is not a valid integer number", node->text_line, tmp);
                    free(data_input);
                    return ERROR;
                }
            }
        }
        if (node->data->integer == NULL) {
            node->data->integer = init_integer();
            current_integer = node->data->integer;
        }
        else {
            current_integer->next = init_integer();
            current_integer = current_integer->next;
        }
        current_integer->num =  strtol(tmp, NULL, 10);
        node->data->number_of_elements++;
    }

    free(data_input);
    return SUCCESS;
}
