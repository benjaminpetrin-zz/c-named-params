/*
 * This file illustrates how to use c-easy-params
 * in a c program.
 *
 */

#include "../src/named_params.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Let's declare a function called openfile. It's
 *  purpose is to open a file and return (via 
 *  parameters) the contents of the file.
 *
 *  It has four named parameters.
 *
 *  The filename is optional. If no filename is
 *   given the function will operate on a default
 *   file.
 *
 *  The result can either be stored in a user_buff
 *   that has length of user_buff_ln, or be stored
 *   in buff which is malloced in this function.
 *  
 */
int openfile(NAMED){
	INIT_ARGS(
		/*   type   name      default value            */
		ARG(char*, filename, "/home/me/default_file.txt")
		ARG(char*, user_buff, NULL)
		ARG(int, user_buff_ln, 0)
		ARG(char**, buff, NULL)
	)

	/* Lets inspect the value of our "arguments" */
	printf("The filename is %s\n", filename);
	printf("The user_buff pointer is %d\n", user_buff);
	printf("The user_buff_ln is %d\n", user_buff_ln);
	printf("The buff pointer is %d\n", buff);
	printf("\n");

	/* open the file and fill the appropriate buffer (not shown) */

	return 0;
}

int main(){
	/*
	 * let's call our named-paramater function
 	 * a few times to so that we can observe the 
 	 * result
 	 *
 	 */

	/*Open the default file and provide an allocated buffer*/
	int buffer_ln = 100;
	char buffer[buffer_ln];
	openfile(CALL(
		N(user_buff, buffer),
		N(user_buff_ln, buffer_ln)
	));

	/*Open the provided file and allocate a buffer for us*/
	char *caller_freed = NULL;
	openfile(CALL(
		N(filename, "test.txt"),
		N(buff, &caller_freed)
	));
	if (caller_freed)
		free(caller_freed);

	return 0; /*It's the law you know...*/
}
