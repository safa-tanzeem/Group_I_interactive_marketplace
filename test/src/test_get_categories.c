/*
 * test_get_categories.c
 *
 *  Created on: Dec. 14, 2020
 *      Author: muhammadbsalman
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/scanner.h"
#include "../include/test_get_categories.h"

/**
 * \brief main function tests get_categories function
*Will output category names to test_get_categories.log if successful, otherwise output fail log
*/

void main(){

	int i = 0; //array counter
	char** categories = get_categories();
	
	FILE *output;
   	output = fopen(PATH, "w+");
	
	if (categories != NULL){
		

    	fprintf(output, "---List of Categories---\n");


        for(i; i<7; i++){
            fprintf(output, "%i. %s\n", i+1, categories[i]);
        }

			


    }
    
    else{
    	fprintf(output, "---TEST FAILED---\n");
	}
    
    
    
    fclose(output);


	return;
}
