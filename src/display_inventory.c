/**
 * @file display_inventory.c
 *
 * @author Sufian Ali Mohammad - sufianalimohammad@cmail.carleton.ca
 *
 * @brief This function allows the seller to view the inventory that contains the information
 * about the products being sold by the seller. The function reads from "scanner.h" to get the
 * products information and "seller.h" to get the product numbers associated with the seller
 *
 * @param[in] seller is a pointer to the structure SELLER in seller.h
 *
 * @param[in] seller_products_head points to the head of structure PRODUCT_NUM defined in "seller.h" to get
 * the product numbers associated to the products being sold by the seller
 *
 * @param[in] products_head points to the head of the structure defined in "scanner.h" to get
 * the products information
 *
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../include/seller.h"
#include "../include/scanner.h"
#include "../include/display_inventory.h"

int display_inventory(struct SELLER *seller){
    product_t* products_head = get_products();
    /* get the list of product ids of a particular seller */
    seller_prod_num_t *seller_products_head = seller->products_number;
    seller_prod_num_t *current_product = seller_products_head;
    /* if the current_product returns NULL then the seller has no products in his inventory */
    if(current_product == NULL){
        printf("The seller does not have any products in the inventory.\n");
        return 0;
    }
    /* defined a character array to print the following headings for better organization of inventory */
    char heading[1000] = "PRODUCT_CATEGORY     PRODUCT_NAME         PRODUCT_NUMBER       STOCK             PRODUCT_PRICE           DISCOUNT_CODE                 DISCOUNT_PERCENTAGE            STATUS";
    printf("%s", heading);
    printf("\n");
    /* iterate over all the product ids of a seller */
    while(current_product!=NULL){
        printf("\n");
        /* current product id */
        int product_id = current_product->value;
        /* get the head of the global product list */
        product_t* current = products_head;

        /* find the product with the "current product id" in the global product list */
        while(current->product_number != product_id)
            current = current->next_product;
            if(current==NULL){
                break;
            }

        /* display information of the product associated with "current product id" */

        printf("%-20s %-20s %-20d %-20d %-20f %-30d %-30f", current->category, current->name, current->product_number, current->stock, current->price, current->discount_code, current->discount_percentage);
        if(current->stock == 0)
            printf("SOLD OUT");
        else if(current->stock > 0 && current->stock < 10)
            printf("LOW IN STOCK");
        else if(current->stock >= 10)
            printf("IN STOCK");

        printf("\n");
        /* get the next product of the seller */
        current_product = current_product->next;
    }

    return 0;
}
