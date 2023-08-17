
#include "first_pass.h"


RESULT set_into_node(Node * node, const char * line);
RESULT set_into_statement(Node * node, const char * line);
RESULT set_into_function(Node * nod,  const char * line);
RESULT set_label_name(Node * node, const char * line);
bool is_line_with_label(const char * line);
unsigned int get_label_position( const char * line );
RESULT set_statement_label_name( Node * node, const char * line );
bool is_statement( const char * line );
unsigned int get_statement_position( const char * line );


void  run_first_pass( InputInformation * input_information ) {
    Node * current_node_ptr = NULL;
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int index = 0, line_number =1;
    RESULT tmp_result = SUCCESS;
    FILE * file;
    file = fopen(input_information->file_name, "r");
    if( ! file ) {
        perror(input_information->file_name);
        input_information->result = ERROR;
        return;
    }
    while( fgets( line, MAX_LINE_LENGTH, file ) ){
        printf( "LINE: %s", line );
        for( index = 0 ; line[index] != '\0' ; index++ );
        line[index] = (line[index-1] =='\n') ? '\0': '\n' ;
        if(input_information->head_nodes == NULL) {
            input_information->head_nodes = init_node();
            current_node_ptr = input_information->head_nodes;
        }
        else if(tmp_result == SUCCESS){
            current_node_ptr->next = init_node();
            current_node_ptr = current_node_ptr->next;
        }
        current_node_ptr->text_line = line_number;
        line_number++;
        tmp_result = SUCCESS;
        if(is_line_with_label(line)) {
            tmp_result = set_label_name(current_node_ptr, line);
            input_information->result = input_information->result == SUCCESS ? tmp_result : ERROR;
            if (tmp_result == SUCCESS) {
                current_node_ptr->is_label = true;
                /* Check for space after ':' */
                if (line[get_label_position(line) + 1] != SPACE_SING &&
                    line[get_label_position(line) + 1] != TAB_SING) {
                    print_error("Need to have space after ':' ", current_node_ptr->text_line, NULL);
                    input_information->result = ERROR;
                }
            }
            tmp_result = set_into_node(current_node_ptr, line + get_label_position(line) + 1);
        }
        else
            tmp_result = set_into_node(current_node_ptr, line);
        input_information->result = input_information->result == SUCCESS ? tmp_result : ERROR;
        memset( line , '\0' , MAX_LINE_LENGTH );
    }
    /* Close file */
    if (fclose(file)) {
        perror(input_information->file_name);
    }
}

void set_address_and_dc_ic(InputInformation * input_information){
    Node * current_node_ptr = input_information->head_nodes;
    unsigned int next_address = START_DECIMAL_ADDRESS;
    while( current_node_ptr != NULL ) {
        if( current_node_ptr->type == CODE ) {
            current_node_ptr->decimal_address = next_address;
            current_node_ptr->number_of_lines = current_node_ptr->functions->number_of_lines;
            input_information->IC += current_node_ptr->number_of_lines;
            if( ! checking_if_the_label_exists( current_node_ptr->functions, current_node_ptr->number_of_lines ) ){
            	printf("\nError: Unable to open file cood_first\n");
            	input_information->result = ERROR;
            }
             
        }
        else if( current_node_ptr->type == DATA ) {
            current_node_ptr->decimal_address = next_address;
            current_node_ptr->number_of_lines = current_node_ptr->data->number_of_elements;
            input_information->DC += current_node_ptr->number_of_lines;
        }
        else if( current_node_ptr->type == STRING ) {
            current_node_ptr->decimal_address = next_address;
            current_node_ptr->number_of_lines = current_node_ptr->string->number_of_elements;
            input_information->DC += current_node_ptr->number_of_lines;
        }
        else if( current_node_ptr->type == ENTRY ) {
            if( ! is_label_exist( current_node_ptr->label_name ) ) {
                print_error("Entry label isn't exist in the file", current_node_ptr->text_line, current_node_ptr->label_name);
                input_information->result = ERROR;
            }
        }
        else if( current_node_ptr->type == EXTERNAL ) {
            if( is_label_exist( current_node_ptr->label_name ) ) {
                print_error("Extern label is already exist in the file", current_node_ptr->text_line, current_node_ptr->label_name);
                input_information->result = ERROR;
            }
        }
        next_address += current_node_ptr->number_of_lines;
        current_node_ptr = current_node_ptr->next;
    }
}

RESULT set_into_node(Node * node, const char * line){
    RESULT result = SUCCESS;
    /* Pass on the rest of line and set it into statement or function */
    if (is_statement(line)){
        result  = set_into_statement(node, line + get_statement_position(line));
        return result;
    }
    else {
        result = set_into_function(node, line);
        return result;
    }
}

RESULT set_into_statement(Node * node, const char * line) {
    unsigned int index = 0;
    RESULT result = SUCCESS;
    if( strncmp( line , NAME_EXTERNAL, strlen( NAME_EXTERNAL ) ) == 0 ) {
        node->type = EXTERNAL;;
        result = set_statement_label_name(node, line+ strlen(NAME_EXTERNAL));
        if (result == SUCCESS)
            node->is_label = true;
    }
    else if( strncmp( line, NAME_DATA, strlen( NAME_DATA ) ) == 0 ) {
        node->type = DATA;
        result = set_data(node, line + strlen( NAME_DATA));
        node->number_of_lines = node->data->number_of_elements;
    }
    else if( strncmp( line, NAME_STRING, strlen( NAME_STRING ) ) == 0) {
        node->type = STRING;
        result = set_string(node, line + strlen(NAME_STRING));
        node->number_of_lines = node->string->number_of_elements;

    }
    else if( strncmp( line, NAME_ENTRY, strlen( NAME_ENTRY ) ) == 0 ) {
        node->type = ENTRY;
        result = set_statement_label_name(node, line+ strlen( NAME_ENTRY ) );
        if( result == SUCCESS )
            node->is_label = true;
    }
    else {
        for ( index = 0 ; line[index] != SPACE_SING && line[index] != TAB_SING && line[index] != '\n' ; index++ ) ;
        result = ERROR;
        print_error("not valid statement", node->text_line, NULL);
    }
    return result;
}

RESULT set_into_function(Node * node,  const char * line) {
    RESULT result = SUCCESS;
    node->functions = init_function();
    if( function_syntax_checker( node->functions, line, node->text_line ) ) {
        node->number_of_lines += node->functions->number_of_lines;
        node->type = CODE;
    }
    else
        result = ERROR;
    return result;
}

RESULT set_label_name(Node * node, const char * line) {
    unsigned int index = 0, end_of_label = 0, start_of_label = 0;
    RESULT result = SUCCESS;
    char * tmp_label_name;
    for(index=0; index < strlen(line); index++){
        if (line[index] != SPACE_SING && line[index] != TAB_SING)
            break;
    }
    start_of_label = index;
    end_of_label = get_label_position(line);
    tmp_label_name = (char *) malloc(sizeof (char )*(end_of_label-start_of_label+1));
    memset( tmp_label_name , '\0' , end_of_label-start_of_label+1);
    for (index = 0; index < end_of_label-start_of_label; index++) {
        tmp_label_name[index] = line[index+start_of_label];
    }
    if(!is_valid_label(node->text_line, tmp_label_name)){
        free(tmp_label_name);
        result = ERROR;
    }
    else {
        if(!is_label_exist(tmp_label_name))
            node->label_name = tmp_label_name;
        else {
            print_error("is not a valid label name, label already exist", node->text_line, tmp_label_name);
            free(tmp_label_name);
            result = ERROR;
        }
    }
    return result;
}

bool is_line_with_label(const char * line) {
    unsigned int index = 0;
    while(line[index] != '\n') {
        if (line[index] == LABELS_SING)
            return true;
        index++;
    }
    return false;
}

unsigned int get_label_position( const char * line){
    unsigned int index = 0;
    while (line[index] != LABELS_SING ) {
        index++;
    }
    return index;
}

RESULT set_statement_label_name(Node * node, const char * line) {
    unsigned int index;
    unsigned int i=0,  end_of_label = 0, start_of_label = 0;
    char * tmp_label_name;
    for( index = 0 ; index < strlen(line) ; index++ ){
        if( line[index] != SPACE_SING && line[index] != TAB_SING )
            break;
    }
    if (line[index] == '\n') {
        print_error("Missing label", node->text_line, NULL);
        return ERROR;
    }
    start_of_label = index;
    for( index = strlen(line) - 1 ; index > start_of_label ; index-- ){
        if (line[index] != SPACE_SING && line[index] != TAB_SING && line[index] != '\n')
            break;
    }
    end_of_label = index+1;
    tmp_label_name = (char *) malloc(sizeof(char) * ( end_of_label - start_of_label + 1 ));
    memset( tmp_label_name , '\0' , end_of_label - start_of_label + 1);
    for ( index = 0 ; index < end_of_label - start_of_label ; index++) {
        tmp_label_name[index] = line[index + start_of_label];
    }

    if( !is_valid_label( node->text_line, tmp_label_name)) {
        free(tmp_label_name);
        return ERROR;
    }
    node->label_name = (char *)malloc(sizeof(char)* (end_of_label - start_of_label));
    for(index = start_of_label, i = 0 ; index < end_of_label ; index++ , i++ ) {
        node->label_name[i] = line[index];
    }
    return SUCCESS;
}

bool is_statement(const char * line) {
    int i;
    for( i = 0 ; line[i] != '\n' ; i++ ){
        if( line[i] == DOT_SING )
            return true;
        else if(line[i] != SPACE_SING && line[i] != TAB_SING)
            return false;
    }
    return false;
}

unsigned int get_statement_position(const char *line) {
    unsigned int i;
    for( i = 0 ; line[i] != '\n'; i++ )
        if(line[i] == DOT_SING)
            return i;
    return 0;
}
