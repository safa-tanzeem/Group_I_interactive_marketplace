/*
 * seller_menu.c
 *
 *  Created on: Dec. 6, 2020
 *      Author: safatanzeem
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "seller_manager.h"
#include "display_inventory.h"
#include "inventory_creation.h"
#include "common.h"
#include "seller.h"
#include <unistd.h>
#include "stock_update.h"


int seller_sub_menu(struct SELLER* seller){
    int choice        = 0;
    int count         = 0;
    int attempts_left = 0;



    while (count < MAX_ATTEMPTS){
        int prod_num = 0;
        int quantity = 0;

        printf("\nWhat would you like to do today?\n"
                "1: Add new product\n"
                "2. Update stock of existing product\n"
                "3. View Revenue\n"
                "4. View Inventory\n"
                "0. Logout\n"
                "Enter Choice:");
        scanf("%d", &choice);

        switch(choice){

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

            printf("Please enter the Product Number of the product "
                    "whose stock you want to change: ");
            scanf("%d", &prod_num);
            printf("Please enter the quantity of products you want to add: ");
            scanf("%d", &quantity);

            update_stock(prod_num,quantity,1);
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

int seller_menu(){
    int choice = 0;
    printf("---SELLER MENU---.\n\n");

    int count = 0;
    int attempts_left = 0;




    while (count < MAX_ATTEMPTS){
        int seller_id = 0;
        char password[20];
        char name[20];
        char temp;


        printf("\nPlease select from the following choices:\n"
                "1. Already have an account? Enter 1 to Sign in\n"
                "2. Want to create a new account? Enter 2 to sign up\n"
                "0. to EXIT\n"
                "Enter choice:");
        scanf("%d", &choice);

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
