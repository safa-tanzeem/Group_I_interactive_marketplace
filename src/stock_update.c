/*
 * stock_update.c
 *
 *  Created on: Dec. 4, 2020
 *      Author: safatanzeem
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../include/seller.h"
#include "../include/stock_update.h"
#include "../include/scanner.h"
#include "../include/common.h"


/*\brief This function updates the product inventory when stock is added
 * @param[in] head_ref points to the head of updated inventory linked list
 * @return 0 on success, -3 on error
 **/

int update_file(product_t *head_ref){

    if(head_ref == NULL){
        printf("Error with product file\n");
        return ERROR_NULL_POINTER;
    }

    product_t *current = head_ref;

    FILE *product_file;
    product_file = fopen("..\\data\\product.txt", "w");

    if (product_file == NULL){
        fprintf(stderr, "\n Error! File can't be opened");
        return ERROR_NULL_POINTER;
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

/*\brief This function calculates new stock
 * This function calculates new stock each time a product is bought and
 * everytime seller updates stock of existing product
 * @param[in] prev_stock previous stock in the inventory
 * @param[in] quantity Quantity of the product that needs to be updated
 * @param[in] type "1" if stock is being added, "0" if stock is being subtracted
 * @return[out] new_stock_val New stock value calculated
 * @return -10 if values of input parameters is less than zero
 * @return -11 if purchased stock is greater than stock available
 * @return -12 if any other value of type is called
 * */
int calculate_new_stock(int prev_stock,int quantity, int type){
    int new_stock_val = 0;

    if(prev_stock < 0 || quantity < 0 || type <0){
        printf("Error! prev_stock, quantity and type can't be less than zero");
        return ERROR_VALUE_ZERO;
    }

    switch (type){

    case 0:
        if (prev_stock >= quantity){
            new_stock_val = (prev_stock - quantity);
        }else{
            printf(
                    "Purchased number of products are greater than products available");
            return ERROR_INVALID_COMPARISON;
        }
        break;
    case 1:
        new_stock_val = (prev_stock + quantity);
        break;
    default:
        printf("invalid entry of type\n");
        return ERROR_INVALID_TYPE;
    }

    return new_stock_val;
}

/*
 * \brief This function updates stock in the inventory when a purchase is made
 * or if seller wants to add new stock
 * @param[in] prod_num Product number of the product whose stock needs to be updated
 * @param[in] quantity Quantity of the product that needs to be updated
 * @param[in] type "1" if stock is being added, "0" if stock is being subtracted
 */
int update_stock(int prod_num, int quantity, int type){

    if(prod_num <= 0 || quantity < 0 || type <0){
        printf("Error! product_number, quantity and type can't be less than zero");
        return ERROR_VALUE_ZERO;
    }

    int prev_stock = 0; //previous stock
    int flag = 1;

    product_t *head_ref = get_products();
    product_t *current_product = head_ref;
    product_t *previous_product = NULL;

    while (flag != 0){

        if (prod_num == current_product->product_number){
            /*stock updation*/
            prev_stock = current_product->stock;

            current_product->stock = calculate_new_stock(prev_stock,quantity,type);

            if (previous_product == NULL){
                /*beginning of the list need to change head*/
                head_ref = current_product;
            }

            flag = 0;

        }else{
            if (current_product->next_product == NULL){
                /*end of the list reached*/
                if (prod_num == current_product->product_number){
                    /*Check if product number is at the last*/
                    current_product->stock = calculate_new_stock(prev_stock,quantity,type);
                    flag = 0;
                }else{
                    printf("Product not found, wrong product number entered");
                    return OK;
                }

            }else{
                /*Traverse the linked list*/
                previous_product = current_product;
                current_product = current_product->next_product;
            }
        }
    }
    update_file(head_ref);
    return OK;
}
