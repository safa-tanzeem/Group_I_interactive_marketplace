
/*
 * test_display_inventory.c
 *
 *  Created on: Dec. 18, 2020
 *      Author: sufian
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/seller.h"
#include "../../include/display_inventory.h"
#include "../include/test_display_inventory.h"

/*
PRECONDITIONS:
- Ensure that the List from which the data is read from, contains the inventory information.

POSTCONDITIONS:
- Display the inventory information when function is called.
- Display the items that are in stock, out of stock, low in stock.
*/


int main()
{

	FILE *output;
   	output = fopen(PATH, "w+");
   	seller_t *seller;
   	seller_prod_num_t *products_num_list;

   	/* CASE 1:
	Function is called with the specified list.
	The expected output will display the inventory information. */
	printf("Case-1: Function is called with the specified list. The expected output will display inventory information.\n\n");

    seller = (seller_t*) malloc(sizeof(seller_t));
    seller->seller_id = 123456;
	products_num_list = malloc(sizeof(seller_prod_num_t));
    products_num_list->value = 10001;
    products_num_list->next = NULL;
    seller->products_number = products_num_list;
    display_inventory(seller);
	fprintf(output,"Test Case-1:\nFunction is called with the specified seller.\n");
    fprintf(output, "The expected output will display the inventory information.\n\n");
    free(products_num_list);
	free(seller);

	printf("\n\n");

    /* CASE 2:
	Function is called with the wrong list/ the list is empty.
	The expected output will display “The seller does not have any products” */
	printf("Case-2: Function is called with the wrong list/ the list is empty.\n\n");
	seller = (seller_t*) malloc(sizeof(seller_t));
    seller->seller_id = 12340;
	seller->products_number = NULL;	// empty list
	display_inventory(seller);
	fprintf(output,"Test Case-2:\nFunction is called with the wrong list/ the list is empty.\n");
    fprintf(output, "The expected output will display “The seller does not have any products”\n\n");
	free(seller);

	printf("\n\n");

	/* CASE 3:
	The function is called successfully, and the quantity of an item is less that 10 but not zero.
	The expected output will be “The item is almost sold out”. */
	printf("Case-3: The function is called successfully, and the quantity of an item is less that 10 but not zero.\n\n");
	seller = (seller_t*) malloc(sizeof(seller_t));
	seller->seller_id = 123456;
	products_num_list = malloc(sizeof(seller_prod_num_t));
    products_num_list->value = 10001;
    products_num_list->next = NULL;
    seller->products_number = products_num_list;
    display_inventory(seller);
	fprintf(output,"Test Case-3:\nThe function is called successfully, and the quantity of an item is less that 10 but not zero.\n");
    fprintf(output, "The expected output will be “The item is almost sold out”\n\n");
    free(products_num_list);
	free(seller);

	printf("\n\n");

	/* CASE 4:
	The function is called successfully, and the quantity of an item is 0.
	The expected output will be “The item is out of stock” */
	printf("Case-4: The function is called successfully, and the quantity of an item is 0.\n\n");
	seller = (seller_t*) malloc(sizeof(seller_t));
	seller->seller_id = 5050;
	products_num_list = malloc(sizeof(seller_prod_num_t));
    products_num_list->value = 111;
    products_num_list->next = NULL;
    seller->products_number = products_num_list;
    display_inventory(seller);
	fprintf(output,"Test Case-4:\nThe function is called successfully, and the quantity of an item is 0.\n");
    fprintf(output, "The expected output will be “The item is out of stock\n\n");
    free(products_num_list);
	free(seller);

	printf("\n\n");

	/* CASE 5:
	The function is called successfully, and the quantity of an item is greater than 10.
	The expected output will be “The item is in stock */
	printf("Case-5: The function is called successfully, and the quantity of an item is greater than 10.\n\n");
	seller = (seller_t*) malloc(sizeof(seller_t));
	seller->seller_id = 3456;
	products_num_list = malloc(sizeof(seller_prod_num_t));
    products_num_list->value = 1234;
    products_num_list->next = NULL;
    seller->products_number = products_num_list;
    display_inventory(seller);
	fprintf(output,"Test Case-5:\nThe function is called successfully, and the quantity of an item is greater than 10.\n");
    fprintf(output, "The expected output will be showing the status of item as 'IN STOCK' \n\n");
    free(products_num_list);
	free(seller);

	printf("\n\n");
	//receipts can be visually observed to see increase in integer appending

    fclose(output);
printf("--------------------All tests have been completed successfully and Log file is generated------------------");

	return 0;
}
