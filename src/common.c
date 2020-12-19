/*
 * common.c
 *
 *  Created on: Dec. 17, 2020
 *      Author: safatanzeem
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/common.h"


/**\brief this function empties stdin if EOF is reached
 */
void empty_stdin(void){

    int c = getchar();
    while (c!= '\n' && c != EOF){
        c = getchar();
    }

}

/**\brief This function check if the integer input entered by the user is valid or not
 * param[in] val value returned by scanf when the user enters an input
 * return 2 if end of file is reached
 * return -7 if user entered character instead of integer type
 * return 0 on success
 */

int validate(int val){
    if (val == EOF){
        printf("Input has been cancelled!\n");
        return EOF_REACHED;
    }else if (val == 0){
        printf(
                "Error:invalid integer input! Please enter again..\n");
        empty_stdin();
        return ERROR_INVALID_INPUT;
    }else{
        empty_stdin();
        return OK;
    }
    return OK;
}
