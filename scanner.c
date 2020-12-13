/*
 * scanner.c
 *
 *  Created on: Dec. 4, 2020
 *      Author: muhammadbsalman
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "seller.h"
#include "scanner.h"
/**
 * \brief This function returns a double array of category names
 * @return categories double array with category names
 */
char **get_categories(){
    int i;
    char **categories = (char **)malloc(7 * sizeof(char*));
    for(i =0 ; i < 7; i++){
        categories[i] = (char *)malloc(20 * sizeof(char));
    }

    categories[0] = "Home and Garden";
    categories[1] = "Grocery";
    categories[2] = "Health and Beauty";
    categories[3] = "Clothing and Shoes";
    categories[4] = "Sports and Outdoor";
    categories[5] = "Automotive";
    categories[6] = "Electronics";

    return categories;
}

/**
 * \brief This function sorts the linked list according to descending price
 * @param[in] list_products The list of products read in from the text file
 */

void sort_products_descend(struct PRODUCT *list_products){
	
	struct PRODUCT *temp; //declare new node
    temp = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
	temp = (list_products);
	
	struct PRODUCT *tracker; //declare new node
    tracker = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
    
    struct PRODUCT *new_list; //declare new node
    new_list = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
    
    
    float temp_price;
	
	//sort original linked list
	while(temp->next_product!=NULL){
		
		tracker = temp->next_product;
		new_list = temp;
		
		while(tracker!=NULL){
			if((new_list->price)<(tracker->price)){
				new_list = tracker;
			}
			tracker=tracker->next_product;
		}
		
        temp_price = temp->price;
        temp->price = new_list->price;
        new_list->price = temp_price;
        
        temp = temp->next_product;
	}
}

/**
 * \brief This function sorts the linked list according to ascending price
 * @param[in] list_products The list of products read in from the text file
 */
void sort_products_ascend(struct PRODUCT *list_products){
	
	struct PRODUCT *temp; //declare new node
    temp = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
	temp = (list_products);
	
	struct PRODUCT *tracker; //declare new node
    tracker = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
    
    struct PRODUCT *new_list; //declare new node
    new_list = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
    
    
    float temp_price;
	
	//sort original linked list
	while(temp->next_product!=NULL){
		
		tracker = temp->next_product;
		new_list = temp;
		
		while(tracker!=NULL){
			if((new_list->price)>(tracker->price)){
				new_list = tracker;
			}
			tracker=tracker->next_product;
		}
		
        temp_price = temp->price;
        temp->price = new_list->price;
        new_list->price = temp_price;
        
        temp = temp->next_product;
	}
}
/**
 * \brief This function returns a list of products read in from a text file, storing product parameters
 * @return head Head of list containing products
 */
struct PRODUCT* get_products(){

    FILE *input;
    input = fopen("/Users/safatanzeem/Desktop/Demo/product.txt", "r");

    char line[1024];
    char *data;

    struct PRODUCT *head; //declare new node
    head = (struct PRODUCT*) malloc(sizeof(struct PRODUCT));

    struct PRODUCT *product_list_head; //declare new node
    product_list_head = (struct PRODUCT*) malloc(sizeof(struct PRODUCT));

    head = product_list_head;

    if (input == NULL){
        printf("Error occured, could not find file!");
        head = NULL;
        return head;
    }

    while (fgets(line, 1024, input)){

        struct PRODUCT *new_product; //declare new node
        new_product = (struct PRODUCT*) malloc(sizeof(struct PRODUCT));

        data = strtok(line, ",");
        strcpy(new_product->name, data);

        data = strtok(NULL, ",");
        strcpy(new_product->category, data);

        data = strtok(NULL, ",");
        new_product->category_num = atoi(data);

        data = strtok(NULL, ",");
        new_product->product_number = atoi(data);

        data = strtok(NULL, ",");
        new_product->stock = atoi(data);

        data = strtok(NULL, ",");
        new_product->price = atof(data);

        data = strtok(NULL, ",");
        new_product->discount_code = atoi(data);

        data = strtok(NULL, ",");
        new_product->discount_percentage = atof(data);

        data = strtok(NULL, ",");
        new_product->seller_id = atoi(data);

        product_list_head->next_product = new_product;
        product_list_head = new_product;

    }
    product_list_head->next_product = NULL;
    head = head->next_product;

    fclose(input);
    return head;

}

void print_list(product_t *n){
    while (n != NULL){
        printf("%d ", n->product_number);
        printf("%d \n", n->stock);
        n = n->next_product;
    }
}
