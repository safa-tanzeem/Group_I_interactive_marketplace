/*
 * scanner.c
 *
 *  Created on: Dec. 4, 2020
 *      Author: muhammadbsalman
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../include/seller.h"
#include "../include/scanner.h"
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
 * \brief This function returns a list of products read in from a text file, storing product parameters
 * @return head Head of list containing products
 */
struct PRODUCT* get_products(){

    FILE *input;
    input = fopen("..//data//product.txt", "r");

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
