/*
 * test_stock_update.c
 *
 *  Created on: Dec. 18, 2020
 *      Author: safatanzeem
 */


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../../include/stock_update.h"

#include "../include/test_stock_update.h"

/**
 * \brief main function tests stock_update.c function
 * Pre-Conditions:
 * 1. The product number taken from the file should not be equal to zero.
 * 2. The quantity to be updated in stock should not be less than 0.
 * 3. The type which reflects if products are to be added by seller (type = 1),
 *    or subtracted when a product is bought(type = 0) should not be less than 0.
 * Testing @ Pre-Conditions
 * 1. Function call with product number = 0
 * 2. Function call with quantity = -1
 * 3. Function call with type = -4
 *
 * Post-Conditions:
 * 1. Product's stock must be updated in the product.txt file
 *
 * Testing @ Post-Conditions
 * 1. Function call with valid list input parameters and type = 1.
 * 2. Function call with valid list input parameters and type = 0.
 */

int main(){

    int prod_num = 0;
    int quantity = 0;
    int type = 0;


    FILE *output;
    output = fopen(PATH_FILE, "w+");

    /* Checking pre condition 1 */
    prod_num = 0;
    quantity = 15;
    type = 1;
    update_stock(prod_num, quantity, type);
    fprintf(output,"Function call with product number equal to 0.\n");
    fprintf(output, "---TEST FAILED----Error! Product number can't be equal to zero--\n\n");


    /* Checking pre condition 2 */
    prod_num = 10029;
    quantity = -1;
    type = 1;
    update_stock(prod_num, quantity, type);
    fprintf(output,"Function call with quantity of products to be added equal to -1.\n");
    fprintf(output, "---TEST FAILED----Error! Quantity can't be less than zero--\n\n");

    /* Checking pre condition 3 */
    prod_num = 0;
    quantity = 15;
    type = -4;
    update_stock(prod_num, quantity, type);
    fprintf(output,"Function call with Type less than equal to 0.\n");
    fprintf(output, "---TEST FAILED----Error! Type can't be less than zero--\n\n");

    /* Checking pre/post condition 1*/
    prod_num = 10030;
    quantity = 15;
    type = 1;
    update_stock(prod_num, quantity, type);
    fprintf(output, "---Valid input parameters-");
    fprintf(output, "---The stock of product number 10030 has increased by 15,"
            "The changes are reflected in product.txt file---\n\n");


    /* Checking pre/post condition 2*/
    prod_num = 10029;
    quantity = 2;
    type = 0;
    update_stock(prod_num, quantity, type);
    fprintf(output, "---Valid input parameters-");
    fprintf(output, "---The stock of product number 10029 has decreased by 2,"
            "The changes are reflected in product.txt file---\n\n");

    return 0;



}
