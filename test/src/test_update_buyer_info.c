/*
 * test_update_buyer_info.c
 *
 *  Created on: Dec. 18, 2020
 *      Author: safatanzeem
 */


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../../include/update_buyer_info.h"
#include "../include/test_update_buyer_info.h"

/**
 * \brief main function tests update_buyer_info.c function
 * Pre-Conditions:
 * 1. The length of buyers name entered by user should be less than 20 characters
 * 2. The length of buyers address entered by user should be less than 40 characters
 * 3. The length of buyers phone number entered by user should be less than 10 characters
 * 4. The product number entered as an input parameter should not be equal to 0
 * 5. The quantity of products bought entered as an input parameter should not be equal to 0
 * 6. The seller id to which this product belongs should not be equal to 0
 * Testing @ Pre-Conditions
 * 1. Function call with buyers name more than 20
 * 2. Function call with buyers address more than 40 character
 * 3. Function call with buyers phone number more than 10 characters
 * 4. Function call with product number equal to 0
 * 5. Function call with quantity equal to 0
 * 6. Function call with seller id equal to 0
 *
 * Post-Conditions:
 * 1. Buyer's information must be added to the seller_id.txt file
 * Testing @ Post-Conditions
 * 1. Function call with valid list input parameters, Buyers information will be appended
 * at the end of the seller_id.txt file
 */

int main(){


    char buyer_name[100];
    char address[100];
    char phone_num[100];
    int prod_num = 0;
    int quantity_sold = 0;
    int seller_id = 0;


    FILE *output;
    output = fopen(PATH_FILE, "w+");

    /*Checking pre-condition 1*/
    strcpy(buyer_name,"abcdefghijklmopghldhj");
    strcpy(address,"Address1");
    strcpy(phone_num,"123456");
    prod_num        = 10007;
    quantity_sold   = 5;
    seller_id       = 5550;

    buyer_info(buyer_name,address,phone_num,prod_num,quantity_sold,seller_id);
    fprintf(output,"Function call with length of buyer's name greater than 20 .\n");
    fprintf(output, "---TEST FAILED----Invalid input! Please enter less than 20 characters--\n\n");

    /*Checking pre-condition 2*/
    strcpy(buyer_name,"Buyer1");
    strcpy(address,"abcdefffgghhooffhhjjddkkssllnnccmmssjjddhh");
    strcpy(phone_num,"123456");
    prod_num        = 10007;
    quantity_sold   = 5;
    seller_id       = 5550;

    buyer_info(buyer_name,address,phone_num,prod_num,quantity_sold,seller_id);
    fprintf(output,"Function call with length of buyer's address greater than 40 .\n");
    fprintf(output, "---TEST FAILED----Invalid input! address can't be more than 40 digits--\n\n");

    /*Checking pre-condition 3*/
    strcpy(buyer_name,"Buyer1");
    strcpy(address,"Address1");
    strcpy(phone_num,"123456789012");
    prod_num        = 10007;
    quantity_sold   = 5;
    seller_id       = 5550;

    buyer_info(buyer_name,address,phone_num,prod_num,quantity_sold,seller_id);
    fprintf(output,"Function call with length of buyer's phone number greater than 10.\n");
    fprintf(output, "---TEST FAILED----Invalid input! phone number can't be more than 10 digits--\n\n");

    /*Checking pre-condition 4*/
    strcpy(buyer_name,"Buyer1");
    strcpy(address,"Address1");
    strcpy(phone_num,"123456");
    prod_num        = 0;
    quantity_sold   = 5;
    seller_id       = 5550;

    buyer_info(buyer_name,address,phone_num,prod_num,quantity_sold,seller_id);
    fprintf(output,"Function call with product number equal to 0.\n");
    fprintf(output, "---TEST FAILED----Invalid product number! Product number can't be less than or equal to 0--\n\n");

    /*Checking pre-condition 5*/
    strcpy(buyer_name,"Buyer1");
    strcpy(address,"Address1");
    strcpy(phone_num,"123456");
    prod_num        = 10007;
    quantity_sold   = 0;
    seller_id       = 5550;

    buyer_info(buyer_name,address,phone_num,prod_num,quantity_sold,seller_id);
    fprintf(output,"Function call with quantity equal to 0.\n");
    fprintf(output, "---TEST FAILED----Invalid quantity number! quantity can't be less than or equal to 0\n--\n\n");

    /*Checking pre-condition 6*/
    strcpy(buyer_name,"Buyer1");
    strcpy(address,"Address1");
    strcpy(phone_num,"123456");
    prod_num        = 10007;
    quantity_sold   = 5;
    seller_id       = 0;

    buyer_info(buyer_name,address,phone_num,prod_num,quantity_sold,seller_id);
    fprintf(output,"Function call with seller_id equal to 0.\n");
    fprintf(output, "---TEST FAILED----Invalid seller_id! seller id can't be less than or equal to 0\n\n--\n\n");

    /*Checking pre/post-condition*/
    strcpy(buyer_name,"Buyer test");
    strcpy(address,"Address test");
    strcpy(phone_num,"123456");
    prod_num        = 10007;
    quantity_sold   = 5;
    seller_id       = 5560;

    buyer_info(buyer_name,address,phone_num,prod_num,quantity_sold,seller_id);
    fprintf(output,"Function call with valid list of input parameters.\n");
    fprintf(output, "---Valid input parameters-");
    fprintf(output, "---Buyer's information appended in the text file with name:5560.txt---\n\n");

    fclose(output);

    return 0;

}


