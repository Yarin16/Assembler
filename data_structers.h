#ifndef C_DATA_STRUCTERS_H
#define C_DATA_STRUCTERS_H

#include "data_structers_structs.h"

InputInformation * init_information();
Node * init_node();
Functions * init_function();
String * init_string();
Data * init_data();
Integer * init_integer();
LinkedList * initLinkedList();
Node_m * initNodeM();


void addNode(LinkedList * list, const char * string);
Node_m* searchNode(LinkedList * list, const char * string);
void deleteNode(LinkedList * list, const char * string);
void destroyLinkedList(LinkedList * list);

#endif /*C_DATA_STRUCTERS_H*/
