/*
 * test_checkout.c
 *
 *  Created on: Dec. 14, 2020
 *      Author: muhammadbsalman
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/scanner.h"
#include "../../include/buyer_functions.h"
#include "../include/test_checkout.h"
#include "../../include/seller.h"
#include "../../include/common.h"


/**
 * \brief main function tests checkout in buyer_functions.c function
*Pre-Conditions: 
*1. Buyer must have selected a list of products (at least one) in earlier functions to be passed to  this function (linked list exists)
*2. The buyer’s funds (float balance) must be greater than $0. 
*Testing @ Pre-Conditions 
*1. Function call with valid list of products
*2. Function call with an empty list, meaning no selected products. 
*3. Function call with valid list of products, and a fund value equal to $0. 
*
*Post-Conditions: 
*1. Buyer must have sufficient funds
*2. Receipt Outputted 
*Testing @ Post-Conditions 
*1. Function call with valid list of products, and a fund value of  greater than $0. 
*2. Function call with valid list of products, and a fund value less than required. 
*3. Integer appended to every new receipt. 

*/

void main(){

    char temp;
    //generate random list of products
    struct PRODUCT *list; //declare new node
    list = (struct PRODUCT*) malloc(sizeof(struct PRODUCT));
	list = get_products(); //load a valid list of products
	struct PRODUCT *list_t; //declare new node
    list_t = (struct PRODUCT*) malloc(sizeof(struct PRODUCT));
	list_t = list;
	
	while(list_t!=NULL){
		list_t->number_selected=1;
		list_t=list_t->next_product;
	}
	
	struct PRODUCT *empty_list; //declare new node
    empty_list = (struct PRODUCT*) malloc(sizeof(struct PRODUCT));
	empty_list = NULL; //load a valid list of products
	
	float fund = 1000000;
	float zero_fund = 0;
	FILE *output;
   	output = fopen(PATH, "w+");
	
	//Pre/Post Test 1.
	checkout(&list, fund);
	fprintf(output,"Function call with valid list of products, and a fund value of  greater than $0.\n");
    fprintf(output, "---Valid Buyer Product List-");
    fprintf(output, "---Receipt Outputted---\n\n");
		

    
    //Pre Test 2.
    scanf("%c", &temp);
    checkout(&empty_list, fund);
    fprintf(output,"Function call with an empty list, meaning no selected products and valid funds.\n");
    fprintf(output, "---TEST FAILED---NO PRODUCTS SELECTED\n\n");

	
	//Pre Test 3.
	scanf("%c", &temp);
	checkout(&list, zero_fund);
	fprintf(output,"Function call with valid list of products, and a fund value equal to $0.\n");
	fprintf(output, "---TEST FAILED---PRODUCTS SELECTED--EMPTY FUNDS--FAIL RECEIPT OUTPUTTED\n\n");

	
		
	//Post Test 2.
	checkout(&list, 1.00);
	fprintf(output,"Function call with valid list of products, and a fund value less than required. \n");
	fprintf(output, "---TEST FAILED---PRODUCTS SELECTED--INSUFFICIENT FUNDS--FAIL RECEIPT OUTPUTTED\n");

	
	
	//receipts can be visually observed to see increase in integer appending
    
    fclose(output);


	return;
}
