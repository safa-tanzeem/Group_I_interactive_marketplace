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
#include "seller.h"
#include "inventory_creation.h"
#include "scanner.h"
#include "seller_manager.h"
#include "update_buyer_info.h"


int buyer_info(char buyer_name[20], char address[40], char phone_num[10], int prod_num, int quantity_sold, int seller_id){

    sold_product_t *buyer_info = (sold_product_t*)malloc(sizeof(sold_product_t));

    strcpy(buyer_info->buyer_name,buyer_name);
    strcpy(buyer_info->buyer_shipping_address,address);
    strcpy(buyer_info->phone_number,phone_num);
    //buyer_info->phone_number = phone_num;
    buyer_info->product_number = prod_num;
    buyer_info->quantity = quantity_sold;

    //converting seller id into string
    char temp_str[12];
    sprintf(temp_str, "%d", seller_id);

    //generating file path
    char file_path[100] = SELLER_ROOT_PATH;
    strcat(file_path, temp_str);
    strcat(file_path, ".txt");

    FILE* file;
    file = fopen(file_path,"a+");

    if(file == NULL){
        fprintf(stderr,"\n Error! File can't be opened");
        return 1;
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
