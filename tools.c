#include "tools.h"

char base64Digits[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


/* 	file: tools.c
 *	function name: string_to_int
 *	parameters: string to convert
 *	return: number from string
 * */
int string_to_int(char * str) {
    long num;
    int i = 0;
    char * endPtr;
    errno = 0;
    if( *( str + i ) == '@' )
    		i++;
    if( *( str + i ) == 'r' )
        		i++;
    num = strtol( str + i, &endPtr , 10 );
    if( errno == ERANGE || num > INT_MAX || num < INT_MIN || * endPtr != '\0') {
        return -1;
    }
    return (int)num;
}

/* 	file: tools.c
 *	function name: decimal_to_binary
 *	parameters: number of digit in the binary array
 *				decimal number
 *				binary array to store the result
 * */
void decimal_to_binary(int digit, int decimal_number, char * binary_array) {
    int i;
    if(decimal_number >= 0) {
        /* Positive number: convert normally*/
        for( i =  (digit - 1) ; i >= 0 ; i-- ) {
            binary_array[i] = decimal_number % 2 ? '1' : '0';
            decimal_number /= 2;
        }
    }
    else {
        /* Negative number: use 2's complement method*/
        int complement = ( ( 1 << ( digit + 1 )  ) + decimal_number ) & 0xFFF;
        for( i = (digit - 1); i >= 0 ; i-- ) {
            binary_array[i] = complement % 2 ? '1' : '0';
            complement /= 2;
        }
    }
}

/* 	file: tools.c
 *	function name: binary_to_base64_6_digit
 *	parameters: string to convert
 *				sting to store the result
 * */
void binary_to_base64_6_digit(const char * binaryString, char* base64String) {
    int index = 0;
    int i;
    int binaryValue = 0;
    for (i = 0 ; i < 6 ; i++) {
        binaryValue = (binaryValue << 1) | (binaryString[i] - '0');
    }
    base64String[index++] = base64Digits[binaryValue];
    base64String[index] = '\0';
}

/* 	file: tools.c
 *	function name: write_extern_to_file
 *	parameters: extern variable name (string)
 *				line number
 *				file name
 *	the function write the variable name into .ext file
 * */
void write_extern_to_file( char ext[30], unsigned int num_of_line, char * file_name) {
    FILE *fp;
    char file_ext_name[MAX_NAME_MACROS];
    strncpy( file_ext_name, file_name, strlen( file_name ) - 3 );
    file_ext_name[strlen( file_name ) - 3 ] = '\0';
    strcat( file_ext_name, END_OF_EXT_FILE );

    fp = fopen( file_ext_name, "a+" );  /* open file in append mode */

    if( fp == NULL) {
        printf( "Error: Unable to open file %s\n", file_name );
        return;
    }
    /* Write extern line data to the file*/
    fprintf(fp, "%d     %s\n", num_of_line, ext);
    fclose(fp);
}

/* 	file: tools.c
 *	function name: write_entry_to_file
 *	parameters: entry variable name (string)
 *				line number
 *				file name
 *	the function write the variable name into .ent file
 * */
void write_entry_to_file(char ent[30],unsigned int num_of_line, char* file_name) {
    FILE *fp;
    char file_ent_name[MAX_NAME_MACROS];
    strncpy(file_ent_name, file_name, strlen(file_name)-3);
    file_ent_name[strlen(file_name)-3] = '\0';
    strcat(file_ent_name, END_OF_ENT_FILE);

    fp = fopen(file_ent_name, "a+");  /* open file in append mode*/

    if (fp == NULL) {
        printf("Error: Unable to open file %s\n", file_name);
        return;
    }
    /* Write extern line data to the file*/
    fprintf(fp, "%d     %s\n", num_of_line, ent);
    fclose(fp);
}

/* 	file: tools.c
 *	function name: write_memory_word_to_ob_file
 *	parameters: binary memory word
 *				line number
 *				file name
 *	the function convert the memory word to base 64 and write it into .ob file
 * */
void write_memory_word_to_ob_file(char * mem, int count, FILE * fp ){
	char base_64[3];
	binary_to_base64_6_digit(mem, base_64);
	binary_to_base64_6_digit(mem + 6, base_64 + 1);
	/* Write the first line data to the file*/
    fprintf(fp, "%d     %s\n",count,base_64);
}

/* 	file: tools.c
 *	function name: write_function_to_file
 *	parameters: function
 *				Address
 *				file name
 *	the function Analyze the data from function and  convert the memory word to base 64 and write it into .ob file
 * */
void write_function_to_file(Functions* func, char* file_name, unsigned int decimal_address) {
	unsigned int count = decimal_address;
	int i;
	FILE * fp;
	int source_name;
	int target_name;
    char mem_word[LEN_OF_MEMORY_WORD] = {0};
    fp = fopen(file_name, "a+");  /* open file in append mode*/
    if (fp == NULL) {
        printf("Error: Unable to open file %s\n", file_name);
        return;
    }
    decimal_to_binary(3,func->method_source, mem_word);
    decimal_to_binary(4,func->number_function, mem_word + 3);
    decimal_to_binary(3,func->method_target, mem_word + 7);
    decimal_to_binary(2, 0, mem_word + 10);
    write_memory_word_to_ob_file(mem_word,count,fp );
    count += 1;
    if (func->number_function >= 0 && func->number_function <= 3) {/* IF */
        if (func->number_of_lines == 3) {
            if (func->method_source == 1) {
            	for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
            		mem_word[i] ='0';
                source_name = string_to_int(func->source_name);
                decimal_to_binary( 10 ,source_name, mem_word);
                write_memory_word_to_ob_file(mem_word,count,fp );
                count += 1;
            }
            if (func->method_source == 3) {
                 if((it_is_extern(func->source_name) == true)){
                	 for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
                		 mem_word[i] ='0';
                	 mem_word[11] = '1';
                	 write_memory_word_to_ob_file(mem_word,count,fp );
                    write_extern_to_file(func->source_name,count,file_name);
                    count += 1;
                 }
                 else if ((it_is_entry(func->source_name) == true)){
                    source_name = get_label_address(func->source_name);
                    for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
                    	mem_word[i] ='0';
                    decimal_to_binary(9,source_name, mem_word);
                    mem_word[10] = '1';
                    write_memory_word_to_ob_file(mem_word,count,fp );
                    write_entry_to_file(func->source_name,source_name,file_name);
                    count += 1;
                }
                 else {
                	 source_name = get_label_address(func->source_name);
                	 for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
                		 mem_word[i] ='0';
                	 decimal_to_binary(10, source_name, mem_word);
                	 mem_word[10] = '1';
                	 write_memory_word_to_ob_file(mem_word,count,fp );
                     count += 1;
                }
            }
            if (func->method_source == 5) {
                source_name = string_to_int(func->source_name);
                for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
                	mem_word[i] ='0';
                decimal_to_binary(5, source_name, mem_word);
                write_memory_word_to_ob_file(mem_word,count,fp );
                count += 1;
            }
            if (func->method_target == 5) {
                target_name = string_to_int(func->target_name);
                for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
                	mem_word[i] ='0';
                decimal_to_binary(5, target_name, mem_word+5);
                write_memory_word_to_ob_file(mem_word,count,fp );
                count += 1;
            }
            if (func->method_target == 3) {
                if(it_is_extern(func->target_name) == true){
                	for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
                		mem_word[i] ='0';
                  	 mem_word[11] = '1';
                  	write_memory_word_to_ob_file(mem_word,count,fp );
                    write_extern_to_file(func->target_name,count,file_name);
                    count += 1;
                } 
                else if(it_is_entry(func->target_name) == true){
                    for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
                    	mem_word[i] ='0';
                    target_name = get_label_address(func->target_name);
                    decimal_to_binary(10,target_name, mem_word);
                    mem_word[10] = '1';
                    write_memory_word_to_ob_file(mem_word,count,fp );
                    write_entry_to_file(func->target_name,target_name,file_name);
                    count += 1;
                } 
                else {
                	for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
                		mem_word[i] ='0';
                    target_name = get_label_address(func->target_name);
                    decimal_to_binary(10, target_name, mem_word);
                     mem_word[10] = '1';
                     write_memory_word_to_ob_file(mem_word,count,fp );
                    count += 1;
                }
            }
            if (func->method_target == 1) {
            	for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
            		mem_word[i] ='0';
                target_name = string_to_int((func->target_name));
                decimal_to_binary( 10 ,target_name, mem_word);
                write_memory_word_to_ob_file(mem_word,count,fp );
                count += 1;
            }
        } 
        else if (func->number_of_lines == 2) {
            source_name = string_to_int((func->source_name));
            target_name = string_to_int((func->target_name));
            for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
            	mem_word[i] ='0';
            decimal_to_binary(5,target_name, mem_word + 5);
            decimal_to_binary(5,source_name, mem_word);
            write_memory_word_to_ob_file(mem_word,count,fp );
            count += 1;
        }

    }
    else if ((func->number_function == 5) || (func->number_function == 4) ||
    		((func->number_function > 6 && func->number_function < 12)||(func->number_function == 13))) {
        if (func->method_target == 3) {
            if(it_is_extern(func->target_name) == true){
            	for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
            		mem_word[i] ='0';
            	mem_word[11] ='1';
            	write_memory_word_to_ob_file(mem_word,count,fp );
                write_extern_to_file(func->target_name,count,file_name);
                count += 1;
            }
            else if (it_is_entry(func->target_name) == true){
                target_name = get_label_address(func->target_name);
            	for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
            		mem_word[i] ='0';
                decimal_to_binary(10,target_name, mem_word);
                mem_word[10] ='1';
                write_memory_word_to_ob_file(mem_word,count,fp );
                write_entry_to_file(func->target_name,target_name,file_name);
                count += 1;
            }
            else {
                target_name = get_label_address(func->target_name);
            	for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
            		mem_word[i] ='0';
            	mem_word[10] ='1';
                decimal_to_binary(10,target_name, mem_word);
                write_memory_word_to_ob_file(mem_word,count,fp );
                count += 1;
            }
        }
        if (func->method_target == 1) {
            target_name = string_to_int(func->target_name);
            for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
            	mem_word[i] ='0';
            decimal_to_binary(10,target_name, mem_word);
            write_memory_word_to_ob_file(mem_word,count,fp );
            count += 1;
        }
    } else if (func->number_function == 6) {
        if (func->method_source == 3) {
            if(it_is_extern(func->source_name) == true){
            	for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
            		mem_word[i] ='0';
            	mem_word[11] ='1';
            	write_memory_word_to_ob_file(mem_word,count,fp );
                write_extern_to_file(func->source_name,count,file_name);
                count += 1;
            }
            else if ((it_is_entry(func->source_name) == true)){
                source_name = get_label_address(func->source_name);
                for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
                	mem_word[i] ='0';
                mem_word[10] ='1';
                decimal_to_binary(10,source_name, mem_word);
                write_memory_word_to_ob_file(mem_word,count,fp );
                write_entry_to_file(func->source_name,source_name,file_name);
                count += 1;
            }
            else {
                source_name = get_label_address(func->source_name);
                for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
                	mem_word[i] ='0';
                mem_word[10] ='1';
                decimal_to_binary(10,source_name, mem_word);
                write_memory_word_to_ob_file(mem_word,count,fp );
                fprintf(fp, "%d     %s\n", count, mem_word);
                count += 1;
            }
        }
        if (func->method_target == 3) {
            if(it_is_extern(func->target_name) == true){
            	for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
            		mem_word[i] ='0';
            	mem_word[11] ='1';
            	write_memory_word_to_ob_file(mem_word,count,fp );
                write_extern_to_file(func->target_name,count,file_name);
                count += 1;
            }
            else if (it_is_entry(func->target_name) == true){
                target_name = get_label_address(func->target_name);
                for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
                	mem_word[i] ='0';
                mem_word[10] ='1';
                decimal_to_binary(10,target_name, mem_word);
                write_memory_word_to_ob_file(mem_word,count,fp );
                write_entry_to_file(func->target_name,target_name,file_name);
                count += 1;
            }
            else {
                target_name = get_label_address(func->target_name);
                for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
                	mem_word[i] ='0';
                mem_word[10] ='1';
                decimal_to_binary(10,target_name, mem_word);
                write_memory_word_to_ob_file(mem_word,count,fp );
                count += 1;
            }
        }
        if (func->method_target == 1) {
            target_name = string_to_int(func->target_name);
            for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
            	mem_word[i] ='0';
            decimal_to_binary(10,target_name, mem_word);
            write_memory_word_to_ob_file(mem_word,count,fp );
            count += 1;
        }
    }
    else if (func->number_function == 12) {
        if (func->method_target == 1) {
            target_name = string_to_int(func->target_name);
            for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
            	mem_word[i] ='0';
            decimal_to_binary(10,target_name, mem_word);
            write_memory_word_to_ob_file(mem_word,count,fp );
            count += 1;
        }
        if (func->method_target == 3) {
            if(it_is_extern(func->target_name) == true){
            	for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
            		mem_word[i] ='0';
            	mem_word[11] ='1';
            	write_memory_word_to_ob_file(mem_word,count,fp );
                write_extern_to_file(func->target_name,count,file_name);
                count += 1;
            }
            else if (it_is_entry(func->target_name) == true){
                target_name = get_label_address(func->target_name);
            	for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
            		mem_word[i] ='0';
            	mem_word[10] ='1';
                decimal_to_binary(10,target_name, mem_word);
                write_memory_word_to_ob_file(mem_word,count,fp );
                write_entry_to_file(func->target_name,target_name,file_name);
                count += 1;
            }
            else {
                target_name = get_label_address(func->target_name);
            	for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
            		mem_word[i] ='0';
            	mem_word[11] ='1';
                decimal_to_binary(10,target_name, mem_word);
                write_memory_word_to_ob_file(mem_word,count,fp );
                count += 1;
            }
        }
        if (func->method_target == 5) {
            int target_name = string_to_int((func->target_name));
        	for( i = 0 ; i < LEN_OF_MEMORY_WORD; i++)
        		mem_word[i] ='0';
            decimal_to_binary(5,target_name, mem_word + 5);
            write_memory_word_to_ob_file(mem_word,count,fp );
            count += 1;
        }
    }
    fclose(fp);
}

/* 	file: tools.c
 *	function name: write_word_to_ob_file
 *	parameters: string
 *				Address
 *				file name
 *	the function write the string into .ob file
 * */
void write_word_to_ob_file(char * string, char* file_name, unsigned int decimal_address){
      int i;
      unsigned int len;
      unsigned int count = decimal_address;
      FILE *fp;
      fp = fopen(file_name, "a+");  /* open file in append mode*/

      if (fp == NULL) {
          printf("Error: Unable to open file %s\n", file_name);
          return;
      }
      len = strlen(string);
      for ( i = 0; i < len; i++) {

          char ascii_in_binary[12]={0};
          int hash;
          hash = (int)string[i];
          decimal_to_binary(12,hash,ascii_in_binary);
          write_memory_word_to_ob_file(ascii_in_binary,count,fp );

          count += 1;
          if(i == len-1){
        	  hash =0;
        	  decimal_to_binary(12,hash,ascii_in_binary);
        	  write_memory_word_to_ob_file(ascii_in_binary,count,fp );
              count += 1;
          }
      }

      fclose(fp);
  }

/* 	file: tools.c
 *	function name: write_num_to_ob_file
 *	parameters: number
 *				Address
 *				file name
 *	the function write the number into .ob file
 * */
void write_num_to_ob_file(int num, char* file_name, unsigned int decimal_address){
      char num_in_binary[12]={0};
      unsigned int count = decimal_address;
      FILE *fp;
      fp = fopen(file_name, "a+");  /* open file in append mode*/

      if (fp == NULL) {
          printf("Error: Unable to open file %s\n", file_name);
          return;
      }

      decimal_to_binary(12,num,num_in_binary);
      write_memory_word_to_ob_file(num_in_binary,count,fp );
      count += 1;
      fclose(fp);
  }
