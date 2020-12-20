/*
 * test_stock_update.c
 *
 *  Created on: Dec. 18, 2020
 *      Author: safatanzeem
 */

void main(){

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
    fprintf(output, "---TEST FAILED----Error! product_number can't be equal to zero;"
            "Quantity and Type can't be less than or equal to zero--\n\n");


    /* Checking pre condition 3 */
    prod_num = 10029;
    quantity = -1;
    type = 1;
    update_stock(prod_num, quantity, type);
    fprintf(output,"Function call with quantity of products to be added equal to -1.\n");
    fprintf(output, "---TEST FAILED----Error! product_number can't be equal to zero;"
            "Quantity and Type can't be less than or equal to zero--\n\n");

    /* Checking pre condition 1 */
    prod_num = 0;
    quantity = 15;
    type = -4;
    update_stock(prod_num, quantity, type);
    fprintf(output,"Function call with Type less than equal to 0.\n");
    fprintf(output, "---TEST FAILED----Error! product_number can't be equal to zero;"
            "Quantity and Type can't be less than or equal to zero--\n\n");

    /* Checking pre/post condition*/
    prod_num = 10029;
    quantity = 15;
    type = 1;
    update_stock(prod_num, quantity, type);
    fprintf(output,"Function call with valid input parameter.\n");
    fprintf(output, "---TEST FAILED----Error! product_number can't be equal to zero;"
            "Quantity and Type can't be less than or equal to zero--\n\n");




}
