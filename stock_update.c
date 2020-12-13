/*
 * stock_update.c
 *
 *  Created on: Dec. 4, 2020
 *      Author: safatanzeem
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "seller.h"
#include "stock_update.h"
#include"scanner.h"

int update_file(product_t *head_ref){

    product_t *current = head_ref;

    FILE *product_file;
    product_file = fopen("/Users/safatanzeem/Desktop/Demo/product.txt", "w");

    if (product_file == NULL){
        fprintf(stderr, "\n Error! File can't be opened");
        return 1;
    }
    while (current != NULL){
        fprintf(product_file, "%s,%s,%d,%d,%d,%f,%d,%f,%d\n",
                current->name,
                current->category,
                current->category_num,
                current->product_number,
                current->stock,
                current->price,
                current->discount_code,
                current->discount_percentage,
                current->seller_id);
        current = current->next_product;
    }
    fclose(product_file);
    return 0;
}

int calculate_new_stock(int prev_stock,int quantity, int type){
    int new_stock_val = 0;

    switch (type){

    case 0:
        if (prev_stock >= quantity){
            new_stock_val = (prev_stock - quantity);
        }else{
            printf(
                    "Purchased number of products are greater than products available");
            return -1;
        }
        break;
    case 1:
        new_stock_val = (prev_stock + quantity);
        break;
    default:
        printf("invalid entry of type\n");
        return -2;
    }

    return new_stock_val;
}

/*
 * \brief This function updates stock in the inventory when a purchase is made
 * or if seller wants to add new stock
 * param[in] prod_num Product number of the product whose stock needs to be updated
 * param[in] quantity Quantity of the product that needs to be updated
 * param[in] type "1" if stock is being added, "0" if stock is being subtracted
 */
void update_stock(int prod_num, int quantity, int type){

    int prev_stock = 0; //previous stock
    int flag = 1;

    product_t *head_ref = get_products();
    product_t *current_product = head_ref;
    product_t *previous_product = NULL;

    while (flag != 0){

        if (prod_num == current_product->product_number){
            //stock updation
            //printf("entering equation\n");
            prev_stock = current_product->stock;

            current_product->stock = calculate_new_stock(prev_stock,quantity,type);
            //printf("Product stock has been updated!");

            if (previous_product == NULL){
                //beginning of the list need to change head
                head_ref = current_product;
            }

            flag = 0;

        }else{
            if (current_product->next_product == NULL){
                //end of the list reached
                if (prod_num == current_product->product_number){
                    //Check if product number is at the last
                    current_product->stock = calculate_new_stock(prev_stock,quantity,type);
                    //printf("Product stock has been updated!");
                    flag = 0;
                }else{
                    printf("Product not found, wrong product number entered");
                    return;
                }

            }else{
                //Traverse the linked list
                previous_product = current_product;
                current_product = current_product->next_product;
            }
        }
    }
    //print_list(head_ref);
    update_file(head_ref);
}
