#include "first_pass.h"
#include "pre_assembler.h"
#include "second_pass.h"


/* 	file: main.c
 *	function name: check_to_continue
 *	parameters: pointer on InputInformation,
 *				A flag that indicates if information should be released
 *	return: A flag that indicates if the program can continue
 * */
bool check_to_continue(InputInformation * input_information, bool free_nodes) {
    if (input_information->result == ERROR) {
        print_error("Stop running on the file", 0, NULL);
        remove(input_information->file_name);
        if(free_nodes)/*IF THE FLAG IS TRUE -> FREE */
            free_all_memory(input_information);
        free(input_information);
        return false;
    }
    return true;
}
/* 	file: main.c
 *	function name: main
 *	parameters:  name of file (from the command line)
 *	return: 0 if success
 * */
int main(int argc, char* argv[]) {
    int i;
    if (argc < 2) {
        printf("\n Usage: %s input_file \n", argv[0]);/*PRINT ERROR */
        exit(1);
    }
    for (i = 1; argv[i] != NULL; i++) {
        InputInformation * input_information = init_information();

        fprintf(stdout,"\nStart working on file: '%s.as'.\n",argv[i]);/*PRINT UPDATE USER INFORMATION */

        pre_assembler(input_information, argv[i]);/*PAST ALL THE MACROS */

        if (check_to_continue(input_information, false)){
            set_label_input_information(input_information);
            set_file_name(input_information->file_name);
            fprintf(stdout,"Start working on file: '%s.am':\n",argv[i]);
            run_first_pass(input_information);
            if (check_to_continue(input_information, true)){
                set_address_and_dc_ic(input_information);
                print_label_list(input_information);
                if (check_to_continue(input_information, true)){
                    second_pass(input_information);
                    fprintf(stdout,"\nFile: '%s.ob' was created successfully\n",argv[i]);
                    free_all_memory(input_information);
                    free(input_information);
                }
            }

        }
    fprintf(stdout,"Finish running the compiler on the file '%s.as'.\n__________________________________________________________________\n",argv[i]);
    }
    return 0;
}

