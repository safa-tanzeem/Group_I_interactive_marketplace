/*
 * test_get_products.c
 *
 *  Created on: Dec. 14, 2020
 *      Author: muhammadbsalman
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/scanner.h"
#include "../include/test_get_products.h"
#include "../../include/seller.h"


/**
 * \brief main function tests get_products function
*Will output product names to test_get_products.log if successful, otherwise output fail log
*/

void main(){

    struct PRODUCT *list; //declare new node
    list = (struct PRODUCT*) malloc(sizeof(struct PRODUCT));
	list = get_products();
	
	FILE *output;
   	output = fopen(PATH, "w+");
	
	if (list != NULL){
		
    	fprintf(output, "---Product List---\n");
		
		while (list!=NULL){
        	fprintf(output,"%s\n", list->name);
        	list=list->next_product;
    	}

    }
    
    else{
    	fprintf(output, "---TEST FAILED---\n");
	}
    
    fclose(output);


	return;
}
