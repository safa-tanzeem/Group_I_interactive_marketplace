/*
 * main.c
 *
 *  Created on: Nov. 29, 2020
 *      Author: safatanzeem
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "seller.h"
#include "inventory_creation.h"
#include "scanner.h"
#include "common.h"
#include "seller_manager.h"


enum category_choice_e {
    CATEGORY_HOME_GARDEN = 1,
    CATEGORY_GROCERY,
    CATEGORY_HEALTH_BEAUTY,
    CATEGORY_CLOTHING_SHOES,
    CATEGORY_SPORTS_AND_OUTDOOR,
    CATEGORY_AUTOMOTIVE,
    CATEGORY_ELECTRONICS

};




int add_product_to_seller(seller_prod_num_t *head, int prod_num){

    seller_prod_num_t *new = (seller_prod_num_t*)malloc(sizeof(seller_prod_num_t));
    seller_prod_num_t *last = head;

    new->value = prod_num;
    new->next = NULL;

    if(head == NULL){

        head=new;
        return OK;
    }

    while (last->next != NULL){
        last= last->next;
    }

    last->next=new;

    return 0;
}

int save_to_product_file(product_t *save_product){

    FILE *product_file;
    product_file = fopen("/Users/safatanzeem/Desktop/Demo/product.txt","a+");

    if(product_file == NULL){
        fprintf(stderr,"\n Error! File can't be opened");
        return 1;
    }

    fprintf(product_file, "%s,%s,%d,%d,%d,%f,%d,%f,%d\n",
            save_product->name,
            save_product->category,
            save_product->category_num,
            save_product->product_number,
            save_product->stock,
            save_product->price,
            save_product->discount_code,
            save_product->discount_percentage,
            save_product->seller_id
            );

        fclose(product_file);
    return OK;
}


int add_new_product(struct SELLER *seller){
    product_t *new_product = (product_t*)malloc(sizeof(product_t));
    product_t *product_list = get_products();
    int product_number = 0;
    //char *data = NULL;

    printf(" Please enter the following information about the product:\n\n");

    printf("Select the category of your product from the following options:\n"
            "1. Home and Garden\n"
            "2. Grocery\n"
            "3. Health and Beauty\n"
            "4. Clothing and Shoes\n"
            "5. Sports and Outdoor\n"
            "6. Automotive\n"
            "7. Electronics\n"
            "Your choice:");
    int choice;
    scanf("%d", &choice);
    switch(choice){
    case CATEGORY_HOME_GARDEN:
       strcpy(new_product->category,"Home and Garden");
       new_product->category_num = 0;
       break;
    case CATEGORY_GROCERY:
        strcpy(new_product->category,"Grocery");
        new_product->category_num = 1;
        break;
    case CATEGORY_HEALTH_BEAUTY:
        strcpy(new_product->category,"Health and Beauty");
        new_product->category_num = 2;
        break;

    case CATEGORY_CLOTHING_SHOES:
        strcpy(new_product->category,"Clothing and Shoes");
        new_product->category_num = 3;
        break;

    case CATEGORY_SPORTS_AND_OUTDOOR:
        strcpy(new_product->category,"Sports and Outdoor");
        new_product->category_num = 4;
        break;

    case CATEGORY_AUTOMOTIVE:
        strcpy(new_product->category,"Automotive");
        new_product->category_num = 5;
        break;

    case CATEGORY_ELECTRONICS:
        strcpy(new_product->category,"Electronics");
        new_product->category_num = 6;
        break;

    default:
        printf("Wrong choice! Please enter between 1 and 7\n");
        return ERROR_WRONG_CATEGORY;
    }
    printf("\n\nYou have chosen: %s\n", new_product->category);

    printf("Product number: ");
    scanf("%d",&product_number);

    while(product_list != NULL){
        if(product_list->product_number == product_number){
            printf("Product can't be added. Product number already exist. Please try again!");
            return add_new_product(seller);
        }
        else{
            product_list = product_list->next_product;
        }
    }
    new_product->product_number = product_number;

    char prod_name[NAME_MAX_LENGTH];
    char temp = '\0';
    printf("Product name:");
    scanf("%c", &temp);
    scanf("%[^\n]",prod_name);
    strcpy(new_product->name,prod_name);


    printf("Stock: ");
    scanf("%d", &new_product->stock);
    if(new_product->stock == 0){
        printf("Invalid entry! Stock cannot be zero");
        return -3;
    }

    printf("Price(in Dollars): ");
    scanf("%f", &new_product->price);
    if(new_product->price == 0.0){
        printf("Invalid entry! Price cannot be zero");
        return -4;
    }

    printf("Discount code: ");
    scanf("%d", &new_product->discount_code);

    printf("Discount percentage: ");
    scanf("%f", &new_product->discount_percentage);

    printf("Confirm Seller Id:");
    scanf("%d", &new_product->seller_id);


    seller_prod_num_t *head_ref = seller->products_number;
    add_product_to_seller(head_ref, new_product->product_number); //update product number in seller linked list
    save_to_product_file(new_product); //update product number in product file

    printf("Your product has been added in the inventory \n\n");
    printf("Product Number        Product Name        Category        Stock\n");
    printf("    %d             %s            %s         %d    \n",
            new_product->product_number,
            new_product->name,
            new_product->category,
            new_product->stock);

    return 0;
}

