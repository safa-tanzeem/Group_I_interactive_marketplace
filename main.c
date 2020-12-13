/*
 * seller_menu.c
 *
 *  Created on: Dec. 4, 2020
 *      Author: safatanzeem
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "seller.h"
#include "inventory_creation.h"
#include "stock_update.h"
#include "seller_manager.h"
#include "common.h"
#include "display_inventory.h"
#include "buyer_wallet.h"
#include "buyer_functions.h"


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

/**
 * \brief The functions brings the user to the buyer's perspective.
*Allows the user to pick products to buy, then check them out
*Other functions include adding funds to their wallets, and pay for products
*/
void buyer_menu(){

    printf("\n---BUYER MENU---\n");
    add_cart();

    return;
}




int main(){


//Variable that stores user's initial buyer/seller preferance
//Setting to 3, because that is the default quit option

int choice = 3;

do{

    //Introductory Remarks
    printf("-----WELCOME TO THE INTERACTIVE MARKETPLACE!-----\n");
    printf("You have the choice to act as a (1) buyer, (2) seller, or (3) quit marketplace.\n\n\n");

    //Loop until acceptable value entered
    do{
        printf("Enter your choice as a numerical integer value: ");
        scanf("%i", &choice);
    }while(choice != 1 && choice != 2 && choice != 3);

    switch(choice){
        case 1:
            buyer_menu();
            break;

        case 2:
            seller_menu();
            break;
    }


}while(choice != 3); //Continue marketplace until user chooses to quit


printf("\nHope you enjoyed your experience!\nSee you soon!\n");
printf("-----YOU HAVE LEFT THE INTERACTIVE MARKETPLACE-----");


return 0;
}
