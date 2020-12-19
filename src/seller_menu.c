/*
 * seller_menu.c
 *
 *  Created on: Dec. 6, 2020
 *      Author: safatanzeem
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/seller_manager.h"
#include "../include/display_inventory.h"
#include "../include/inventory_creation.h"
#include "../include/common.h"
#include "../include/seller.h"
#include "../include/stock_update.h"

/*\brief This function displays and allows the seller to access all seller files
 * This function displays all the available features to the seller and also allows him
 * to access desired feature.
 * @param[in] *seller Pointer to a structure seller which has all the information of seller in it.
 * @return 0 on success, -3 if the pointer is NULL
 * */
int seller_sub_menu(struct SELLER* seller){

    if(seller == NULL){
        printf("Error while fetching seller information\n");
        return ERROR_NULL_POINTER;
    }

    int choice        = 0;
    int count         = 0;
    int attempts_left = 0;

    while (count < MAX_ATTEMPTS){
        int prod_num = 0;
        int quantity = 0;
        int flag     = 1;
        int output   = 0;




        while(1){

            printf("\nWhat would you like to do today?\n"
                    "1: Add new product\n"
                    "2. Update stock of existing product\n"
                    "3. View Revenue\n"
                    "4. View Inventory\n"
                    "0. Logout\n"
                    "Enter Choice:");
            //scanf("%d", &choice);

            output = scanf("%d", &choice);
            if( validate(output) == OK){
                break;
            };

        }


        switch (choice) {

        case 0:
            seller_log_out(seller);
            return OK;
            break;

        case 1:
            printf("You have chosen to add new products in the inventory. \n");
            add_new_product(seller);
            break;

        case 2:
            printf("You have chosen to Update stock of existing product\n\n");

            /* Input the value of product number and check the validation*/
            output = 0;
            while(1){
                printf("Please enter the Product Number of the product "
                        "whose stock you want to change: ");
                output = scanf("%d", &prod_num);
                if( validate(output) == OK){
                    break;
                }
            };

            seller_prod_num_t *current_product = seller->products_number;

            while (flag == 1){
                if (current_product->value == prod_num){
                    printf("Product exists!\n");
                    flag = 0;
                }else{
                    if (current_product->next == NULL){
                        printf("The product doesn't exist in your inventory\n");
                        return seller_sub_menu(seller);
                        //flag = 0;
                    }
                    current_product = current_product->next;
                }
            }

            /* Input the quantity seller wants to add and check the validation*/
            output = 0;
            while(1){
                printf(
                        "Please enter the quantity of products you want to add: ");
                output = scanf("%d", &quantity);
                if( validate(output) == OK){
                    break;
                }
            }

            update_stock(prod_num, quantity, 1);
            break;

        case 3:
            printf("You have chosen to View Revenue\n\n");
            show_revenue(seller);

            break;

        case 4:
            printf("You have chosen to view Inventory\n\n");
            display_inventory(seller);
            break;

        default:
            printf("Wrong choice entered\n");
            attempts_left = MAX_ATTEMPTS - (count + 1);
            printf("Attempts left = %d \n\n", attempts_left);
            if (attempts_left == 0){
                printf("You have exhausted all the attempts");
            }
            count++;
        }

    }
    return OK;
}

/*This function displays different features for seller
 * when the user enters seller marketplace
 * @return 0 on success
 **/

int seller_menu(){


    int choice          = 0;
    int count           = 0;
    int attempts_left   = 0;
    int output          = 0;

    printf("---SELLER MENU---.\n\n");

    while (count < MAX_ATTEMPTS){
        int seller_id = 0;
        char password[20];
        char name[20];
        char temp;


        while(1){
            printf("\nPlease select from the following choices:\n"
                    "1. Already have an account? Enter 1 to Sign in\n"
                    "2. Want to create a new account? Enter 2 to sign up\n"
                    "0. to EXIT\n"
                    "Enter choice:");

            output = scanf("%d", &choice);
            if( validate(output) == OK){
                break;
            }


        }


        switch (choice) {

        case 0:
            printf("Thank you for choosing Market Place.."
                    "Hope to see you soon again \n\n");
            return OK;
            break;

        case 1:

            printf("\nYou have chosen to Sign in\n");

            struct SELLER* seller = (struct SELLER*)malloc(sizeof(struct SELLER));

            printf("Please enter your seller_id:");
            scanf("%d",&seller_id);

            printf("Please enter your password:");
            scanf("%s",password);

            seller = seller_log_in(seller_id ,password);

            if(seller == NULL){
                break;
            }else{
                //printf("You have successfully signed in\n\n");
                seller_sub_menu(seller);
            }
            break;

        case 2:

            printf(" You have chosen to sign up\n");
            printf("Please enter seller_id:");
            scanf("%d", &seller_id);

            printf("Please enter name:");
            scanf("%c", &temp);
            scanf("%[^\n]",name);

            printf("Please enter password:");
            scanf("%s", password);

            seller_sign_up(seller_id,name,password);
            break;

        default:

            printf("Wrong choice entered!\n");
            attempts_left = MAX_ATTEMPTS - (count + 1);
            printf("Attempts left = %d \n\n", attempts_left);

            if (attempts_left == 0){
                printf("You have exhausted all the attempts\n");
            }
            count++;
        }

    }
    return OK;
}
