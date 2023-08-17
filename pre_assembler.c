
#include "pre_assembler.h"

/* 	file: pre_assembler.c
 *	function name: delete_white_tabs_frome_line
 *	parameters: file name
 *	return: o if o.k
 *  The function receives a file and copies to another file all the lines that are not comments
 *  finally changes the name of the file it created to the name of the
 *  file it received and deletes the old file
 * */
int delete_white_tabs_frome_line(char * filename) {
    FILE * fp_in;
    FILE * fp_out;
    char line[MAX_LINE_LENGTH];
    int i;
    fp_in = fopen(filename, "r");
    if(fp_in == NULL) {
        fprintf(stdout,"Error - opening input file %s",filename);
        return 1;
    }
    fp_out = fopen("temp.txt", "w");
    if(fp_out == NULL) {
        fprintf(stdout,"Error opening output file");
        fclose(fp_in);
        return 1;
    }
    while(fgets(line, MAX_LINE_LENGTH, fp_in) != NULL) {
        for( i = 0 ; i < strlen(line) ; i++)
            if(line[i] != SPACE_SING && line[i] != TAB_SING)
                break;
        if (line[i] !=  NOTE_SING) {
            fputs(line+i, fp_out);
        }
    }
    fclose(fp_in);
    fclose(fp_out);
    if (remove(filename) != 0) {
        fprintf(stdout,"Error deleting input file %s",filename);
        return 1;
    }
    if (rename("temp.txt", filename) != 0) {
        fprintf(stdout,"Error deleting input file %s",filename);
        return 1;
    }
    return 0;
}

/* 	file: pre_assembler.c
 *	function name: pre_assembler
 *	parameters: InputInformation
 *				file name
 *  The function receives the name of the file and a node it fills in
 *  the name of the file with the .am extension and after cleaning the macros
 *  this is done with the help of the two files
 *  one is free of macros and the other contains only macros and
 *  also with the help of the list of macros
 */
void pre_assembler(InputInformation *inputInformation, char *name_file) {
    LinkedList * macro_list = NULL;
    char * first_word;
    char line[MAX_LINE_LENGTH];
    char copy_line[MAX_LINE_LENGTH];
    char name_of_file[MAX_NAME_MACRO];
    char *output_file_name = NULL;
    FILE * macro_file = NULL;
    FILE * no_macro_file = NULL;
    FILE * output_file = NULL;

    macro_list = crete_macro_list(name_file, inputInformation);
    macro_file = fopen("mf.txt", "r");
    no_macro_file = fopen("nmf.txt", "r");
    strcpy(name_of_file, name_file);
    strcat(name_of_file, END_OF_OUTPUT_FILE);
    output_file = fopen(name_of_file, "w");
    if (output_file == NULL) {
        print_error("Will opening file",0, name_of_file);
        inputInformation->result = ERROR;
        return;
    }
    while (fgets(line, MAX_LINE_LENGTH, no_macro_file)) {
        strcpy(copy_line, line);
        first_word = strtok(copy_line, " \n");
        if (searchNode(macro_list, first_word) != NULL) {
            rewind(macro_file);
            while (fgets(line, sizeof(line), macro_file)) {
                if ((strstr(line, first_word) != NULL) && (strstr(line, START_MACRO) != NULL)) {
                    while (fgets(line, sizeof(line), macro_file)) {
                        if (strstr(line, END_MACRO) != NULL) {
                            break;
                        }
                        fprintf(output_file, "%s", line);
                    }
                    break;
                }
            }
        }
        else
            fprintf(output_file, "%s", line);
    }
    fclose(no_macro_file);
    fclose(macro_file);
    remove("mf.txt");
    remove("nmf.txt");
    fclose(output_file);
    delete_white_tabs_frome_line(name_of_file);
    output_file_name = malloc(strlen(name_of_file) + 1);
    if (output_file_name == NULL) {
        fprintf(stdout, "Error allocating memory for output_file_name\n");
        inputInformation->result = ERROR;
        return;
    }
    strcpy(output_file_name, name_of_file);
    strcpy(inputInformation->file_name , output_file_name);
    destroyLinkedList(macro_list);
}

/* 	file: pre_assembler.c
 *	function name: crete_macro_list
 *	parameters: InputInformation
 *				file name
 *	return: macro linked list
 *  The function goes over the incoming file and produces two files from it
 *  one containing only macros and one free of macros
 *  In addition, the function produces a linked list that includes all the names of the macros
 */
LinkedList * crete_macro_list(char *name_file, InputInformation * inputInformation) {
    LinkedList * macro_list = NULL;
    char * first_word = NULL;
    char * macro_name = NULL;
    char line[MAX_LINE_LENGTH];
    char copy_line[MAX_LINE_LENGTH];
    char name_input_file[MAX_NAME_MACRO];
    FILE *macro_file = NULL, *nomacro_file = NULL, *input_file = NULL;
    macro_list = initLinkedList();
    strcpy(name_input_file, name_file);
    strcat(name_input_file, END_OF_INPUT_FILE);
    input_file = fopen(name_input_file, "r");
    if(input_file == NULL) {
        fprintf(stdout, "Error opening input file %s\n", name_file);
        inputInformation->result = ERROR;
        return NULL;
    }
    macro_file = fopen("mf.txt", "w");
    nomacro_file = fopen("nmf.txt", "w");
    while(fgets(line, MAX_LINE_LENGTH, input_file)) {
        if(strncmp(line, "\n", 1) == 0){
            continue;
        }
        strcpy(copy_line, line);
        first_word = strtok(copy_line, " ");
        if(first_word == NULL)
            continue;
        else if(strcmp(first_word, START_MACRO) == 0) {
            macro_name = strtok(NULL, " \n");
            addNode(macro_list, macro_name);
            fprintf(macro_file, "%s", line);
            while (fgets(line, MAX_LINE_LENGTH, input_file)) {
                strcpy(copy_line, line);
                fprintf(macro_file, "%s", line);
                first_word = strtok(copy_line, " \n");
                if (strcmp(first_word, END_MACRO) == 0)
                    break;
            }
        }
        else
            fprintf(nomacro_file, "%s", line);
    }
    fclose(input_file);
    fclose(nomacro_file);
    fclose(macro_file);
    return macro_list;
}
