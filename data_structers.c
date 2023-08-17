#include "data_structers_structs.h"


InputInformation * init_information() {
    InputInformation * input_information = NULL;
    input_information = (InputInformation * )malloc( sizeof( struct InputInformation ) );
    if( input_information == NULL )
        handle_alloc_error();
    input_information->file_name = ( char * )malloc( sizeof( char ) * MAX_FILE_NAME );
    memset(input_information->file_name, '\0', MAX_FILE_NAME);
    if(input_information == NULL)
        handle_alloc_error();
    input_information->DC = 0;
    input_information->IC = 0;
    input_information->result = SUCCESS;
    input_information->head_nodes   = NULL;
    return input_information;
}

Node * init_node(){
    Node * node = NULL;
    node = ( Node * ) malloc( sizeof( struct Node ) );
    if( node == NULL )
        handle_alloc_error();
    node->type = UNKNOWN;
    node->number_of_lines = 0;
    node->decimal_address = 0;
    node->text_line = 0;
    node->is_label = false;
    node->label_name = NULL;
    node->string = NULL;
    node->data = NULL;
    node->functions = NULL;
    node->next = NULL;
    return node;
}

Functions * init_function(){
    Functions * function = NULL;
    function = ( Functions * )malloc( sizeof( struct Functions ) );
    if(function == NULL)
        handle_alloc_error();
    function->number_function = 0;
    function->method_target = 0;
    function->method_source = 0;
    function->number_of_lines = 0;
    return function;
}

String * init_string() {
    String * string = NULL;
    string = ( String * )malloc( sizeof( struct String ) );
    if( string == NULL )
        handle_alloc_error();
    string->number_of_elements = 0;
    string->letter = NULL;
    return string;
}

Data * init_data() {
    Data * data = NULL;
    data = ( Data * )malloc( sizeof( struct Data ) );
    if(data == NULL)
        handle_alloc_error();
    data->number_of_elements = 0;
    data->integer = NULL;
    return data;
}

Integer * init_integer(){
    Integer * integer = NULL;
    integer = ( Integer * )malloc( sizeof( struct Integer ) );
    if( integer == NULL )
        handle_alloc_error();
    integer->num = 0;
    integer->next = NULL;
    return integer;
}

LinkedList * initLinkedList() {
    LinkedList * linkedList = NULL;
    linkedList = ( LinkedList * )malloc( sizeof( struct LinkedList ) );
    if( linkedList == NULL )
        handle_alloc_error();
    linkedList->head = NULL;
    return linkedList;
}

Node_m * initNodeM() {
    Node_m * node_m = NULL;
    node_m = (Node_m * )malloc( sizeof( struct Node_m ) );
    if( node_m == NULL )
        handle_alloc_error();
    node_m->next = NULL;
    memset(node_m->string, '\0', MAX_STRING_LENGTH);
    return node_m;
}

void addNode( LinkedList * list, const char * string ) {
    Node_m * newNode = initNodeM();
    strncpy(newNode->string, string, MAX_STRING_LENGTH);
    newNode->next = list->head;
    list->head = newNode;
}

Node_m * searchNode(LinkedList * list, const char * string) {
    Node_m * current = list->head;
    while(current != NULL) {
        if(strncmp(current->string, string, MAX_STRING_LENGTH) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void deleteNode(LinkedList * list, const char * string) {
    Node_m * current = list->head;
    Node_m * previous = NULL;
    while( current != NULL ) {
        if( strncmp( current->string, string, MAX_STRING_LENGTH ) == 0) {
            if(previous == NULL) {
                list->head = current->next;
            }
            else
                previous->next = current->next;
            free( current );
            return;
        }
        previous = current;
        current = current->next;
    }
}

void destroyLinkedList(LinkedList * list) {
    Node_m * current = list->head;
    while(current != NULL) {
         Node_m * next = current->next;
        free( current );
        current = next;
    }
    list->head = NULL;
}

