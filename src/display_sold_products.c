 /**
 * @file display_sold_products.c
 *
 * @author Sufian Ali Mohammad - sufianalimohammad@cmail.carleton.ca
 *
 * @brief This function allows the seller to display the products that have been sold in
 * his inventory along with an option to view the entire list of products sold or search by
 * product number. The execution of this function will display the Buyer's name, shipping
 * address, phone number, product number, product quantity.
 *
 * @param[in] seller is a pointer to the structure SELLER in seller.h
 * @param[in] sold_products is a pointer that points to the head of
 * SOLD_PRODUCT structure defined in "seller.h" to get the information of products sold
 *
 * @param[in] option is an integer variable defined to choose different options to view
 * sold products
 * @param[in] found checks for the product number
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../include/seller.h"
#include "../include/display_sold_products.h"


int display_sold_products(struct SELLER *seller)
{
    /* getting the list of sold products */
    sold_product_t *sold_products = seller->products_sold;
    if(sold_products == NULL)
    {
        printf("No sold products for this seller\n");
        return 0; /* returns an empty list */
    }

    /* ask user for input */
    int option;
    printf("1. Get details for a particular product. \n2. View all Sold products\nEnter your choice:");
    scanf("%d", &option);

    char heading[1000] = "BUYER_NAME     BUYER_SHIPPING_ADDRESS         PHONE_NUMBER       PRODUCT_NUMBER            PRODUCT_QUANTITY";

    /* if view all
     * iterate over all the sold products for a seller */
    if(option == 2)
    {
        printf("%s", heading);
        printf("\n");
        while(sold_products != NULL)
        {
            printf("\n");
            printf("%-20s %-30s %-20s %-20d %-20d", sold_products->buyer_name, sold_products->buyer_shipping_address, sold_products->phone_number
                   , sold_products->product_number, sold_products->quantity);
            sold_products = sold_products->next_sold_product;
            printf("\n");
        }
    }
    else if(option==1)
    {
        /*if sort by product number */
        int pnum;
        printf("Enter product number:");
        scanf("%i", &pnum);
        int found = 0;
        while(sold_products != NULL)    /* check whether the product entered exists in the sold products list */
        {
            if(sold_products->product_number==pnum)
            {
                printf("%s", heading);
                printf("\n");
                printf("\n");
                printf("%-20s %-30s %-20s %-20d %-20d", sold_products->buyer_name, sold_products->buyer_shipping_address, sold_products->phone_number
                   , sold_products->product_number, sold_products->quantity);
                found = 1;
                break;
            }
            sold_products = sold_products->next_sold_product;
        }
        if(!found)  /* if product entered is not found */
        {
            printf("There is no product with the product number as %d\n", pnum);
            return -1;  /* invalid inputs */
        }
    }
    else
    {
        printf("Please enter valid inputs\n");
        return -1;  /* invalid inputs */
    }
    return 1;   /* success */
}
