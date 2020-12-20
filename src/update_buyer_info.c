/*
 * update_buyer_info.c
 *
 *  Created on: Dec. 5, 2020
 *      Author: safatanzeem
 */


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include "../include/seller.h"
#include "../include/inventory_creation.h"
#include "../include/scanner.h"
#include "../include/seller_manager.h"
#include "../include/update_buyer_info.h"
#include "../include/common.h"


/*\brief This function updates buyer information for seller after each successful transaction
 * @param[in] buyer_name Name of the buyer who bought the product
 * @param[in] address Address of the buyer
 * @param[in] phone_num Phone number of buyer
 * @param[in] prod_num Product number of the product that buyer bought
 * @param[in] quantity_sold number of items of that product sold
 * @param[in] seller_id Seller id of the seller who added this product
 * @return 0 on success
 * @return -3 is file is unable to open
 * @return -2 if name of buyer is more than 20 characters
 * @return -9 if phone number of buyer is more than 10 characters
 * @return -8 if address of buyer is more than 40 characters
 * @return -10 if the value is equal to zero
 *
 **/

int buyer_info(char buyer_name[NAME_MAX_LENGTH], char address[ADDRESS_MAX_LENGTH], char phone_num[PHONE_NUM_MAX_LENGTH], int prod_num, int quantity_sold, int seller_id){

    /* Checking conditions*/
    if (strlen(buyer_name) > NAME_MAX_LENGTH){
        printf(" Invalid input! Please enter less than 20 characters\n");
        return ERROR_WRONG_NAME;
    }

    if (strlen(phone_num) > PHONE_NUM_MAX_LENGTH){
        printf(" Invalid input! phone number can't be more than 10 digits\n");
        return ERROR_INVALID_PHONE_NUMBER;
    }

    if (strlen(address) > ADDRESS_MAX_LENGTH){
        printf(" Invalid input! address can't be more than 40 digits\n");
        return ERROR_INVALID_ADDRESS;
    }

    if(prod_num == 0){
        printf("Invalid product number, Product number can't be 0\n");
        return ERROR_VALUE_ZERO;
    }

    if(quantity_sold == 0){
        printf("Invalid quantity number, quantity can't be 0\n");
        return ERROR_VALUE_ZERO;
    }

    if(seller_id == 0){
        printf("Invalid seller_id, seller id can't be 0\n");
        return ERROR_VALUE_ZERO;
    }

    sold_product_t *buyer_info = (sold_product_t*)malloc(sizeof(sold_product_t));

    strcpy(buyer_info->buyer_name,buyer_name);
    strcpy(buyer_info->buyer_shipping_address,address);
    strcpy(buyer_info->phone_number,phone_num);
    buyer_info->product_number = prod_num;
    buyer_info->quantity = quantity_sold;

    /*converting seller id into string*/
    char temp_str[12];
    sprintf(temp_str, "%d", seller_id);

    /*generating file path*/
    char file_path[100] = SELLER_ROOT_PATH;
    strcat(file_path, temp_str);
    strcat(file_path, ".txt");

    FILE* file;
    file = fopen(file_path,"a+");

    if(file == NULL){
        fprintf(stderr,"\n Error! File can't be opened");
        return ERROR_NULL_POINTER;
    }

    fprintf(file, "%d,%d,%s,%s,%s\n",
            buyer_info->product_number,
            buyer_info->quantity,
            buyer_info->buyer_name,
            buyer_info->buyer_shipping_address,
            buyer_info->phone_number);
    fclose(file);


    return 0;
}
