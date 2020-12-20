/*
 * main.c
 *
 *  Created on: Dec. 5, 2020
 *      Author: muhammadbsalman
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/scanner.h"
#include "../include/buyer_wallet.h"
#include "../include/buyer_functions.h"
#include "../include/common.h"
#include "../include/seller_menu.h"


/**
 * \brief main function, will re-direct to buyer-seller menus
*/

int main(){


//Variable that stores user's initial buyer/seller preferance
//Setting to 3, because that is the default quit option

int choice = 3;
int output;

do{

    //Introductory Remarks
    printf("-----WELCOME TO THE INTERACTIVE MARKETPLACE!-----\n");
    printf("You have the choice to act as a (1) buyer, (2) seller, or (3) quit marketplace.\n");

    //Loop until acceptable value entered
    do{
        printf("Enter your choice as a numerical integer value: ");
        
		output=scanf("%i", &choice);
        if(validate(output)==OK){
        	break;
		}
    }while(1);

    switch(choice){
        case 1:
            printf("\n---BUYER MENU---\n");
    		add_cart();
            break;

        case 2:
            seller_menu();
            break;
        
        case 3:
        	printf("\nYou are quitting the Marketplace!\n");
        	break;
        
        default:
        	printf("\nPlease enter a valid option!");
        
    }


}while(choice != 3); //Continue marketplace until user chooses to quit


printf("\nHope you enjoyed your experience!\nSee you soon!\n");
printf("-----YOU HAVE LEFT THE INTERACTIVE MARKETPLACE-----");


return 0;
}
