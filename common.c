/*
 * common.c
 *
 *  Created on: Dec. 17, 2020
 *      Author: safatanzeem
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

void empty_stdin(void){

    int c = getchar();
    while (c!= '\n' && c != EOF){
        c = getchar();
    }

}

int validate(int val){
    if (val == EOF){
        printf("Input has been cancelled!\n");
        return 2;
    }else if (val == 0){
        printf(
                "Error:invalid integer input! Please enter again..\n");
        empty_stdin();
        return -1;
    }else{
        empty_stdin();
        return OK;
    }
    return OK;
}
