/*
 * test_inventory_creation.c
 *
 *  Created on: Dec. 20, 2020
 *      Author: safatanzeem
 */



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../../include/inventory_creation.h"
#include "../include/test_inventory_creation.h"
#include "../../include/seller_manager.h"

/**
 * \brief main function tests inventory_creation.c function
 * Pre-Conditions:
 * 1. The length of product number entered by user should be unique equal to 5 digits
 * 2. The length of product name entered by user should be less than 20 characters
 * 3. The stock of product entered should not be less than or equal to zero
 * 4. The price of product entered should not be less than or equal to zero
 * 5. the input parameter shoudl not be equal to NULL;
 *
 * Testing @ Pre-Conditions
 * 1. Function call with input parameter equal to NULL
 * 2. Function call, user will have to enter valid/invalid entries to check these parameters
 *
 * Post-Conditions:
 * 1. Buyer's information must be added to the seller_id.txt file
 * Testing @ Post-Conditions
 * 1. Function call with valid list input parameters, Buyers information will be appended
 * at the end of the seller_id.txt file
 */

int main(){

    FILE *output;
    output = fopen(PATH_FILE, "w+");

    /*Checking pre-condition 1*/
    add_new_product(NULL);
    fprintf(output,"Function call with NULL as input parameter.\n");
    fprintf(output, "---TEST FAILED----Invalid Input--\n\n");


    /*Checking pre/post-condition 2*/
    int seller_id = 5560;
    int result = 0;
    char password[20] = "pass5";

    struct SELLER *seller = (struct SELLER*) malloc(sizeof(struct SELLER));

    seller = seller_log_in(seller_id,password);

    printf("------------------INSTRUCTIONS FOR TEST------------------------------");
    printf("For testing purpose seller is logged in with seller id: 5560\n"
            "Please enter seller id: 5560 when asked again. if not product won't be added\n");
    printf("User will have to test the function with the help of following functions following instructions:\n,"
            "- Test will fail more than 5 digits for product number\n"
            "- You will be asked to enter again if product number is not unique, "
            "- Enter Product number > 20000 and 5 digit so that it is unique\n"
            "- Test will fail if more than 20 characters for name of product\n"
            "- Test will fail if stock is equal to zero or negative\n"
            "- Test will fail if price is equal to zero or negative\n"
            "- The seller ID should be entered in the end: 5560\n");

    result = add_new_product(seller);
    if(result == 0){

        fprintf(output,"Input Parameter are valid and correct.\n");
        fprintf(output, "---TEST PASSED---Product has been added in product.txt--\n\n");

    }else if(result == -1){

        fprintf(output,"Input Parameter is valid.\n");
        fprintf(output, "---TEST FAILED---Wrong category has been entered.txt--\n\n");

    }else if(result == -2){

        fprintf(output,"Input Parameter is invalid.\n");
        fprintf(output, "---TEST FAILED---Input is NULL --\n\n");

    }else if(result == -3){

        fprintf(output,"Input Parameter is valid.\n");
        fprintf(output, "---TEST FAILED---Product name is more than 20 characters--\n\n");

    }else if(result == -4){

        fprintf(output,"Input Parameter is valid.\n");
        fprintf(output, "---TEST FAILED---Product number is not 5 digit--\n\n");

    }else if(result == -5){

        fprintf(output,"Input Parameter is valid.\n");
        fprintf(output, "---TEST FAILED---Price is less than or equal to zero--\n\n");

    }else if(result == -6){

        fprintf(output,"Input Parameter is valid.\n");
        fprintf(output, "---TEST FAILED---Stock is less than or equal to zero--\n\n");

    }else{

        fprintf(output,"Input Parameter is valid.\n");
        fprintf(output, "---TEST FAILED---You have been asked to enter again\n"
                "Either Seller id entered again doesn't match or product number is not unique--\n\n");

    }



    return 0;
}
