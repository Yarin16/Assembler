#include "labels.h"

InputInformation* _inputInformation = NULL;


void set_label_input_information(InputInformation* inputInformation) {
    _inputInformation = inputInformation;
}

bool checking_if_the_label_exists(Functions *function, unsigned int line_number){
    bool label_exists = true;
    if (function->method_source == 3){
        if (is_label_exist(function->source_name) == 0 && it_is_extern(function->source_name) == false && it_is_entry(function->source_name) == false){
            fprintf(stdout,"ERROR - In a line number %d does not recognize the variable %s\n",line_number,function->source_name);
            label_exists = false;
        }
    }
    if (function->method_target == 3){
        if (is_label_exist(function->target_name) == 0 && it_is_extern(function->target_name) == false && it_is_entry(function->target_name) == false){
            fprintf(stdout,"ERROR - In a line number %d does not recognize the variable %s\n",line_number,function->target_name);
            label_exists = false;
        }
    }

    return label_exists;
}

void print_label_list(InputInformation * input_information) {
    Node * current_node_ptr = input_information->head_nodes;
    char decimal_line[4];

    printf("______________________\n\nLabels list:\n");
    while(current_node_ptr != NULL)  {
        if(current_node_ptr->is_label && !(current_node_ptr->type == ENTRY || current_node_ptr->type == EXTERNAL))
        {
            if(current_node_ptr->decimal_address < 1000) {
                decimal_line[0] = '0';
                sprintf(decimal_line +1 , "%d", current_node_ptr->decimal_address);
            }
            else
                sprintf(decimal_line , "%d", current_node_ptr->decimal_address);
            printf("%s | %s\n", decimal_line, current_node_ptr->label_name);
        }
        current_node_ptr = current_node_ptr->next;
    }
}

bool is_label_exist(const char * label_name) {
    Node * current_node_ptr = _inputInformation->head_nodes;
    while(current_node_ptr != NULL) {
        if(current_node_ptr->is_label) {
            if(strncmp(current_node_ptr->label_name,label_name, strlen(label_name)) == 0) {
                if (current_node_ptr->type != EXTERNAL && current_node_ptr->type != ENTRY)
                    return true;
            }
        }
        current_node_ptr = current_node_ptr->next;
    }
    return false;
}

bool it_is_extern(const char * label_name) {
    Node * current_node_ptr = _inputInformation->head_nodes;
    while(current_node_ptr != NULL) {
        if(current_node_ptr->is_label && strncmp(current_node_ptr->label_name,label_name, strlen(label_name)) == 0 && current_node_ptr->type == EXTERNAL)
            return true;
        current_node_ptr = current_node_ptr->next;
    }
    return false;
}

bool it_is_entry(const char * label_name) {
    Node * current_node_ptr = _inputInformation->head_nodes;
    while(current_node_ptr != NULL) {
        if(current_node_ptr->is_label && strncmp(current_node_ptr->label_name,label_name, strlen(label_name)) == 0 && current_node_ptr->type == ENTRY)
            return true;
        current_node_ptr = current_node_ptr->next;
    }
    return false;
}

unsigned int get_label_address(const char * label_name) {
    Node * current_node_ptr = _inputInformation->head_nodes;
    while(current_node_ptr != NULL) {
        if(current_node_ptr->is_label){
            if(strcmp(current_node_ptr->label_name,label_name) == 0){
                if(current_node_ptr->type != EXTERNAL && current_node_ptr->type != ENTRY)
                    return current_node_ptr->decimal_address;
            }
        }
        current_node_ptr = current_node_ptr->next;
    }
    return -1;
}

bool is_valid_label(unsigned int text_line, const char * label_name) {
    const char FUNCTION_NAMES[NUMBER_OF_FUNCTIONS][LEN_OF_FUNCTION_NAME] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne",
    																														"red", "prn", "jsr", "rts"};
    const char FUNCTION_STOP[LEN_OF_STOP_FUNCTION] = "stop";
    int i = 0;
    if (strlen(label_name) > MAX_LABEL_NAME_LENGTH) {
        print_error("Illegal label name, too long", text_line, NULL);
        return false;
    }
    if (strlen(label_name) <= LEN_OF_STOP_FUNCTION) {
        if (strcmp(label_name, FUNCTION_STOP) == 0) {
            print_error("is not a valid label name, it is a function name", text_line, FUNCTION_STOP);
            return false;
        }
        else {
            for (i = 0; i < 16; i++) {
                if (strcmp(FUNCTION_NAMES[i], label_name) == 0) {
                    print_error("is not a valid label name, it is a function name", text_line, FUNCTION_NAMES[i]);
                    return false;
                }
            }
        }
    }
    if (!((label_name[0] >= 'a' && label_name[0]<='z') || (label_name[0] >= 'A' && label_name[0] <= 'Z'))){
        print_error("is Illegal label name, label name start only with letters", text_line, label_name);
        return false;
    }
    for (i=0; i < strlen(label_name);i++){
        if (label_name[i] == SPACE_SING || label_name[i] == TAB_SING) {
            print_error("Illegal space inside label definition", text_line, NULL);
            return false;
        }
    }
    return true;
}
