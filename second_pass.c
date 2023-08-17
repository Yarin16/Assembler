#include "second_pass.h"


void set_data_code(Node * node, char * file_name);


void free_data_node(Node * node);


void second_pass(InputInformation * input_information) {
    Node *current_node_ptr = input_information->head_nodes;
    char file_ob_name[MAX_LEN_LABEL_NAME];
    FILE *fp;
	
    /* open file: */
    strncpy(file_ob_name, input_information->file_name, strlen(input_information->file_name)-3);
    file_ob_name[strlen(input_information->file_name)-3] = '\0';
    strcat(file_ob_name, END_OF_OB_FILE);

    fp = fopen(file_ob_name, "w");  /* open file in append mode*/
    if (fp == NULL) {
        printf("Error: Unable to open file %s\n", file_ob_name);
        return;
    }
    fprintf(fp,"     %d %d\n",input_information->IC, input_information->DC);
    fclose(fp);



    while (current_node_ptr != NULL) {
        if (current_node_ptr->type == CODE) {
            write_function_to_file(current_node_ptr->functions, file_ob_name, current_node_ptr->decimal_address);
        }
        else if (current_node_ptr->type == DATA) {
            set_data_code(current_node_ptr, file_ob_name);
        }
        else if (current_node_ptr->type == STRING) {
            write_word_to_ob_file(current_node_ptr->string->letter,file_ob_name, current_node_ptr->decimal_address);
        }
        current_node_ptr = current_node_ptr->next;
    }
}

void set_data_code(Node * node, char * file_name) {
    unsigned int address = node->decimal_address;
    Integer * current_integer =node->data->integer;
    while(current_integer != NULL) {
        write_num_to_ob_file(current_integer->num,file_name, address);
        current_integer = current_integer->next;
        address++;
    }
}

void free_all_memory(InputInformation * input_information) {
    Node *current_node_ptr = NULL;
    Node *next_node_ptr = NULL;
    current_node_ptr = input_information->head_nodes;
    next_node_ptr = current_node_ptr->next;
    while (current_node_ptr != NULL) {
        next_node_ptr = current_node_ptr->next;
        if (current_node_ptr->type == CODE)
            free(current_node_ptr->functions);
        else if (current_node_ptr->type == DATA)
            free_data_node(current_node_ptr);
        else if (current_node_ptr->type == STRING){
            free(current_node_ptr->string->letter);
            free(current_node_ptr->string);
        }
        if (current_node_ptr->is_label) {
            free(current_node_ptr->label_name);
        }
        free(current_node_ptr);
        if (next_node_ptr == NULL)
            break;
        current_node_ptr = next_node_ptr;
    }
}

void free_data_node(Node * node){
    Integer * current_integer = NULL;
    Integer * next_integer = NULL;
    current_integer = node->data->integer;
    while (current_integer != NULL) {
        next_integer = current_integer->next;
        free(current_integer);
        current_integer = next_integer;
    }
    free(node->data);
}
