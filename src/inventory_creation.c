/*
 * main.c
 *
 *  Created on: Nov. 15, 2020
 *      Author: safatanzeem
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "inventory_creation.h"
#include "../include/scanner.h"
#include "../include/common.h"
#include "../include/seller_manager.h"
#include "../include/seller.h"


enum category_choice_e {
    CATEGORY_HOME_GARDEN = 1,
    CATEGORY_GROCERY,
    CATEGORY_HEALTH_BEAUTY,
    CATEGORY_CLOTHING_SHOES,
    CATEGORY_SPORTS_AND_OUTDOOR,
    CATEGORY_AUTOMOTIVE,
    CATEGORY_ELECTRONICS

};

/**\brief This function adds new product's product number in seller database
 * @param[in] head contains the head linked list where the product is to be added
 * @param[in] prod_num product number that needs to be added
 * return 0 on success
 */

int add_product_to_seller(seller_prod_num_t **head, int prod_num){

    seller_prod_num_t *new = (seller_prod_num_t*) malloc(sizeof(seller_prod_num_t));
    seller_prod_num_t *last = *head;
    //printf("%d", head->value);

    new->value = prod_num;
    new->next = NULL;

    if (*head == NULL){
        printf("Entering head\n");
        *head = new;
        return OK;
    }

    while (last->next != NULL){
        last = last->next;
    }

    last->next = new;

    return 0;
}

/**\brief This function saves newly added product to inventory
 * @param[in] save_product contains all information about newly added product
 * return 0 on success, -3 on error
 */

int save_to_product_file(product_t *save_product){

    /*Checking input validation*/
    if(save_product == NULL){
        printf("Something went wrong, new product is not added to inventory\n");
        return ERROR_NULL_POINTER;
    }

    FILE *product_file;
    product_file = fopen("/Users/safatanzeem/Desktop/Demo/product.txt","a+");

    if(product_file == NULL){
        fprintf(stderr,"\n Error! File can't be opened");
        return ERROR_NULL_POINTER;
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

/** \brief This function adds product in the inventory
 * This product takes structure Seller as an input which contains all the
 * information about seller and adds a new product in the inventory
 * @param[in] seller contains all information about seller
 * return 0 on success, -1 if wrong cateogary is chosen
 * return -4 if number of digits for product number is  not equal to 5
 * return -2 if the length of name is greater than 20
 * return -6 if stock for product added is 0
 * return -5 if price of product added is 0
 * return -3 if input parameter for function is NULL
 */

int add_new_product(struct SELLER *seller){

    if(seller == NULL){
        printf("Seller information invalid, Product can't be added\n");
        return ERROR_NULL_POINTER;
    }

    product_t *new_product = (product_t*)malloc(sizeof(product_t));
    product_t *product_list = get_products();
    int product_number = 0;
    int output = 0;
    int choice = 0;


    printf(" Please enter the following information about the product:\n\n");

    while (1){
        printf(
                "Select the category of your product from the following options:\n"
                        "1. Home and Garden\n"
                        "2. Grocery\n"
                        "3. Health and Beauty\n"
                        "4. Clothing and Shoes\n"
                        "5. Sports and Outdoor\n"
                        "6. Automotive\n"
                        "7. Electronics\n"
                        "Your choice:");
        output = scanf("%d", &choice);

        if (validate(output) == OK){
            break;
        }
    }


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

    /* input validation for product number*/
    output = 0;
    while (1){
        printf("Product number(5-Digit): ");
        output = scanf("%d", &product_number);

        if (validate(output) == OK){
            break;
        }
    }

    if(product_number < 10000 || product_number > 99999){
        printf("Enter 5 digits product number");
        return ERROR_PRODUCT_NUMBER_DIGITS;

    }

    /* Checking if the product number already exist*/
    while (product_list != NULL){
        if (product_list->product_number == product_number){
            printf(
                    "Product can't be added. Product number already exist. Please try again!");
            return add_new_product(seller);
        }else{
            product_list = product_list->next_product;
        }
    }
    new_product->product_number = product_number;

    /* Adding product name*/
    char prod_name[NAME_MAX_LENGTH];
    char temp = '\0';
    printf("Product name(Maximum 20 characters):");
    scanf("%c", &temp);
    scanf("%[^\n]", prod_name);
    strcpy(new_product->name, prod_name);

    /* Checking if the length of name is greater than 20 */
    if (strlen(new_product->name) > 20){
        printf(" Invalid input! Please enter less than 20 characters.");
        return ERROR_WRONG_NAME;
    }

    /* Adding stock*/
    output = 0;
    while (1){
        printf("Stock: ");
        output = scanf("%d", &new_product->stock);
        if (validate(output) == OK){
            break;
        }
    }

    /*Checking if stock is equal to zero*/
    if (new_product->stock <= 0){
        printf("Invalid entry! Stock cannot be negative or zero\n");
        return ERROR_STOCK;
    }

    /*Adding price*/
    output = 0;
    while (1){
        printf("Price(in CAD): ");
        output = scanf("%f", &new_product->price);
        if (validate(output) == OK){
            break;
        }
    }
    /*Adding discount code*/
    output = 0;
    while (1){
        printf("Discount code(in digits): ");
        output = scanf("%d", &new_product->discount_code);
        if (validate(output) == OK){
            break;
        }
    }

    /*Adding discount percentage*/
    output = 0;
    while (1){
        printf("Discount percentage: ");
        output = scanf("%f", &new_product->discount_percentage);
        if (validate(output) == OK){
            break;
        }
    }

    /*Confirm seller id to add product*/
    output = 0;
    while(1){
        printf("Confirm Seller Id: ");
        scanf("%d", &new_product->seller_id);
        if( validate(output) == OK){
            break;
        }
    }

    if (new_product->seller_id != seller->seller_id){
        printf(
                "Seller Id doesn't match. Cannot add product! Please try again!");
        return add_new_product(seller);
    }

    /*update product number in seller linked list*/
    add_product_to_seller(&(seller->products_number), new_product->product_number);    /*update product number in product file*/
    save_to_product_file(new_product);

    printf("Your product has been added in the inventory \n\n");
    printf("Product Number        Product Name        Category        Stock\n");
    printf("    %d             %s            %s         %d    \n",
            new_product->product_number,
            new_product->name,
            new_product->category,
            new_product->stock);

    return OK;
}

