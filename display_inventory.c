/*
 * display_inventory.c
 *
 *  Created on: Dec. 6, 2020
 *      Author: sufian
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "seller.h"
#include "scanner.h"
#include "display_inventory.h"

int display_inventory(seller_t *seller)
{
    product_t* products_head = get_products();
    seller_prod_num_t *seller_products_head = seller->products_number;  // get the list of product ids of a particular seller
    seller_prod_num_t *current_product = seller_products_head;
    if(current_product == NULL)
    {
        printf("No products for this seller");
        return 0;
    }
    char heading[1000] = "PRODUCT_CATEGORY     PRODUCT_NAME         PRODUCT_NUMBER       STOCK             PRODUCT_PRICE           DISCOUNT_CODE                 DISCOUNT_PERCENTAGE            STATUS";
    printf("%s", heading);
    printf("\n");
    // iterate over all the product ids of a seller
    while(current_product!=NULL)
    {
        printf("\n");
        int product_id = current_product->value;   // current product id
        product_t* current = products_head;    // get the head of the global product list

        // find the product with the "current product id" in the global product list
        while(current->product_number != product_id)
            current = current->next_product;
            if(current==NULL){
                break;
            }

        // display info of the product associated with "current product id"

        printf("%-20s %-20s %-20d %-20d %-20f %-30d %-30f", current->category, current->name, current->product_number, current->stock, current->price, current->discount_code, current->discount_percentage);
        if(current->stock == 0)
            printf("SOLD OUT");
        else if(current->stock > 0 && current->stock < 10)
            printf("LOW IN STOCK");
        else if(current->stock >= 10)
            printf("IN STOCK");

        printf("\n");
        // get the next product of the seller
        current_product = current_product->next;
    }

    return 0;
}
