
/*
 * test_display_sold_products.c
 *
 *  Created on: Dec. 18, 2020
 *      Author: sufian
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/seller.h"
#include "../../include/display_sold_products.h"
#include "../include/test_display_sold_products.h"

/**
 * @brief main function tests display_sold_products in buyer_functions.c function
*Pre-Conditions:
*1. Buyer must have purchased atleast one product
*2. product number should exist to search for the particular product
*
*Post-Conditions:
*1. Seller has entered the right sold product number
*2. Give an error if seller selects option other than 1 and 2
*3. Seller must be able to view all list of sold products with option 2
*4. seller must be able to view particular product with option 1
*/


/* add element to the sold products list */
void addToSoldProductsList(sold_product_t **list, char buyerName[20], char buyerShipAddress[20], char phoneNum[10], int productNum, int productQuantity)
{
	sold_product_t *newElement = malloc(sizeof(sold_product_t));
	strcpy(newElement->buyer_name, buyerName);
	strcpy(newElement->buyer_shipping_address, buyerShipAddress);
	strcpy(newElement->phone_number, phoneNum);
	newElement->product_number = productNum;
	newElement->quantity = productQuantity;
	newElement->next_sold_product = (*list);
	(*list) = newElement;
	return;
}

/* clears the allocated memory */
void clearMemory(sold_product_t **list)
{
	sold_product_t *curr = (*list), *nextElem;
	if(curr == NULL)
		return;
	while(curr->next_sold_product != NULL)
	{
		nextElem = curr->next_sold_product;
		free(curr);
		curr = nextElem;
	}
	free(curr);
	return;
}

int main()
{

	FILE *output;
    output = fopen(PATH, "w+");
   	seller_t *seller;
   	sold_product_t **sold_products_list = malloc(sizeof(sold_product_t *));

   	/*CASE 1:
	Function is called with the specified seller. The expected output will display the sold products */
	printf("Case-1:\n\n");
	printf("Please select the option number - 2 first to view the sold products to test the next case\n");
	(*sold_products_list) = NULL;
    seller = (seller_t*) malloc(sizeof(seller_t));
	addToSoldProductsList(sold_products_list, "B1", "A1", "11111", 10, 20);
	addToSoldProductsList(sold_products_list, "B2", "A2", "11112", 5, 5);
    seller->products_sold = (*sold_products_list);
    display_sold_products(seller);
	fprintf(output,"Test Case-: 1\nFunction is called with the specified seller\n");
    fprintf(output, "The expected output will display the sold products\n\n");
  	clearMemory(sold_products_list);
	free(seller);

	printf("\n\n");

    /* CASE 2:
	Function is called with the wrong list/ the sold_products_list is empty.
	The expected output will display “The seller does not have any sold products”*/

	printf("Case2:\n\n");
	(*sold_products_list) = NULL;
    seller = (seller_t*) malloc(sizeof(seller_t));
    seller->products_sold = NULL;
    display_sold_products(seller);
	fprintf(output,"Test Case-2:\nFunction is called with the wrong list/ the sold_products_list is empty.\n");
    fprintf(output, "The expected output will display “The seller does not have any sold products\n\n");
  	clearMemory(sold_products_list);
	free(seller);

	printf("\n\n");

	/* CASE 3:
	The function is called successfully, and option 1 is chosen.
	The expected output will display the product information for the product number entered*/
	printf("Case3:\n\n");
	printf("Please select the option-1 and enter the product number as 10\n");
	(*sold_products_list) = NULL;
    seller = (seller_t*) malloc(sizeof(seller_t));
	addToSoldProductsList(sold_products_list, "B1", "A1", "11111", 10, 20);
	addToSoldProductsList(sold_products_list, "B2", "A2", "11112", 5, 5);
    seller->products_sold = (*sold_products_list);
    display_sold_products(seller);
	fprintf(output,"Test Case-3:\nThe function is called successfully, and option 1 is chosen.\n");
    fprintf(output, "The expected output will display the product information for the product number entered”\n\n");
    clearMemory(sold_products_list);
	free(seller);

	printf("\n\n");


	/* CASE 4:
	The function is called successfully, and the option is incorrect. The expected
	output will be “please enter valid inputs” and return to the option menu. */
	printf("Case-4:\n\n");
	printf("Please enter the wrong option number let's say - 3\n");
	(*sold_products_list) = NULL;
    seller = (seller_t*) malloc(sizeof(seller_t));
	addToSoldProductsList(sold_products_list, "B1", "A1", "11111", 10, 20);
	addToSoldProductsList(sold_products_list, "B2", "A2", "11112", 5, 5);
    seller->products_sold = (*sold_products_list);
    display_sold_products(seller);
	fprintf(output," Test Case-4:\nThe function is called successfully, and the option is incorrect. \n");
    fprintf(output, "The expected output will be “please enter valid inputs” and return to the option menu.\n\n");
   	clearMemory(sold_products_list);
	free(seller);

	printf("\n\n");
	/*receipts can be visually observed to see increase in integer appending */

    free(sold_products_list);
    fclose(output);


	return 0;
}
