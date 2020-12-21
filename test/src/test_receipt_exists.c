/*
 * test_receipt_exists.c
 *
 *  Created on: Dec. 14, 2020
 *      Author: muhammadbsalman
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/buyer_functions.h"
#include "../include/test_receipt_exists.h"


/**
 * \brief main function tests checkout in buyer_functions.c function
*Pre-Conditions: 
*1. Receipt name was be valid
*Testing @ Pre-Conditions 
*1. Receipt is NULL
*2. Receipt is valid 
*
*Post-Conditions: 
*1. Filename exists or not
*Testing @ Post-Conditions 
*1. Return 0 if not existing
*2. Returning 1 if exists 
*/

void main(){

	FILE *output;
   	output = fopen(PATH, "w+");

    int return_val;
    char* receipt_name;
    receipt_name='\0';
    //Pre Test 1
	return_val = receipt_exists(receipt_name);
	if (return_val ==-1){
		fprintf(output,"---NULL FILENAME---\n\n");
	}
	
	//Pre Test 2
	char receipt_name_new[20];
	strcpy(receipt_name_new,"..//data//receipt");
	return_val = receipt_exists(receipt_name_new);
	if (return_val !=-1){
		fprintf(output,"---VALID FILENAME---\n\n");
	}
    
    //Post Test 1
	strcpy(receipt_name_new,"..//data//receipt45");
	return_val = receipt_exists(receipt_name_new);
	if (return_val ==0){
		fprintf(output,"---VALID FILENAME---HAS NOT EXISTED BEFORE\n\n");
	}
    
    //Post Test 2
	strcpy(receipt_name_new,"..//data//receipt");
	return_val = receipt_exists(receipt_name_new);
	if (return_val ==1){
		fprintf(output,"---FILENAME EXISTS---");
	}
	
    fclose(output);


	return;
}
